#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries\mystring.h"
#include <locale.h>

#define OK 0
#define Error "Error"
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight " ,!.?-)"
#define OneSpaceLeft "("


int outputText(char* s);
void* mallocList(int count, int sizeOfType);
int solutionFunc(char* str, char*** listWords, int** listCounter, int* count);
int outputLists(char** listWords, int* listCounter, int count);

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    char str[100];
    gets(str);
    char** listWords;
    int count=0, *listCounter;
    if (!solutionFunc(str, &listWords, &listCounter, &count) && !outputLists(listWords, listCounter, count)){
    }
    else {
        outputText("\n"Error);
    }
    _getch();
    return OK;
}

void* mallocList(int count, int sizeOfType) {
    return malloc(sizeOfType * count);
}

int solutionFunc(char* str, char*** listWords, int** listCounter, int* count) {
    int n, j;
    char s[2] = " \0";
    for (int i = 0; i < lenStr(OneSpaceRight""OneSpaceLeft); ++i) {
        if (OneSpaceRight""OneSpaceLeft[i] == ' ') { continue; }
        s[0] = OneSpaceRight""OneSpaceLeft[i];
        replace(str, s, " ", -1);
    }
    replace(str, "  ", " ", -1);
    lowerStr(str);
    char** listStr = split(str, " ", &n);
    *listWords = (char**)mallocList(n, sizeof(char*));
    *listCounter = (int*)mallocList(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        for (j = 0; j < *count && !compareStr((*listWords)[j], listStr[i]); ++j);
        if (*count == j) {
            (*listWords)[*count] = (char*)mallocList(lenStr(listStr[i]) + 1, sizeof(char));
            (*listWords)[(*count)++] = listStr[i];
            (*listCounter)[j] = 1;
        }
        else {
            ++(*listCounter)[j];
        }
    }
    free(listStr);
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
