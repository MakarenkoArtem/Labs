#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries\mystring.h"

#define OK 0
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight " ,!.?-)"
#define OneSpaceLeft "("


int inputCount(int* count);
int outputText(char* s);
int solutionFunc(char* str);

int main() {
    int count, n=0;
    if (inputCount(&count)) {
        outputText(ErrorIncorrectInput);
        _getch();
        return !OK;
    }
    scanf("\n");
    //fflush(stdin);
    char** list = (char**)malloc(count * sizeof(void*));
    for (int i = 0; i < count; ++i) {
        list[i]= (char*)malloc(40*sizeof(char));
        gets(list[i]);
    }
    char* a = (char*)malloc(50* sizeof(char));
    gets(a);
    char* b = (char*)malloc(50* sizeof(char));
    gets(b);
    for (int k = 0; k < count; k++) {
        outputText(list[k]);
        outputText("\n");
        solutionFunc( list[k]);
        char** listStr = split(list[k], " ", &n);
        if (n != 3) {
            outputText("It is not FIO\n");
            continue;
        }
        listStr[2]=replace(listStr[2]+1, a, b, -1)-1;
        outputText(join(listStr, 3, " "));
        outputText("\n");
    }
    _getch();
    return OK;
}

int solutionFunc(char* str) {
    int i = 0;
    while (str[i]) {
        if (str[i] == ' ' && (i == 0 || str[i+1]=='\0' || charInSyms(str[i + 1], OneSpaceRight))) {
            delChar(str, i);
            continue;
        }else if(charInSyms(str[i], OneSpaceLeft) && str[i+1]==' '){
            delChar(str, i+1);
            continue;
        }
        i++;
    }
    return OK;
}

int inputCount(int* count) {
    printf("Enter count: ");
    return scanf("%i", count) == 0 || *count <= 0;
}

int outputText(char* s) {
    printf(s);
    return OK;
}