#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorIncorrectInput "Incorrect input"
#define SquareMatrix -1
#define SpiralMatrix -10
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
void** copyMatrix(TypeOfMatix** matrix, int columns, int rows);
int inputMatrix(TypeOfMatix** matrix, int columns, int rows);
void swap(TypeOfMatix* address1, TypeOfMatix* address2);
int solutionFunc(TypeOfMatix** matrix, int columns, int rows, int counterMatrix);
int printMatrix(TypeOfMatix** matrix, int columns, int rows);
void freeMatrix(TypeOfMatix** matrix, int rows);
int outputText(char* s);

int main() {
	int rows, columns;
	if (inputColRow(&rows, &columns)) {
		outputText(ErrorIncorrectInput);
		_getch();
		return !OK;
	}
	TypeOfMatix** matrix = (TypeOfMatix**)createMatrix(columns, rows);
	inputMatrix(matrix, columns, rows);
	TypeOfMatix** matrixNew = (TypeOfMatix**)copyMatrix(matrix, columns, rows);
	int result = solutionFunc(matrix, columns, rows, 0);
	if (result == SpiralMatrix) {
		solutionFunc(matrixNew, columns, rows, 1);
		outputText("\n+1 extra point\n");
		printMatrix(matrixNew, columns, rows);
		outputText("\n+2 extra point\n");
	}else if(result == SquareMatrix){
		outputText("\n+2 extra point\n");
	}
	printMatrix(matrix, columns, rows);
	freeMatrix(matrixNew, rows);
	freeMatrix(matrix, rows);
	_getch();
	return OK;
}

void** copyMatrix(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix** matrixNew = (TypeOfMatix**)createMatrix(columns, rows);
	for (int i = 0; i < rows; ++i) {
		for (int j = 0; j < columns; ++j) {
			matrixNew[i][j] = matrix[i][j];
		}
	}
	return (void**)matrixNew;
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

void swap(TypeOfMatix* address1, TypeOfMatix* address2) {
	TypeOfMatix dop = *address1;
	*address1 = *address2;
	*address2 = dop;
}

void sorted(TypeOfMatix** list, int count) {
	for (int i = 0; i < count; ++i) {
		for (int y = i + 1; y < count; ++y) {
			if (*list[i] > *list[y]) {
				swap(list[i], list[y]);
			}
		}
	}
}

TypeOfMatix** createSnakeList(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix** list = (TypeOfMatix**)callocList(columns * rows, sizeof(void*));
	int counter = 0, i = 0;
	while (++i < rows + columns) {
		for (int x = max(0, i - columns); x < min(i, columns); ++x) {
			list[counter++] = matrix[i - x - 1] + x;
		}
		if (++i >= rows + columns) { break; };
		for (int x = max(0, i - rows); x < min(i, rows); ++x) {
			list[counter++] = matrix[x] + i - x - 1;
		}
	}
	return list;
}

TypeOfMatix** createFromCenterList(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix** list = (TypeOfMatix**)callocList(columns * rows, sizeof(void*));
	int c, counter = 0, center = rows/2, x = center, y = center, i = 0;
	while (x < columns) {
		++i;
		c = i;
		while(c--){//for (; y > center - i; --y) {//int y = center + (i - 1)
			list[counter++] = matrix[y--] + x;
			//printf("%i", *list[counter - 1]);
		}
		if (y < 0) { break; }
		c = i;
		while(c--){//for (; x > center - i; --x) {//int x = center +(i - 1)
			list[counter++] = matrix[y] + x--;
			//printf("%i", *list[counter - 1]);
		}
		if (x < 0) { break; }
		++i;
		c = i;
		while(c--){//for (; y < center + i; ++y) {//int y = center - (i - 1)
			list[counter++] = matrix[y++] + x;
			//printf("%i", *list[counter - 1]);
		}
		if (y >= rows) { break; }
		c = i;
		while(c--){//for (; x < center + i; ++x) {//int x = center - (i - 1)
			list[counter++] = matrix[y] + x++;
			//printf("%i", *list[counter - 1]);
		}
	}
	return list;
}

TypeOfMatix** createList(TypeOfMatix** matrix, int columns, int rows) {
	TypeOfMatix** list = (TypeOfMatix**)callocList(columns * rows, sizeof(void*));
	int counter = 0, i = 0;
	for (int y = columns - 1; y > columns % 2 - 1; y -= 2) {
		for (int x = rows - 1; x > -1; --x) {
			list[counter++] = matrix[x] + y;
		}
		for (int x = 0; x < rows; ++x) {
			list[counter++] = matrix[x] + y - 1;
		}
	}
	if (columns % 2) {
		for (int x = rows - 1; x > -1; --x) {
			list[counter++] = matrix[x];
		}
	}
	return list;
}

int solutionFunc(TypeOfMatix** matrix, int columns, int rows, int counterMatrix) {
	int answer = OK;
	TypeOfMatix** list;
	if (columns == rows) {
		answer = SquareMatrix;
		if (rows % 2) {
			answer = SpiralMatrix;
		}
		if (counterMatrix) {
			list = createFromCenterList(matrix, columns, rows);
		}
		else {
			list = createSnakeList(matrix, columns, rows);
		}
	}
	else {
		list = createList(matrix, columns, rows);		
	}
	sorted(list, columns * rows);
	free(list);
	return answer;
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
	return OK;
}
