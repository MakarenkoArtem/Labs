#include "mystring.h"

#define OK 0
#define Error -1
#define IndexOutOfRange -2

static void* reallocList(void* str, int count, int sizeOfType) {
	return realloc(str, sizeOfType * count);
}


static void* mallocList(int count, int sizeOfType) {
	return malloc(sizeOfType * count);
}

char* createNewString(int count){
  char* str = mallocList(count, sizeof(char));
  *str='\0';
  return str;
}

char* addStr(char* str, char* addStr){
    char *p = str;
    str += lenStr(str);
    for(;*addStr;*(str++)=*addStr++);
    *str = '\0';
    return p;
}
char* addStrOnIndex(char* str, char* addStr, int index){
    char *p = str;
    int lenstr = lenStr(str), lenadd = lenStr(addStr);
    for(int i= 0;i<=lenadd;str[lenstr+lenadd-(i++)]=str[lenstr-i]);
    str += index;
    for(;*addStr;*(str++)=*(addStr++));
    return p;
}

char* delChar(char* str, int index) {
	if (index < 0) {
		return (char*)Error;
	}else if (index>=lenStr(str)){
        return (char*)IndexOutOfRange;
    }
	for(;str[index];str[index++]=str[index+1]);
	return str;
}
char* addChar(char* str, int index, char addChar) {
    if (index < 0) {
        return (char*)Error;
    }else if (index>=lenStr(str)){
        return (char*)IndexOutOfRange;
    }
    int i = lenStr(str);
    for(;i!=index;str[i--+1]=str[i]);
    str[index]=addChar;
	return str;
}

int lenStr(char* str) {
	int i = -1;
	for(;str[++i];){}
	return i;
}

char* subStr(char* str, int start, int end) {
	// �������� ������ ��� ����� ������
	char* slice = (char*)mallocList(end - start + 1, sizeof(char));
	for (int i = start; i < end; ++i) {
		slice[i-start] = str[i];
	}
	slice[end - start] = '\0';
	return slice;
}

int compareStr(char* a, char* b) {
    int i=0;
    for(;a[i] && a[i]==b[i];++i);
    return !(a[i] || b[i]);
}


char** split(char* str, char* s, int* n) {
	int i = 0, c=0, lenSplitStr= lenStr(s);
	*n = 0;
 	char** list = (char**)mallocList(lenStr(str)/2+1,sizeof(void*));
	do{
        if(compareStr(subStr(str,i,i+lenSplitStr), s) || !str[i]){
            list[*n]=(char*) mallocList(c+1, sizeof(char));
            list[(*n)++]=subStr(str, i-c, i);
            c=0;
        }else{c++;}
    }while(str[i++]);
	return list;
}

char* charInSyms(char s, char* syms){
    for(;*syms&&*syms!=s;++syms);
    return *syms==s?syms:0;
}

char* replace(char* str, char* lastValue, char* newValue, int count){
    int k,h, i = 0, lenLastValue= lenStr(lastValue), lenNewValue = lenStr(newValue);
    do{
        if(compareStr(subStr(str,i,i+lenLastValue), lastValue)){
            --count;
            k = lenLastValue-lenNewValue;
            if(k>=0){
                for(int j=0;j<lenNewValue;str[i+j++]=newValue[j]);
                for(;k--; delChar(str, i+lenNewValue));
            }
            if(k<0){
                k=-k;
                h = k;
                for(;h; addChar(str, i, newValue[h--]));
                for(int j=k;j<k+lenLastValue;str[i+j++]=newValue[j]);
            }}
    }while(str[++i] && count);
    return str;
}

char* join(char** list, int count, char* joiner){
    int sizeStr = lenStr(joiner)*(count-1)+1;
    for(int i =0;i<count;sizeStr+=lenStr(list[i++]));
    char* str = createNewString(sizeStr);
    int n=0;
    for(int i=0;i<count;i++){
        addStr(str+n, list[i]);
        n+= lenStr(list[i]);
        if (i+1< count){
            addStr(str+n, joiner);
            n+=lenStr(joiner);
        }
    }
    return str;
}