#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries\mystring.h"
#include <locale.h>

#define min(a,b) (((a)<(b))?(a):(b))
#define max(a,b) (((a)>(b))?(a):(b))

#define OK 0
#define Error "Error"
#define MemoryError "Memory error"
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight ",!.?-)"
#define OneSpaceLeft "("


void* reallocList(void* str, int count, int sizeOfType);
void* mallocList(int count, int sizeOfType);
int outputText(char* s);
void freeTwoDArr(char** matrix, int rows);
void freeOneDArr(char* arr);
int inputCount(int* count);
void swap(void** a, void** b);
typedef struct{
    char* lastname;
    int* marks;
    int countMarks;
}Student;
typedef struct{
    Student** list;
    int count;
}StudentsList;


int inputStudents(StudentsList* list);
int solutionFunc(StudentsList* list, StudentsList* first, StudentsList* second, StudentsList* third, StudentsList* fourth);
int outputStruct(StudentsList* list);
int sortStruct(StudentsList* list);

int main() {
    setlocale(LC_ALL, "Russian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int count;
    if (inputCount(&count)) {
        outputText(ErrorIncorrectInput);
        _getch();
        return !OK;
    }
    StudentsList list;
    list.list = (Student**)mallocList(count, sizeof(Student*));
    list.count = count;
    if (inputStudents(&list)) {
        outputText(ErrorIncorrectInput);
        _getch();
        return !OK;

    }
    StudentsList first = { NULL, 0 };// = (struct Student*)mallocList(count, sizeof(struct Student));
    StudentsList second = { NULL, 0 };// = (struct Student*)mallocList(count, sizeof(struct Student));
    StudentsList third = { NULL, 0 };// = (struct Student*)mallocList(count, sizeof(struct Student));
    StudentsList fourth = { NULL, 0 };// = (struct Student*)mallocList(count, sizeof(struct Student));
    if (solutionFunc(&list, &first, &second, &third, &fourth) || outputStruct(&first) || outputStruct(&second) || outputStruct(&third) || outputStruct(&fourth)) {
        outputText("\n"Error);
    }
    _getch();
    return OK;
}

int inputStudents(StudentsList* list) {
    for (int i = 0; i < list->count; ++i) {
        while (fgetc(stdin) != '\n');
        Student* p= (Student*)mallocList(1, sizeof(Student));
        p->lastname = getStr();
        p->marks = (int*)mallocList(5, sizeof(int));
        p->countMarks = 5;
        list->list[i] = p;
        for (int j = 0; j < 5; ++j) {
            if (scanf("%i", p->marks+j) != 1 || p->marks[j]>5 || p->marks[j]<1) {
                return !OK;
            }
        }
    }
    return OK;
}
int valueInList(int* list, int count, int value){
    int i = 0;
    for (; i < count && list[i] != value; i++);
    return count != i;
}

int sortStruct(StudentsList* list) {
    for (int i = 0; i < list->count - 1; ++i) {
        for (int j = i + 1; j < list->count; ++j) {
            if (!lessOrEqualStr(list->list[j - 1]->lastname, list->list[j]->lastname)) {
                swap(list->list + j - 1, list->list + j);
            }
        }
    }
    return OK;
}

int outputStruct(StudentsList* list) {
    sortStruct(list);
    for (int i = 0; i < list->count; ++i) {
        printf("\n\n%s\n", (list->list[i]->lastname));
        for (int j = 0; j < list->list[i]->countMarks; printf("%d ", list->list[i]->marks[j++]));
    }
    return OK;
}

int solutionFunc(StudentsList* list, StudentsList* first, StudentsList* second, StudentsList* third, StudentsList* fourth) {
    first->list = (Student**)mallocList(list->count, sizeof(Student*));
    second->list = (Student**)mallocList(list->count, sizeof(Student*));
    third->list = (Student**)mallocList(list->count, sizeof(Student*));
    fourth->list = (Student**)mallocList(list->count, sizeof(Student*));
    for (int i = 0; i < list->count; ++i) {
        if (valueInList(list->list[i]->marks, list->list[i]->countMarks, 2)) {
            fourth->list[fourth->count++] = list->list[i];
        }
        else if(valueInList((*list->list[i]).marks, list->list[i]->countMarks, 3)) {
            third->list[third->count++] = list->list[i];
        }
        else if(valueInList((*list->list[i]).marks, list->list[i]->countMarks, 4)) {
            second->list[second->count++] = list->list[i];
        }
        else if (!valueInList(list->list[i]->marks, list->list[i]->countMarks, 1)) {
            first->list[first->count++] = list->list[i];
        }
    }
    return (list->count >= 0) ? (OK) : ((int)!OK);
}

int outputText(char* s) {
    printf(s);
    return OK;
}

void freeTwoDArr(char** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDArr(char* arr) {
    free(arr);
}

int inputCount(int* count) {
    printf("Enter count: ");
    return scanf("%i", count) == 0 || *count <= 0;
}

void* reallocList(void* str, int count, int sizeOfType) {
    return realloc(str, sizeOfType * count);
}

void* mallocList(int count, int sizeOfType) {
    return malloc(sizeOfType * count);
}

void swap(void** a, void** b) {
    void* tmp = *a;
    *a = *b;
    *b = tmp;
}
