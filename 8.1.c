#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries\mystring.h"

#define OK 0
#define ErrorIncorrectInput "Incorrect input"
#define MemoryError "Memory error"
#define OneSpaceRight " ,!.?-)"
#define OneSpaceLeft "("

int outputText(char* s);
int solutionFunc(char* str);

int main() {
    char str[] = "";
    gets(str);
    outputText("|");
    outputText(str);
    outputText("|\n|");
    solutionFunc(str);
    outputText(str);
    outputText("|");
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

int outputText(char* s) {
    printf(s);
    return OK;
}
