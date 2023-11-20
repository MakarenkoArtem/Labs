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

int main() {
    char* str = getStr();
    if (str == NULL) {
        outputText(MemoryError"\n");
        _getch();
        return !OK;
    }
    outputText("|");
    outputText(str);
    outputText("|\n|");
    outputText(stdStr(str, (char*)OneSpaceLeft, (char*)OneSpaceRight));
    outputText("|");
    freeOneDArr(str);
    _getch();
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
