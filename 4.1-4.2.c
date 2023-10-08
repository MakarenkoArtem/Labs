

#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorCountNotNumber -1
#define ErrorCountNotInteger -2
#define ErrorCountLessZero -3
#define ErrorListHasNotZero "List has not 0"

char* checkInPut(int resultInput);
int inputCount(float* count);
void* mallocList(float count);
int inputList(float* list, float count);
int solutionFunc(float* list, int resultInput, float count, float* avg);
int findBorders(float* list, int* indexFirstMaxNum, int* indexLastZero, float count);
float average(float* list, int leftBorder, int rightBorder);
void freeList(float* list);
int outPut(float s);
int outPutText(char* s);

int main() {
	float count, avg;
	float* list;
	int resultInput = inputCount(&count);
	if (resultInput) {
		outPutText(checkInPut(resultInput));
		return !OK;
	}
	list = (float*)mallocList(count);
	inputList(list, count);
	char* result = solutionFunc(list, resultInput, count, &avg);
		if (result) {
			outPutText(result);
		}
		else {
			outPut(avg);
		}
	freeList(list);
	return OK;
}
void freeList(float* list) {
	free(list);
	list = NULL;
}

void* mallocList(float count) {
	return malloc(sizeof(float) * (int)count);
}
int inputCount(float* count) {
	printf("Enter count: ");
	if (scanf("%f", count) == 0) {
		return ErrorCountNotNumber;
	}
	else if (*count != (int)*count) {
		return ErrorCountNotInteger;
	}
	else if (*count <= 0) {
		return ErrorCountLessZero;
	}
	return OK;
}
int inputList(float* list, float count) {
	for (int i = 0; i < count; ++i) {
		printf("%i value: ", i);
		while (scanf("%f", &list[i]) == 0) {
			printf("Value not number\n%i value: ", i);
			scanf("%*[^\r^\n]");
		}
	}
	return OK;
}

char* checkInPut(int resultInput) {
	switch (resultInput) {
	case ErrorCountNotNumber:
		return "Count not number";
	case ErrorCountNotInteger:
		return "Count not integer";
	case ErrorCountLessZero:
		return "Count <= 0";
	default:
		return "OК";
	}
}

int solutionFunc(float* list, int resultInput, float count, float* avg) {
	int indexFirstMaxNum = 0, indexLastZero = -1;
	if (findBorders(list, &indexFirstMaxNum, &indexLastZero, count)) {
		return ErrorListHasNotZero;
	}
	int leftBorder = indexFirstMaxNum, rightBorder = indexLastZero;
	if (leftBorder > rightBorder) {
		leftBorder = leftBorder + rightBorder;
		rightBorder = leftBorder - rightBorder;
		leftBorder = leftBorder - rightBorder;
	}
	*avg = average(list, leftBorder, rightBorder);
	return OK;
}
int findBorders(float* list, int* indexFirstMaxNum, int* indexLastZero, float count) {
	float maxValue = list[0];
	for (int i = 0; i < count; ++i) {
		if (list[i] == 0.0) {
			*indexLastZero = i;
		}
		if (list[i] > maxValue) {
			maxValue = list[i];
			*indexFirstMaxNum = i;
		}
	}
	return *indexLastZero == -1;
}
float average(float* list, int leftBorder, int rightBorder) {
	float sumElems = 0;
	for (int i = leftBorder; i <= rightBorder; ++i) {
		sumElems += list[i];
	}
	return sumElems / (float)(rightBorder - leftBorder + 1);
}

int outPutText(char* s) {
	printf(s);
	_getch();
	return OK;
}

int outPut(float s) {
	printf("Value=%f\n", s);
	_getch();
	return OK;
}
