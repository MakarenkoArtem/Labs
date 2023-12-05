#define Task 120
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
//#define FIELD_NAME(s,f) (sizeof((s*)0->f), #f)
//#define VAR_NAME(variable) (#variable)

#define OK 0
#define IndexOutOfRange -2
#define Error "Error"
#define MemoryError "Memory error"
#define ErrorIncorrectInput "Incorrect input"
#define OneSpaceRight ",!.?-)"
#define OneSpaceLeft "("


void* reallocList(void* str, int count, int sizeOfType);
void* mallocList(int count, int sizeOfType);
int outputText(char* s);
void freeTwoDStr(char** matrix, int rows);
void freeOneDStr(char* arr);
void freeTwoDArr(void** matrix, int rows);
void freeOneDArr(void* arr);
int inputCount(int* count);
void swap(void** a, void** b);
void freeStructList(void* structList);
#define LEN 255
#define WORKFILE "listCars.txt"
#define COUNTARGS 4
void outputNumListToFile(FILE* file, char** list, int n);

typedef struct {
    char brand[LEN];
    char model[LEN];
    int cost;
    int year;
}Car;

typedef struct {
    Car** cars;
    int size;
}Cars;

void printListCars(Cars* cars);
Cars* getCars();
int delCar(Cars* cars);
int outputStructToFile(FILE* file, Car* car);
void* delElem(void* str, int count, int index);
void freeStruct(Car* car);
int sortCosts(Car* a, Car* b);
int sortYears(Car* a, Car* b);
int sortBrands(Car* a, Car* b);
int sortModels(Car* a, Car* b);
Cars* sortCars(Cars* cars, int sortFunc(Car*, Car*));
int printCarsInFile(Cars* list);
void freeStructs(Cars* cars);
int printCars(Cars* list);

int main() {
    int c, size;
    FILE* file;
    Cars* list;
    char* str = (char*)mallocList(100, sizeof(char));
    do {
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            addCar();
            break;
        case 2:
            list = getCars();
            printListCars(list);
            freeStructs(list);
            break;
        case 3:
            printf("Sort by:");
            scanf("%s", str);
            str = lowerStr(stdStr(str, (char*)OneSpaceLeft, (char*)OneSpaceRight));
            list = getCars();
            if (compareStr(str, "brand")){
                sortCars(list, sortBrands);
            }
            else if (compareStr(str, "model")) {
                sortCars(list, sortModels);
            }
            else if (compareStr(str, "year")) {
                sortCars(list, sortYears);
            }
            else if (compareStr(str, "cost")) {
                sortCars(list, sortCosts);
            }
            else { outputText(ErrorIncorrectInput"\n");
            freeStructs(list);
            break;
            }
            printListCars(list);
            freeStructs(list);
            break;
        case 4:
            list = getCars();
            (delCar(list))?(outputText(ErrorIncorrectInput"\n")):(printCarsInFile(list));
            freeStructs(list);
            break;
        case 5:
            break;
        default:
            outputText(ErrorIncorrectInput);
            break;
        }
    } while (c != 5);
    return OK;
}

int printCarsInFile(Cars* list) {
    FILE* file = fopen(WORKFILE, "w");//"wb"
    for (int i = 0; i < list->size; outputStructToFile(file,list->cars[i++]));
    fclose(file);
    return OK;
}

Cars* sortCars(Cars* cars, int sortFunc(Car*,Car*)) {
    for (int i = 0; i < cars->size - 1; ++i) {
        for (int j = 1; j < cars->size-i; ++j) {
            if (!sortFunc(cars->cars[j - 1], cars->cars[j])) {
                swap((void**)(cars->cars+ j - 1), (void**)(cars->cars + j));
            }
        }
    }
    return cars;
}
int sortCosts(Car* a, Car* b) {
    return a->cost <= b->cost;
}
int sortYears(Car* a, Car* b) {
    return a->year<=b->year;
}
int sortBrands(Car* a, Car* b) {
    return lessOrEqualStr(a->brand, b->brand);
}

int sortModels(Car* a, Car* b){
    return lessOrEqualStr(a->model, b->model);
}

