#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorIncorrectInput "Incorrect input"

int inputColRow(int* rows, int* columns);
void** createMatrix(int columns, int rows);
void* mallocList(int count, int sizeOfType);
void* callocList(int count, int sizeOfType);
int inputMatrix(int** matrix, int columns, int rows);
int solutionFunc(int** matrix, int columns, int rows);
int printMatrix(int** matrix, int columns, int rows);
void freeMatrix(int** matrix, int rows);
int main() {
	int rows, columns;
	if (inputColRow(&rows, &columns)) {
		outputText(ErrorIncorrectInput);
		return !OK;
	}
	int** matrix = (int**)createMatrix(columns, rows);
	inputMatrix(matrix, columns, rows);
	solutionFunc(matrix, columns, rows);
	printMatrix(matrix, columns, rows);
	freeMatrix(matrix, rows);
	return OK;
}

int inputColRow(int* rows, int* columns) {
	printf("Enter rows and columns: ");
	return scanf("%i %i", rows, columns) <2 || *rows <= 0 || *columns <= 0;
}

void* mallocList(int count, int sizeOfType) {
	return malloc(sizeOfType * count);
}

void* callocList(int count, int sizeOfType) {
	return calloc(count, sizeOfType);
}

void** createMatrix(int columns, int rows) {
	int** matrix = (int*)callocList(rows, sizeof(int*));
	for (int i = 0; i < rows; ++i) {
		matrix[i] = (int*)callocList(columns, sizeof(int));
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

int solutionFunc(int** matrix, int columns, int rows) {
	int x = 0, y = 0, maxValue = matrix[0][0], sum = 0;
	for (int i = 0; i < rows - 1; ++i) {
		for (int j = columns - 2 - i; j > -1; --j) {
			sum += matrix[i][j];
		}
	}

	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (maxValue < matrix[i][j]) {
				maxValue = matrix[i][j];
				x = i;
				y = j;
			}
		}
	}
	matrix[x][y] = sum;
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
