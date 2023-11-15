#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdlib.h>
#include<stdio.h>


int lessOrEqualStr(char* a, char* b);
void sortWords(char** words, int count);
char* concatWords(char* str, char** words, int count);//join
char* copyStr(char* str);
char* lowerStr(char* str);
char* toStr(char s);
char* addStr(char* str, char* addStr);
char* createNewString(int count);
char* delChar(char* str, int index);
char* subStr(char* str, int start, int end);
int lenStr(char* str);
int compareStr(char* a, char* b);
char* addChar(char* str, int index, char addChar);
char** split(char* str, char* s, int* n);
char* charInSyms(char s, char* syms);
char* replace(char* str, char* lastValue, char* newValue, int count);
char* join(char** list, int count, char* joiner);
char* addStrOnIndex(char* str, char* addStr, int index);