int delCar(Cars* cars) {
    int i = 0, count = 0, * l = (int*)mallocList(cars->size, sizeof(int));
    printf("\nBrand:");
    char* s = getStr();
    for (; i < cars->size; i++) {
        if (compareStr(s, cars->cars[i]->brand)) {
            l[count++] = i;// (*list) + i;
        }
    }
    i = 0;
    if (!count) {
        return !OK;
    }
    else if (count >1) {
        for (i = 0; i < count; printf("\n%s", cars->cars[l[i++]]->model));
        printf("\nModel:");
        char* s = getStr();
        for (i=0; i < count && !compareStr(s, cars->cars[l[i]]->model); ++i);
        if (i == count) {
            return !OK;
        }
    }
    swap((void**)(cars->cars + l[i]), (void**)(cars->cars + cars->size - 1));
            //delElem((void*)cars->cars, cars->size, i);
    freeStruct(cars->cars[--cars->size]);
    return OK;
}

void* delElem(void* list, int count, int index) {
    if (index < 0) {
        return (void*)Error;
    }
    else if (index >= count) {
        return (void*)IndexOutOfRange;
    }
    for (; index != count - 1; ((Car*)list)[index++] = ((Car*)list)[index + 1]);
    return (void*)list;
}
int addCar() {
    FILE* file = fopen(WORKFILE, "a");
    printf("\nBrand:");
    fprintf(file, "\n*)%s", getStr());
    printf("\nModel:");
    fprintf(file, "\n%s", getStr());
    printf("\nyear:");
    int c;
    scanf("%d", &c);
    fprintf(file, "\n%d", c);
    printf("\ncost:");
    scanf("%d", &c);
    fprintf(file, "\n%d", c);
    fclose(file);
    return OK;
}

Cars* getCars() {
    int c = 0;
    FILE* file = fopen(WORKFILE, "r");
    char** list = getListStrFromFile(file, &c);
    delThisStr(list, "", &c);
    Cars* cars = (Cars*)mallocList(1, sizeof(Cars));
    cars->size = 0;
    cars->cars = (Car**)mallocList(c / COUNTARGS, sizeof(Car*));
    for (int i = 0; i < c; ++i) {
        if (compareStr("*)", subStr(list[i], 0, 2))) {
            cars->cars[cars->size] = (Car*)mallocList(1, sizeof(Car));
            for (int gg = -1; cars->cars[cars->size]->brand[gg++] || !gg; cars->cars[cars->size]->brand[gg] = list[i][gg + 2]);
            for (int gg = -1; cars->cars[cars->size]->model[gg++] || !gg; cars->cars[cars->size]->model[gg] = list[i + 1][gg]);
            cars->cars[cars->size]->year = strToInt(list[i + 2]);
            cars->cars[cars->size++]->cost = strToInt(list[i + 3]);
            i += 3;
        }
    }
    freeTwoDStr(list, c);
    fclose(file);
    return cars;
}

void printListCars(Cars* cars) {
    for (int i = 0; i < cars->size;) {
        printf("\n%i.", ++i);
        outputStruct(cars->cars[i - 1]);
    }
}

int outputStructToFile(FILE* file, Car* car) {
    fprintf(file, "*)%s\n", car->brand);
    fprintf(file, "%s\n", car->model);
    fprintf(file, "%d\n", car->year);
    fprintf(file, "%d\n", car->cost);
    return OK;
}

int outputStruct(Car* car) {
    printf("brand:%s\n", car->brand);
    printf("model:%s\n", car ->model);
    printf("year:%d\n", car->year);
    printf("cost:%d$\n", car->cost);
    return OK;
}

void freeStruct(Car* car) {
    freeOneDArr((void*)car);
}

void freeStructs(Cars* cars) {
    for(int i=0;i<cars->size;freeStruct(cars->cars[i++]));
    freeOneDArr((void*)cars->cars);
    freeOneDArr((void*)cars);
}

void outputNumListToFile(FILE* file, char** list, int n) {
    for (int i = 0; i < n; ++i) {
        if (i) { fprintf(file, "\n"); }
        fprintf(file, "%d. %s", i + 1, list[i]);
    }
}

int outputText(char* s) {
    printf(s);
    return OK;
}

void freeTwoDStr(char** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDStr(char* arr) {
    free(arr);
}

void freeTwoDArr(void** matrix, int rows) {
    for (int i = 0; i < rows; ++i) {
        free(matrix[i]);
    }
    free(matrix);
}

void freeOneDArr(void* arr) {
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


