#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries\mystring.h"
#include <locale.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define OK 0
#define Error "Error"
#define MemoryError "Memory error"
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight ",!.?-)"
#define OneSpaceLeft "("


void* reallocList(void* str, int count, int sizeOfType);
void* mallocList(int count, int sizeOfType);
int outputText(char* s);
void freeTwoDArr(char** matrix, int rows);
void freeOneDArr(char* arr);
int inputCount(int* count);
char** solutionFunc(char*** list, char* a, char* b, int count);
int inputStrings(char** str, int count);
int outputLists(char** list, char** anotherList, int count);

int main() {
    int count;
    if (inputCount(&count)) {
        outputText(ErrorIncorrectInput);
        _getch();
        return !OK;
    }
    char** list = (char**)mallocList(count, sizeof(void*));
    if (inputStrings(&list, count)) {
        outputText(MemoryError"\n");
        _getch();
        return !OK;
    }
    char *a = getStr(), *b = getStr();
    if (a==NULL || b==NULL) {
        outputText(MemoryError"\n");
        _getch();
        return !OK;
    }
    char** answerList = solutionFunc(&list, a, b, count);
    if (answerList == (char**)!OK) {
        outputText(Error"\n");
        _getch();
        return !OK;
    }
    if (outputLists(list, answerList, count) == (char**)!OK) {
        outputText(Error"\n");
        _getch();
        return !OK;
    }
    _getch();
    return OK;
}

int inputStrings(char*** str, int count) {
    while (fgetc(stdin) != '\n');
    for (int i = 0; i < count; ++i) {
        (*str)[i] = getStr();
        if ((*str)[i] == NULL) {
            return !OK;
        }
    }
    return OK;
}

char** solutionFunc(char*** list, char* a, char* b, int count) {
    int n = 0;
    stdStr(a, &OneSpaceLeft, &OneSpaceRight);
    stdStr(b, &OneSpaceLeft, &OneSpaceRight);
    char** answerList = (char**)malloc(count * sizeof(void*));
    for (int k = 0; k < count; k++) {
        stdStr((*list)[k], &OneSpaceLeft, &OneSpaceRight);
        char** listStr = split((*list)[k], " ", &n);
        if (n == 3) {
            listStr[2] = (char*)reallocList(listStr[2], max(lenStr(listStr[2])+1, (lenStr(listStr[2]) / lenStr(a) + 1) * lenStr(b) + 1), sizeof(char));
            listStr[2] = replace((listStr[2] + 1), a, b, -1) - 1;
            answerList[k] = join(listStr, 3, " ");
        }
        else {
            answerList[k] = "It is not FIO";
        }
        freeTwoDArr(listStr, n);
    }
    return (count>=0)?(answerList):((char**)!OK);
}

int outputLists(char** list, char** anotherList, int count) {
    for (int i = 0; i < count; i++) {
        outputText("%s\n%s\n", list[i], anotherList[i]);
    }
    return (count >= 0) ? (OK) : ((int)!OK);
}

int outputText(char* s) {
    printf(s);
    return OK;
}

void freeTwoDArr(char** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDArr(char* arr) {
    free(arr);
}

int inputCount(int* count) {
    printf("Enter count: ");
    return scanf("%i", count) == 0 || *count <= 0;
}

void* reallocList(void* str, int count, int sizeOfType) {
    return realloc(str, sizeOfType * count);
}

void* mallocList(int count, int sizeOfType) {
    return malloc(sizeOfType * count);
}
