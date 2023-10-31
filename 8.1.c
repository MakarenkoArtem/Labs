#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries\strbase.h"

#define OK 0

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
	while (str[i] != '\0') {
		if (str[i] == ' ') {
			if (i == 0 || str[i + 1] == ' ' || str[i + 1] == '\0' || str[i + 1] == ','
				|| str[i + 1] == '!' || str[i + 1] == '.' || str[i + 1] == '?') {
				moveStr(str, i);
				continue;
			}
		}
		i++;
	}
	return OK;
}

int outputText(char* s) {
	printf(s);
	return OK;
}
