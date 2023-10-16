#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorIncorrectInput "Incorrect input"

int inputCount(int* count);
void** createMatrix(int columns, int rows);
void* mallocList(int count);
void* callocList(int count);
int inputMatrix(int** matrix, int columns, int rows);
int solutionFunc(int** matrix, int count);
int printMatrix(int** matrix, int columns, int rows);
void freeMatrix(int** matrix, int rows);
int main() {
	int count;
	if (inputCount(&count)) {
		outputText(ErrorIncorrectInput);
		return !OK;
	}
	int** matrix = (int**)createMatrix(count, count);
	inputMatrix(matrix, count, count);
	solutionFunc(matrix, count);
	printMatrix(matrix, count, count);
	freeMatrix(matrix, count);
	return OK;
}
int inputCount(int* count) {
	printf("Enter count: ");
	return scanf("%i", count) == 0 || *count <= 0;
}

void* mallocList(int count) {
	return malloc(sizeof(int) * (int)count);
}

void* callocList(int count) {
	return calloc(count, sizeof(int));
}

void** createMatrix(int columns, int rows) {
	int** matrix = (int*)callocList(rows);
	for (int i = 0; i < rows; ++i) {
		matrix[i] = (int*)callocList(columns);
	}
	return matrix;
}

int inputMatrix(int** matrix, int columns, int rows){
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			while (scanf("%i", &matrix[i][j]) == 0) {
				printf("Value not number\n");
				scanf("%*[^\r^\n]");
			}
		}
	}
	return OK;
}

void swap(int* adres1, int* adres2) {
	*adres1 = *adres1 + *adres2;
	*adres2 = *adres1 - *adres2;
	*adres1 = *adres1 - *adres2;
}

int solutionFunc(int** matrix, int count) {
	for (int i = 0; i < count - 1; ++i) {
		for (int j = count - 2 - i; j > -1; --j) {
			swap(&matrix[i][j], &matrix[count - 1 - j][count - 1 - i]);
		}
	}
	return OK;
}

int printMatrix(int** matrix, int columns, int rows) {
	for (int i = 0; i < rows; ++i) {
		printf("\n");
		for (int j = 0; j < columns; ++j) {
			printf("%i ", matrix[i][j]);
		}
	}
	return OK;
}

void freeMatrix(int** matrix, int rows){
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
