#define _CRT_SECURE_NO_WARNINGS
#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>

#define OK 0
#define ErrorIncorrectInput "Incorrect input"

int inputCount(int* count);
void* mallocList(int count);
void* callocList(int count);
int inputList(int* list, int count);
int solutionFunc(int* list, int count, int* indexLastNegative, int* indexLastZero);
int sortedFunc(int* list, int count);
int searchIndex(int* list, int count, int* indexLastNegative, int* indexLastZero);
int printList(int* list, int count, int indexLastNegative, int indexLastZero);
void freeList(int* list);
int outputText(char* s);
int main() {
	int count, indexLastNegative=-1, indexLastZero=-1;
	if (inputCount(&count)) {
		outputText(ErrorIncorrectInput);
		return !OK;
	}
	int* list=(int*)mallocList(count);
	inputList(list, count);
	int result = solutionFunc(list, count , &indexLastNegative, &indexLastZero);
	printList(list, count, indexLastNegative, indexLastZero);
	freeList(list);
	return OK;
}
int inputCount(int* count) {
	printf("Enter count: ");
	return scanf("%i", count) == 0 || *count <= 0;
}

void* mallocList(int count) {
	return malloc(sizeof(int) * (int)count);
}

void* callocList(int count) {
	return calloc(count, sizeof(int));
}

int inputList(int* list, int count) {
	for (int i = 0; i < count; ++i) {
		printf("%i value: ", i);
		while (scanf("%i", &list[i]) == 0) {
			printf("Value not number\n%i value: ", i);
			scanf("%*[^\r^\n]");
		}
	}
	return OK;
}

int solutionFunc(int* list, int count, int* indexLastNegative, int* indexLastZero) {
	sortedFunc(list, count);
	searchIndex(list, count, indexLastNegative, indexLastZero);
	return OK;
}

int searchIndex(int* list, int count, int* indexLastNegative, int* indexLastZero) {
	for (int i = 0; i < count; ++i) {
		if (list[i] > 0) {
			break;
		}
		else if (list[i] < 0) {
			*indexLastNegative = i;
		}
		else {
			*indexLastZero = i;
		}
	}
	return OK;
}

int convertIntToUnsigned(int* list, int count) {
	for (int i = 0; i < count; ++i) {
		list[i] = (unsigned int)(list[i] + (unsigned int)pow(2.0,(double)sizeof(int)*8-1));//pow(2,sizeof(int)*8-1));
	}
	return OK;
}

int convertUnsignedToInt(unsigned* list, int count) {
	for (int i = 0; i < count; ++i) {
		list[i] = (int)(list[i] - (unsigned int)pow(2.0,(double)sizeof(int)*8-1));//pow(2, sizeof(int) * 8 - 1));
	}
	return OK;
}

int sortByByte(int* list, int count, int countByte) {
	int* c = (int*)callocList(257);
	for (int i = 0; i < count; ++i) {
		++c[list[i] /(unsigned)pow(256.0, countByte) % 256U + 1];
	}
	for (int i = 1; i < 257; ++i) {
		c[i] += c[i - 1];
	}
	unsigned int* auxiliaryList = (unsigned int*)mallocList(count);
	for (int i = 0; i < count; ++i) {
		auxiliaryList[c[list[i] / (unsigned)pow(256.0, countByte) % 256U]++] = list[i];
		/*printf("\n===========%i===============\n", i);
		for (int i = 0; i < count; ++i) {
			printf("%i, ", (int)(list[i] - (int)pow(2, sizeof(int) * 8 - 1)));
		}
		printf("\n///////////%i///////////////\n", i);
		for (int i = 0; i < count; ++i) {
			printf("%i, ", (int)(auxiliaryList[i] - (int)pow(2, sizeof(int) * 8 - 1)));
		}*/
	}
	//printf("\n===========end %i===============\n", countByte);
	for (int i = 0; i < count; ++i) {
		list[i] = auxiliaryList[i];
		//printf("%i, ", (int)(list[i] - (int)pow(2, sizeof(int) * 8 - 1)));
	}
	freeList((int*)auxiliaryList);
	freeList(c);
	return OK;
}

int sortedFunc(int* list, int count) {
	convertIntToUnsigned(list, count);
	for (int countByte = 0; countByte < sizeof(int); ++countByte) {
		sortByByte(list, count, countByte);
	}
	convertUnsignedToInt((unsigned*)list, count);
	return OK;
}

int printList(int* list, int count, int indexLastNegative, int indexLastZero) {
	printf("\n");
	if(indexLastZero==-1){indexLastZero=indexLastNegative;}
	if(indexLastNegative==-1){indexLastNegative=indexLastZero;}
	for (int i = count - 1; i > indexLastZero; --i) {
		printf("%i ", list[i]);
	}
	for (int i = indexLastNegative+1; i <= indexLastZero; ++i) {
		printf("%i ", list[i]);
	}
	for (int i = 0; i <= indexLastNegative; ++i) {
		printf("%i ", list[i]);
	}
	_getch();
	return OK;
}

void freeList(int* list) {
	free(list);
	list = NULL;
}

int outputText(char* s) {
	printf(s);
	_getch();
	return OK;
}
