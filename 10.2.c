#define _CRT_SECURE_NO_WARNINGS
//#include "stdafx.h"
#include<stdio.h>
//#include<conio.h>
#include<math.h>
#include<stdlib.h>
#include"libraries/mystring.h"
#include <locale.h>

#define min(a, b) (((a)<(b))?(a):(b))
#define max(a, b) (((a)>(b))?(a):(b))
//#define FIELD_NAME(s,f) (sizeof((s*)0->f), #f)
//#define VAR_NAME(variable) (#variable)

#define OK 0
#define IndexOutOfRange -2
#define Error "Error"
#define MemoryError "Memory error"
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight ",!.?-)"
#define OneSpaceLeft "("


void *reallocList(void *str, int count, int sizeOfType);

void *mallocList(int count, int sizeOfType);

int outputText(char *s);

void freeTwoDStr(char **matrix, int rows);

void freeOneDStr(char *arr);

void freeTwoDArr(void **matrix, int rows);

void freeOneDArr(void *arr);

int inputCount(int *count);

void swap(void **a, void **b);

void freeStructList(void *structList);


typedef struct{
    char* lastname;
    int* marks;
    int countMarks;
    float average;
}Student;
typedef struct{
    Student** list;
    int count;
}StudentsList;
#define BADMARKSCOUNT 2
#define VERYGOOD 5
#define GOOD 4
#define NORM 3
#define BAD 2
#define VERYBAD 1
#define COUNT 4
int inputStudents(StudentsList* list);
int solutionFunc(StudentsList* list, StudentsList* first, StudentsList* second, StudentsList* third, StudentsList* fourth);
int outputStruct(StudentsList* list);
int sortStruct(StudentsList* list);
int countInList(int* list, int len, int value);
void** delElem(void** str, int count, int index);
void freeStruct(void* student);
void freeStructList(void* structList);

int main() {
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    int count;
    if (inputCount(&count)) {
        outputText(ErrorIncorrectInput);
        getchar();
        return !OK;
    }
    StudentsList* list=(StudentsList*)mallocList(1, sizeof(StudentsList));
    list->list = (Student**)mallocList(count, sizeof(Student*));
    list->count = count;
    if (inputStudents(list)) {
        outputText(ErrorIncorrectInput);
        getchar();
        return !OK;

    }
    StudentsList* first = (StudentsList*)mallocList(1, sizeof(StudentsList));
    StudentsList* second = (StudentsList*)mallocList(1, sizeof(StudentsList));
    StudentsList* third = (StudentsList*)mallocList(1, sizeof(StudentsList));
    StudentsList* fourth = (StudentsList*)mallocList(1, sizeof(StudentsList));
    if (solutionFunc(list, first, second, third, fourth) || outputStruct(first) || outputStruct(second) || outputStruct(third) || outputStruct(fourth)) {
        outputText("\n"Error);
    }
    freeStructList((void*)list);
    first->count = 0;
    second->count = 0;
    third->count = 0;
    fourth->count = 0;
    freeStructList((void*)first);
    freeStructList((void*)second);
    freeStructList((void*)third);
    freeStructList((void*)fourth);
    getchar();
    return OK;
}

int inputStudents(StudentsList* list) {
    for (int i = 0; i < list->count; ++i) {
        while (fgetc(stdin) != '\n');
        Student* p= (Student*)mallocList(1, sizeof(Student));
        p->lastname = getStr();
        p->countMarks = COUNT;
        p->marks = (int*)mallocList(p->countMarks, sizeof(int));
        p->average = 0;
        list->list[i] = p;
        for (int j = 0; j < p->countMarks; ++j) {
            if (scanf("%i", p->marks+j) != 1 || p->marks[j]>VERYGOOD || p->marks[j]<VERYBAD) {
                return !OK;
            }
            p->average += p->marks[j];
        }
        p->average /= p->countMarks;
    }
    return OK;
}

