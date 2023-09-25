#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define factorialZero 1;

int inPut(float* e);
float solutionFunc(float e);
int outPut(char* s, float value);
int answerFunc(float e, float value);

void main() {
	float e;
	if (!inPut(&e)){
		outPut("Incorrect input", 0.0);
	}else {
		answerFunc(e, solutionFunc(e));
	}
	return 0;
}

int inPut(float* e) {
	printf("Enter E = ");
	return scanf("%f", e) == 1 && *e>0;
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
		//printf("%i %f %f %f %f\n", factorial, currentValue, lastValue, currentValue + lastValue, fabs(currentValue + lastValue));
	} while (fabs(currentValue + lastValue)>=e || n==1);
	//value += lastValue;
	return value;
}

int answerFunc(float e, float value){
	int counter = 1;
	while ((int)e == 0) {
		e *= 10;
		++counter;
	}
	char s[] = { '%','.', counter + '0', "f"};
	//sprintf(s, s, value);
	outPut(s, value);
}
int outPut(char* s, float value) {
	printf(s, value);
	_getch();
	return 0;
}
