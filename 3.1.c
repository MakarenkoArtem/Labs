#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define factorialZero 1
#define Error "Incorrect input\n"
int inPut(float* e);
float solutionFunc(float e);
int output(float value);
int outputText(char* value);

int main() {
	float e;
	if (inPut(&e) != 0) {
		outputText(Error);
	}
	else {
		output(solutionFunc(e));
	}
	return OK;
}

int inPut(float* e) {
	printf("Enter E = ");
	int res = 0;
	if (scanf("%f", e) != 1 || 0> *e || e >1) {
		res = -1;
	}
	return res;
}
float solutionFunc(float e) {
	float currentValue, lastValue, value = 0;
	int n = 0, factorial = factorialZero;
	currentValue = 1.0 / factorial;
	do {
		lastValue = currentValue;
		factorial = -factorial * ++n;
		currentValue = 1.0 / factorial;
		value += lastValue;
	} while (fabs(currentValue + lastValue) >= e || n == 1);
	value += lastValue;
	return value;
}

int output(float value) {
	printf("%.4f", value);
	_getch();
	return OK;
}
int outputText(char* value) {
	printf(value);
	_getch();
	return OK;
}
