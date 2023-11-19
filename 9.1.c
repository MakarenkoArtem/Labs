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
int solutionFunc(char* str, char*** listWords, int** listCounter, int* count);
int outputLists(char** listWords, int* listCounter, int count);

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char **listWords,*str = getStr();
    int count = 0, *listCounter;
    if (!solutionFunc(str, &listWords, &listCounter, &count) && !outputLists(listWords, listCounter, count)) {
    }
    else {
        outputText("\n"Error);
        _getch();
        return !OK;
    }
    freeOneDArr(str);
    freeTwoDArr(listWords, count);
    freeOneDArr(listCounter);
    _getch();
    return OK;
}

int solutionFunc(char* str, char*** listWords, int** listCounter, int* count) {
    int n, j;
    delSymbols(str, &OneSpaceRight""OneSpaceLeft);
    stdStr(lowerStr(str), &OneSpaceLeft, &OneSpaceRight);
    char** listStr = split(str, " ", &n);
    *listWords = (char**)mallocList(n, sizeof(char*));
    *listCounter = (int*)mallocList(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        for (j = 0; j < *count && !compareStr((*listWords)[j], listStr[i]); ++j);
        if (*count == j) {
            (*listWords)[(*count)++] = copyStr(listStr[i]);
            (*listCounter)[j] = 0;
        }
        ++(*listCounter)[j];
    }
    freeOneDArr(listStr, n);
    return OK;
}

int outputLists(char** listWords, int* listCounter, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %i\n", listWords[i], listCounter[i]);
    }
    return OK;
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
