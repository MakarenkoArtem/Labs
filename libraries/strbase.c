#include<stdio.h>
#define OK 0
#define Error -1

char* moveStr(char* str, int begin) {
	if (begin < 0) {
		return Error;
	}
	do {
		str[begin] = str[begin+1];
		begin++;
	} while (str[begin - 1] != '\0');
	return str;
}
char* addChar(char* str, int begin, char* addStr) {
	if (begin < 0) {
		return Error;
	}
	str = (char*)realloc(str, (lenStr(str)+ lenStr(addStr)-1) * sizeof(char));
	for (int i = 0; i < lenStr(addStr)-1; ++i) {
		int j = lenStr(str) + 1+i;
		while (j>begin){
			str[j] = str[j - 1];
			j--;
		}
		str[begin] = addStr[lenStr(addStr)-i-2];
	}
	return str;
}

int lenStr(char* str) {
	int i = 0;
	while (str[i++] != '\0') {}
	return i;
}

char* sliceStr(char* str, int start, int end) {
	// Выделяем память для новой строки
	char* slice = malloc((end - start + 1) * sizeof(char));
	for (int i = start; i < end; ++i) {
		slice[i-start] = str[i];
	}
	slice[end - start] = '\0';
	return slice;
}

int compareStr(char* a, char* b) {
	if (lenStr(a) != lenStr(b)) {
		return OK;
	}
	for (int i = 0; i < lenStr(a); ++i) {
		if (a[i] != b[i]) {
			return OK;
		}
	}
	return !OK;
}

char** split(char* str, char s, int* n) {
	int i = 0, c=0;
	*n = 1;
 	char** list = (char**)malloc(sizeof(void*));
	list[*n - 1] = (char*)malloc(sizeof(char) * 10);
	//char* text=(char*)malloc(sizeof(char)*100);
	while (str[i] != '\0') {
		if (str[i] == s) {
			//list[(*n) - 1] = text;
			//text = (char*)malloc(sizeof(char) * 100);
			list = (char**)realloc(list, ++(*n) * sizeof(void*));
			list[*n-1] = (char*)malloc(sizeof(char) * 100);
			c = 0;
		}
		else {
			list[*n - 1][c++] = str[i];
			list[*n - 1][c] = '\0';
		}
		i++;
	}
	return list;
}