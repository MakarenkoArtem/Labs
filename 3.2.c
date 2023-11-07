#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorValuesAB -1
#define ErrorValueE -2
#define ErrorInput -3

int inPut(float* a, float* b, float* e);
char* checkInPut(int resultInput);
float solutionFunc(float a, float b, float e);
//char* solutionFunc(float a, float b, float e, bool text);
float function(float x);
float integralFunc(float a, float b, float h, int n);
int outputText(char* s);
int output(float s);

int main() {
	float a, b, e;
	int resultInput = inPut(&a, &b, &e);
	if (resultInput) {
		outputText(checkInPut(resultInput));
		return resultInput;
	}
	float result = solutionFunc(a, b, e);
	output(result);
	//free(result);
	return 0;
}

int inPut(float* a, float* b, float* e) {
	printf("Enter a b E:");
	if (scanf("%f%f%f", a, b, e) != 3) {
		return ErrorInput;
	}
	else if (*e <= 0) {
		return ErrorValueE;
	}
	else if (*b <= *a) {
		return ErrorValuesAB;
	}
	return OK;
}

char* checkInPut(int resultInput) {
	switch (resultInput) {
	case ErrorInput:
		return "Incorrect input";
	case ErrorValueE:
		return "Incorrect value: E <= 0";
	case ErrorValuesAB:
		return "Incorrect value: A >= B";
	default:
		break;
	}
}
/*
char* solutionFunc(float a, float b, float e, bool text) {
	float nFloat = (b - a) / 2 / e;
	int n = (int)nFloat + ((float)(int)nFloat != nFloat);
	float h = (b - a) / 2 / n;
	float integral = integralFunc(a, b, h, n);
	char* answer = (char*)calloc(100, sizeof(char));
	sprintf(answer, "Integral=%.4f", integral);
	return answer;
}
*/
float solutionFunc(float a, float b, float e) {
	float nFloat = (b - a) / 2 / e;
	int n = (int)nFloat + ((float)(int)nFloat != nFloat);
	float h = (b - a) / 2 / n;
	float integral = integralFunc(a, b, h, n);
	return integral;
}

float function(float x) {
	return logf(x);
}

float integralFunc(float a, float b, float h, int n) {
	float* x = (float*)malloc(sizeof(float) * (2 * n + 1));
	for (int i = 0; i < 2 * n + 1; ++i) {
		x[i] = a + i * h;
	}
	float component1 = function(x[0]), component2 = 0, component3 = 0, component4 = function(x[n * 2]);
	for (int i = 1; i <= n; ++i) {
		component2 += function(x[i * 2 - 1]);
	}
	for (int i = 1; i < n; ++i) {
		component3 += function(x[i * 2]);
	}
	free(x);
	x = NULL;
	float integral = h / 3 * (component1 + 4 * component2 + 2 * component3 + component4);
	return integral;
}

int outputText(char* s) {
	printf("%s\n", s);
	_getch();
	return 0;
}

int output(float s) {
	printf("Integral=%.4f\n", s);
	_getch();
	return 0;
}
