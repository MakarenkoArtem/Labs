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

int inputColRow(int* rows, int* columns);
void** createMatrix(int columns, int rows);
void* mallocList(int count, int sizeOfType);
void* callocList(int count, int sizeOfType);
int inputMatrix(TypeOfMatix** matrix, int columns, int rows);
TypeOfMatix* maxElem(TypeOfMatix** matrix, int columns, int rows);
TypeOfMatix sumOnDiagonal(TypeOfMatix** matrix, int columns, int rows);
int solutionFunc(TypeOfMatix** matrix, int columns, int rows);
int printMatrix(TypeOfMatix** matrix, int columns, int rows);
void freeMatrix(TypeOfMatix** matrix, int rows);
int outputText(char* s);

int main() {
	int rows, columns;
	if (inputColRow(&rows, &columns)) {
		outputText(ErrorIncorrectInput);
		return !OK;
	}
	TypeOfMatix** matrix = (TypeOfMatix**)createMatrix(columns, rows);
	inputMatrix(matrix, columns, rows);
	solutionFunc(matrix, columns, rows);
	printMatrix(matrix, columns, rows);
	freeMatrix(matrix, rows);
	_getch();
	return OK;
}

int inputColRow(int* rows, int* columns) {
	printf("Enter rows and columns: ");
	return scanf("%i %i", rows, columns) < 2 || *rows <= 0 || *columns <= 0;
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

TypeOfMatix sumOnDiagonal(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix maxValue = matrix[0][0], sum = 0;
	for (int i = rows - 1; i > -1; --i) {
		for (int j = 0; j < rows - i - 1; ++j) {
			sum += matrix[i][j];
		}
	}
	return sum;
}
TypeOfMatix* maxElem(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix* maxElement = matrix[0] + 0;
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			if (*maxElement < matrix[i][j]) {
				maxElement = matrix[i] + j;
			}
		}
	}
	return maxElement;
}
int solutionFunc(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix* maxElement = maxElem(matrix, columns, rows);
	*maxElement = sumOnDiagonal(matrix, columns, rows);
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
