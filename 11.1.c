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
#define IndexOutOfRange -2
#define Error "Error"
#define MemoryError "Memory error"
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight ",!.?-)"
#define OneSpaceLeft "("


void* reallocList(void* str, int count, int sizeOfType);
void* mallocList(int count, int sizeOfType);
int outputText(char* s);
void freeTwoDStr(char** matrix, int rows);
void freeOneDStr(char* arr);
void freeTwoDArr(void** matrix, int rows);
void freeOneDArr(void* arr);
int inputCount(int* count);
void swap(void** a, void** b);
void freeStructList(void* structList);
#define RFILE "input.txt"
#define WFILE "output.txt"
char* getStrFromFile(FILE*);
void outputNumListToFile(FILE* file, char** list, int n);
char** getListStrFromFile(FILE* file, int* k);

int main() {
    FILE* file = fopen(RFILE, "r"), *wfile= fopen(WFILE, "w");
    int k=0;
    char** list = getListStrFromFile(file, &k);
    delThisStr(list, "", &k);
    outputNumListToFile(wfile,list, k);
    freeTwoDStr(list, k);
    fclose(file);
    fclose(wfile);
    getchar();
    return OK;
}

char** getListStrFromFile(FILE* file, int* k) {
    int c = 5;
    char** list = (char**)mallocList(c, sizeof(void*));
    while (!feof(file)) {
        if (*k == c) {
            c *= 2;
            list = (char**)reallocList(list, c, sizeof(void*));
        }
        list[(*k)++] = getStrFromFile(file);
    }
    return list;
}
void outputNumListToFile(FILE* file, char** list, int n) {
    for (int i = 0; i < n; ++i){
        if (i) { fprintf(file, "\n"); }
        fprintf(file, "%d. %s", i+1, list[i]);
    }
}
char* getStrFromFile(FILE *file) {
    int count = 0, size = 10;
    char* str = (char*)mallocList(size, sizeof(char));
    if (str == NULL) { return (char*)Error; }
    while ((str[count] = fgetc(file)) != EOF && str[count] != '\r' && str[count] != '\n' && str[count] != '\0') {
        if (++count == size) {
            size *= 2;
            str = (char*)reallocList(str, size, sizeof(char));
            if (str == NULL) { return (char*)Error; }
        }
    }
    str[count] = '\0';
    return str;
}

int outputText(char* s) {
    printf(s);
    return OK;
}

void freeTwoDStr(char** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDStr(char* arr) {
    free(arr);
}

void freeTwoDArr(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDArr(void* arr) {
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

void swap(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}
