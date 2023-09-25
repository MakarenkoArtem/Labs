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
char* solutionFunc(float a, float b, float e, int resultInput);
float function(float x);
float integralFunc(float a, float b, float h, int n);
int outPut(char* s);

void main() {
	float a,b,e;
	int resultInput = inPut(&a, &b, &e);
	char* result = solutionFunc(a, b, e, resultInput);
	outPut(result);
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


char* solutionFunc(float a, float b, float e, int resultInput) {
	switch (resultInput){
	case ErrorInput:
		return "Incorrect input";
	case ErrorValueE:
		return "Incorrect value: E <= 0";
	case ErrorValuesAB:
		return "Incorrect value: A >= B";
	default:
		break;
	}
	float nFloat = (b - a) / 2 / e;
	int n = (int)nFloat + ((float)(int)nFloat != nFloat);
	float h = (b - a) / 2 / n;
	float integral = integralFunc(a, b, h, n);
	char answer[100];
	sprintf(answer, "integral=%.4f", integral);
	return answer;
}

float function(float x) {
	return logf(x);
}

float integralFunc(float a, float b, float h, int n){
	float* x= malloc(sizeof(float) * (2 * n + 1));
	for (int i = 0; i < 2 * n + 1; ++i) {
		x[i] = a + i * h;
	}
	float sum1 = function(x[0]), sum2=0, sum3=0, sum4 = function(x[n*2]);
	for (int i = 1; i <= n; ++i) {
		sum2 += function(x[i * 2 - 1]);
	}
	for (int i = 1; i < n; ++i) {
		sum3 += function(x[i * 2]);
	}
	float integral = h / 3 * (sum1 + 4 * sum2 + 2 * sum3 + sum4);
	return integral;
}

int outPut(char* s) {
	printf(s);
	_getch();
	return 0;
}
