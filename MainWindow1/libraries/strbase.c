//#include<stdio.h>
#include"mystring.h"
#define OK 0
#define IndexOutOfRange -2
#define Error -1

char* deleteChar(char* str, int index) {
	if (index < 0) {
		return Error;
	}else if (index>=lenStr(str)){
  return IndexOutOfRange;
}
for(;str[index]; str[index++]=str[index+1]);
/*	do {
		str[begin] = str[begin+1];
	} while (str[begin++] != '\0');*/
	return str;
}
char* addChar(char* str, int index, char addCahr) {
	if (begin < 0) {
		return Error;
	}else if (begin>=lenStr(str)){
  return IndexOutOfRange;
}
	//str = (char*)realloc(str, (lenStr(str)+ lenStr(addStr)-1) * sizeof(char));
 int i=lenStr(str);
	for (; i!=index; str[i--+1]=str[i]);/* {
		int j = lenStr(str) + 1+i;
		while (j>begin){
			str[j] = str[j - 1];
			j--;
		}
		str[begin] = addStr[lenStr(addStr)-i-2];
	}*/
 str[index]=addChar;
	return str;
}

int lenStr(char* str) {
 int i=0;
 for(;str[i];++i);
	//int i = 0;
	//while (str[i++] != '\0') {}
	return i;
}

char* subStr(char* str, int start, int end) {
	// Âûäåëÿåì ïàìÿòü äëÿ íîâîé ñòðîêè
	char* slice = (char*)malloc((end - start + 1) * sizeof(char));
	for (int i=start; i < end; ++i) {
		slice[i-start] = str[i];
	}
 slice[end - start] = '\0';
	return slice;
}

int compareStr(char* a, char* b) {
 int i=0;
	for (; a[i] && a[i]==b[i]; ++i);
	return !(a[i] || b[i]);
}

char** split(char* str, char* s, int* n) {
	int i = 0, c=0, lenSplitStr=lenStr(s);
	*n = 0;
 char** list = (char**)malloc(sizeof(void*)*lenStr(str)/2);
	char* text=(char*)malloc(sizeof(char)*lenStr(str)+1);
	do {
		if (comparedStr(subStr(str,i,i+lenSplitStr), s) || !str[i]) {
   text[c++]='\0';
   list[*n] = (char*)malloc(sizeof(char) * c);
			list[*n++] = text;
			c = 0;
   i+=lenSplitStr;
		}
		else {
			text = str[i];
		}
	}while(str[i++]);
free(text);
	return list;
}