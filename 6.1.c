#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorIncorrectInput "Incorrect input"
#define TypeOfMatix int
#ifdef TypeOfMatix==int 
	#define TOMFConsole "%d" //TOMFConsole-TypeOfMatixForConsole
#elif TypeOfMatix == float || TypeOfMatix==double
	#define TOMFConsole "%f"
#elif TypeOfMatix == unsigned int
	#define TOMFConsole "%u"
#elif TypeOfMatix == char
	#define TOMFConsole "%c"
#elif TypeOfMatix == long long int
	#define TOMFConsole "%lld"
#elif TypeOfMatix == long int
	#define TOMFConsole "%ld"
#endif

int inputCount(int* count);
void** createMatrix(int columns, int rows, int size);
void* mallocList(int count, int sizeOfType);
void* callocList(int count, int sizeOfType);
int inputMatrix(TypeOfMatix** matrix, int columns, int rows);
void swap(TypeOfMatix* address1, TypeOfMatix* address2);
int solutionFunc(TypeOfMatix** matrix, int count);
int printMatrix(TypeOfMatix** matrix, int columns, int rows);
void freeMatrix(TypeOfMatix** matrix, int rows);
int outputText(char* s);

int main() {
	int count;
	if (inputCount(&count)) {
		outputText(ErrorIncorrectInput);
		return !OK;
	}
	TypeOfMatix** matrix = (TypeOfMatix**)createMatrix(count, count, sizeof(TypeOfMatix));
	inputMatrix(matrix, count, count);
	solutionFunc(matrix, count);
	printMatrix(matrix, count, count);
	freeMatrix(matrix, count);
	_getch();
	return OK;
}

int inputCount(int* count) {
	printf("Enter count: ");
	return scanf("%i", count) == 0 || *count <= 0;
}

void* mallocList(int count, int sizeOfType) {
	return malloc(sizeOfType * count);
}

void* callocList(int count, int sizeOfType) {
	return calloc(count, sizeOfType);
}

void** createMatrix(int columns, int rows) {
	//1)sizeof(void*)-size all types addresses equal
	//2)(TypeOfMatix**)-in define changes the type
	//3)callocList-in C++ you only need to change the body of the callocList()/mallocList()
	TypeOfMatix** matrix = (TypeOfMatix**)callocList(rows, sizeof(void*));
	for (int i = 0; i < rows; ++i) {
		matrix[i] = (TypeOfMatix*)callocList(columns, sizeof(TypeOfMatix));
	}
	return (void**)matrix;
}

int inputMatrix(TypeOfMatix** matrix, int columns, int rows) {
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			while (scanf(TOMFConsole, &matrix[i][j]) == 0) {
				printf("Value not number\n");
				scanf("%*[^\r^\n]");
			}
		}
	}
	return OK;
}

void swap(TypeOfMatix* address1, TypeOfMatix* address2) {
	TypeOfMatix dop = *address1;
	*address1 = *address2;
	*address2 = dop;
}

int solutionFunc(TypeOfMatix** matrix, int count) {
	count--;
	for (int i = 0; i < count; ++i) {
		for (int j = count - 1 - i; j > -1; --j) {
			swap(&matrix[i][j], &matrix[count - j][count - i]);
		}
	}
	return OK;
}

int printMatrix(TypeOfMatix** matrix, int columns, int rows) {
	for (int i = 0; i < rows; ++i) {
		printf("\n");
		for (int j = 0; j < columns; ++j) {
			printf(TOMFConsole" ", matrix[i][j]);
		}
	}
	return OK;
}

void freeMatrix(TypeOfMatix** matrix, int rows) {
	for (int i = 0; i < rows; ++i) {
		free(matrix[i]);
	}
	free(matrix);
}

int outputText(char* s) {
	printf(s);
	_getch();
	return OK;
}
