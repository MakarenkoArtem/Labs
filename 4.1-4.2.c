
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

int inPut(float** list, float* count);
char* solutionFunc(float* list, int resultInput, float count);
int findBorders(float* list, int* indexFirstMaxNum, int* indexLastZero, float count);
float average(float* list, int leftBorder, int rightBorder);
int outPut(char* s);

void main() {
	float count;
	float* list;
	int resultInput = inPut(&list, &count);
	char* result = solutionFunc(list, resultInput, count);
	outPut(result);
	return 0;
}

int inPut(float** list, float* count) {
	printf("Enter count: ");
	if (scanf("%f", count) == 0) {
		return ErrorCountNotNumber;
	}
	else if (*count != (int)*count) {
		return ErrorCountNotInteger;
	}
	else if (*count<=0) {
		return ErrorCountLessZero;
	}
	*list = (float*)malloc(sizeof(float) * (int)*count);
	for (int i = 0; i < *count; ++i) {
		printf("%i value: ", i);
		while (scanf("%f", &(*list)[i]) == 0){
			printf("Value not number\n%i value: ", i);
			scanf("%*[^\r^\n]");	
		}
	}
	return OK;
}
char* solutionFunc(float* list, int resultInput, float count) {
	switch (resultInput) {
	case ErrorCountNotNumber:
		return "Count not number";
	case ErrorCountNotInteger:
		return "Count not integer";
	case ErrorCountLessZero:
		return "Count <= 0";
	default:
		break;
	}
	int indexFirstMaxNum=0, indexLastZero = -1;
	if (findBorders(list, &indexFirstMaxNum, &indexLastZero, count)) {
		return "List has not 0";
	}
	int leftBorder = indexFirstMaxNum, rightBorder = indexLastZero;
	if (leftBorder > rightBorder) {
		leftBorder = leftBorder + rightBorder;
		rightBorder = leftBorder - rightBorder;
		leftBorder = leftBorder - rightBorder;
	}
	char answer[100];
	sprintf(answer, "Answer=%f", average(list, leftBorder, rightBorder));
	free(list);
	list = NULL;
	return answer;
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
	for (int i= leftBorder; i <= rightBorder; ++i) {
		sumElems += list[i];
	}
	return sumElems / (float)(rightBorder - leftBorder + 1);
}

int outPut(char* s) {
	printf(s);
	_getch();
	return 0;
}
