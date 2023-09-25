#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>

int inPut(float* x, float* y);
char* solutionFunction(float x, float y);
int definitionY(float x, float y, int c);
int determiningPosPoint(float y, float y1);
char* findPosition(int a, int b, int c);
int outPut(char* s);

void main(){
	float x, y;
	if (!inPut(&x, &y)){
		outPut("Incorrect input");
	}else{
		outPut(solutionFunction(x, y));
	}
	return 0;
}

char* solutionFunction(float x, float y) {
	int a = definitionY(x, y, 0), b = definitionY(x, y, 1), c = definitionY(x, y, 2);
	return findPosition(a, b, c);
}
int outPut(char* s){
	printf(s);
	_getch();
	return 0;
}
int inPut(float* x, float* y) {
	printf("Enter: ");
	return scanf("%f%f", x, y) == 2;
}
char* findPosition(int a, int b, int c){
	if (a!=1 & b!=-1 & c!=1)	{
		return "Center";
	}else if (a==1 & b==1 & c==1)	{
		return "1";
	}else if (a==1 & b==1 & c==-1)	{
		return "2";
	}else if (a==1 & b==-1 & c==-1)	{
		return "3";
	}else if (a==-1 & b==-1 & c==-1){
		return "4";
	}else if (a==-1 & b==-1 & c==1)	{
		return "5";
	}else if (a==-1 & b==1 & c==1){
		return "6";
	}else if (a==0){
		return "y=x+2";
	}else if (b==0)	{
		return "y=-0.5*x-1";
	}else if (c==0)	{
		return "y=-2*x+2";
	}
}
int definitionY(float x, float y, int c){
	float y1;
	if (c == 0)
	{
		y1 = x + 2;
	}
	else if (c == 1)
	{
		y1 = -0.5*x-1;
	}else
	{
		y1 = -2*x+2;
	}
	return determiningPosPoint(y, y1);
}

int determiningPosPoint(float y, float y1){
	int a = 0;
	if (y1 < y){
		a=1;
	}else if(y1 > y){
		a=-1;
	}
	return a;
}