int valueInList(int* list, int count, int value){
    int i = 0;
    for (; i < count && list[i] != value; i++);
    return count != i;
}

int countInList(int* list, int len, int value) {
    int count = 0;
    for (int i = 0; i < len; count += list[i++] == value);
    return count;
}

int sortStruct(StudentsList* list) {
    for (int i = 0; i < list->count - 1; ++i) {
        for (int j = i + 1; j < list->count; ++j) {
            if (!lessOrEqualStr(list->list[j - 1]->lastname, list->list[j]->lastname)) {
                swap((void**)list->list + j - 1, (void**)list->list + j);
            }
        }
    }
    return OK;
}

int outputStruct(StudentsList* list) {
    sortStruct(list);
    for (int i = 0; i < list->count; ++i) {
        printf("\n%s\n", (list->list[i]->lastname));
        for (int j = 0; j < list->list[i]->countMarks; printf("%i ", list->list[i]->marks[j++]));
        printf("\n%.2f\n", (list->list[i]->average));
    }
    return OK;
}

int solutionFunc(StudentsList* list, StudentsList* first, StudentsList* second, StudentsList* third, StudentsList* fourth) {
    first->list = (Student**)mallocList(list->count, sizeof(Student*));
    second->list = (Student**)mallocList(list->count, sizeof(Student*));
    third->list = (Student**)mallocList(list->count, sizeof(Student*));
    fourth->list = (Student**)mallocList(list->count, sizeof(Student*));
    first->count = 0;
    second->count = 0;
    third->count = 0;
    fourth->count = 0;
    for (int i = 0; i < list->count; ++i) {
        if (valueInList(list->list[i]->marks, list->list[i]->countMarks, BAD)) {
            if (countInList(list->list[i]->marks, list->list[i]->countMarks, BAD) > BADMARKSCOUNT) {
                freeStruct((void*)list->list[i]);
                delElem((void**)&list->list, list->count--, i--);
            }
            else {
                fourth->list[fourth->count++] = list->list[i];
            }
        }
        else if(valueInList((*list->list[i]).marks, list->list[i]->countMarks, NORM)) {
            third->list[third->count++] = list->list[i];
        }
        else if(valueInList((*list->list[i]).marks, list->list[i]->countMarks, GOOD)) {
            second->list[second->count++] = list->list[i];
        }
        else if (!valueInList(list->list[i]->marks, list->list[i]->countMarks, VERYBAD)) {
            first->list[first->count++] = list->list[i];
        }
    }
    return (list->count >= 0) ? (OK) : ((int)!OK);
}

void freeStruct(void* student) {
    freeOneDStr(((Student*)student)->lastname);
    freeOneDStr(((Student*)student)->marks);
    freeOneDArr(student);
}

void freeStructList(void* structList) {
    for (int i = 0; i < ((StudentsList*)structList)->count;) {
        freeOneDArr((void*)((StudentsList*)structList)->list[i++]);
    }
    freeOneDArr(structList);
}

void** delElem(void** str, int count, int index) {
    if (index < 0) {
        return (void*)Error;
    }
    else if (index >= count) {
        return (void*)IndexOutOfRange;
    }
    for (; index != count - 1;*((Student*)*str + index++) = *((Student*)*str + index + 1));
    return str;
}


int outputText(char *s) {
    printf(s);
    return OK;
}

void freeTwoDStr(char **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDStr(char *arr) {
    free(arr);
}

void freeTwoDArr(void **matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDArr(void *arr) {
    free(arr);
}

int inputCount(int *count) {
    printf("Enter count: ");
    return scanf("%i", count) == 0 || *count <= 0;
}

void *reallocList(void *str, int count, int sizeOfType) {
    return realloc(str, sizeOfType * count);
}

void *mallocList(int count, int sizeOfType) {
    return malloc(sizeOfType * count);
}

void swap(void **a, void **b) {
    void *tmp = *a;
    *a = *b;
    *b = tmp;
}
