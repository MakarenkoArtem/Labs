#define Task 120
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


#if Task == 81

int main() {
    char* str = getStr();
    if (str == NULL) {
        outputText(MemoryError"\n");
        getchar();
        return !OK;
    }
    outputText("|");
    outputText(str);
    outputText("|\n|");
    outputText(stdStr(str, (char*)OneSpaceLeft, (char*)OneSpaceRight));
    outputText("|");
    freeOneDStr(str);
    getchar();
    return OK;
}



#elif Task == 82
char** solutionFunc(char*** list, char* a, char* b, int count);
int inputStrings(char** str, int count);
int outputLists(char** list, char** anotherList, int count);

int main() {
    int count;
    if (inputCount(&count)) {
        outputText(ErrorIncorrectInput);
        getchar();
        return !OK;
    }
    char** list = (char**)mallocList(count, sizeof(void*));
    if (inputStrings(&list, count)) {
        outputText(MemoryError"\n");
        getchar();
        return !OK;
    }
    char *a = getStr(), *b = getStr();
    if (a==NULL || b==NULL) {
        outputText(MemoryError"\n");
        getchar();
        return !OK;
    }
    char** answerList = solutionFunc(&list, a, b, count);
    if (answerList == (char**)!OK || outputLists(list, answerList, count) == (char**)!OK) {
        outputText(Error"\n");
        getchar();
        return !OK;
    }
    getchar();
    return OK;
}

int inputStrings(char*** str, int count) {
    while (fgetc(stdin) != '\n');
    for (int i = 0; i < count; ++i) {
        (*str)[i] = getStr();
        if ((*str)[i] == NULL) {
            return !OK;
        }
    }
    return OK;
}

char** solutionFunc(char*** list, char* a, char* b, int count) {
    int n = 0;
    stdStr(a, (char*)OneSpaceLeft, (char*)OneSpaceRight);
    stdStr(b, (char*)OneSpaceLeft, (char*)OneSpaceRight);
    char** answerList = (char**)malloc(count * sizeof(void*));
    for (int k = 0; k < count; k++) {
        stdStr((*list)[k], (char*)OneSpaceLeft, (char*)OneSpaceRight);
        char** listStr = split((*list)[k], " ", &n);
        if (n == 3) {
            listStr[2] = (char*)reallocList(listStr[2], max(lenStr(listStr[2])+1, (lenStr(listStr[2]) / lenStr(a) + 1) * lenStr(b) + 1), sizeof(char));
            listStr[2] = replace((listStr[2] + 1), a, b, -1) - 1;
            answerList[k] = join(listStr, 3, " ");
        }
        else {
            answerList[k] = "It is not FIO";
        }
        freeTwoDArr(listStr, n);
    }
    return (count>=0)?(answerList):((char**)!OK);
}

int outputLists(char** list, char** anotherList, int count) {
    for (int i = 0; i < count; i++) {
        outputText("%s\n%s\n", list[i], anotherList[i]);
    }
    return (count >= 0) ? (OK) : ((int)!OK);
}

#elif Task == 91

int solutionFunc(char* str, char*** listWords, int** listCounter, int* count);
int outputLists(char** listWords, int* listCounter, int count);
void sortByCounts(char** words, int* counters, int count);

int main() {
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    char **listWords,*str = getStr();
    int count = 0, *listCounter;
    if (!solutionFunc(str, &listWords, &listCounter, &count) && !outputLists(listWords, listCounter, count)) {
    }
    else {
        outputText("\n"Error);
        getchar();
        return !OK;
    }
    freeOneDStr(str);
    freeTwoDArr(listWords, count);
    freeOneDArr((void*)listCounter);
    getchar();
    return OK;
}

int solutionFunc(char* str, char*** listWords, int** listCounter, int* count) {
    int n, j;
    delSymbols(str, (char*)OneSpaceRight""OneSpaceLeft);
    stdStr(lowerStr(str), (char*)OneSpaceLeft, (char*)OneSpaceRight);
    char** listStr = split(str, " ", &n);
    *listWords = (char**)mallocList(n, sizeof(char*));
    *listCounter = (int*)mallocList(n, sizeof(int));
    for (int i = 0; i < n; ++i) {
        for (j = 0; j < *count && !compareStr((*listWords)[j], listStr[i]); ++j);
        if (*count == j) {
            (*listWords)[(*count)++] = copyStr(listStr[i]);
            (*listCounter)[j] = 0;
        }
        ++(*listCounter)[j];
    }
    sortByCounts(*listWords, *listCounter, *count);
    freeTwoDStr(listStr, n);
    return OK;
}

void swapInt(int* a, int*b){
    int tmp = *a;
    *a=*b;
    *b=tmp;
}

void sortByCounts(char** words, int* counters, int count) {
    for (int i = 0; i < count - 1; ++i) {
        for (int j =1; j < count-i; ++j) {//(int j = i + 1; j < count; ++j) {
            if (*(counters + j - 1)< *(counters + j)) {
                swap((void**)words + j - 1, (void**)words + j);
                swapInt(counters + j - 1, counters + j);
            }
        }
    }
}

int outputLists(char** listWords, int* listCounter, int count) {
    for (int i = 0; i < count; ++i) {
        printf("%s: %i\n", listWords[i], listCounter[i]);
    }
    return OK;
}


#elif Task == 92
int solutionFunc(char* str, int length, char*** listStr, int* counter);

int main() {
    setlocale(LC_ALL, "Russian");
    //SetConsoleCP(1251);
    //SetConsoleOutputCP(1251);
    char** listRows;
    int counter, length;
    char* str = (char*)mallocList(300, sizeof(char));
    gets(str);
    if (inputCount(&length)) {
        outputText(ErrorIncorrectInput);
        getchar();
        return !OK;
    }
    if (!solutionFunc(str, length, &listRows, &counter) && !outputText(join(listRows, counter, "\n"))) {
    }
    else {
        outputText("\n"Error);
    }
    freeTwoDStr(listRows, counter);
    freeOneDStr(str);
    getchar();
    return OK;
}

int solutionFunc(char* str, int length, char*** listRows, int* counter) {
    stdStr(str, (char*)OneSpaceLeft, (char*)OneSpaceRight);
    int n, h, lenRow, lenNewWord, cntWordsRow=0;
    *counter = 0;
    char** listStr = split(str, " ", &n);

    *listRows = (char**)mallocList(n, sizeof(char*));
    char *spaces, ** helpRow = (char**)mallocList(lenStr(str)+1, sizeof(char*));

    lenRow = lenStr(listStr[0]);
    helpRow[cntWordsRow++] = listStr[0];

    for (int i = 1; i <= n; ++i) {
        lenNewWord = lenStr(listStr[i%n]);
        if (length < lenRow + lenNewWord + 1 || i==n) {
            if (cntWordsRow == 1) {
                if (lenStr(helpRow[0]) > length) {
                    (*listRows)[(*counter)++] = subStr(helpRow[0], 0, length);
                    helpRow[0] = subStr(helpRow[0], length, lenStr(helpRow[0]));
                    lenRow -= length;
                    --i;
                    continue;
                }
                else {
                    (*listRows)[(*counter)++] = copyStr(helpRow[0]);
                }
            }
            else {
                h = (length - lenRow) / (cntWordsRow - 1);
                spaces=createNewString(h+1, ' ');
                (*listRows)[*counter] = (char*)reallocList(join(helpRow, cntWordsRow, spaces), length+1,sizeof(char));
                freeOneDStr(spaces);
                spaces=createNewString(h+2, ' ');
                replace((*listRows)[(*counter)++], subStr(spaces, 0, h+1), spaces, length - lenRow - (cntWordsRow - 1) * h);
                freeOneDStr(spaces);
            }
            if (i != n) {
                lenRow = lenNewWord;
                cntWordsRow = 0;
                helpRow[cntWordsRow++] = listStr[i];
            }
        }
        else {
            lenRow += lenNewWord + 1;
            helpRow[cntWordsRow++] = listStr[i];
        }
    }
    freeOneDStr(helpRow);
    freeTwoDStr(listStr, n);
    return OK;
}
#elif Task == 101
typedef struct {
    char* lastname;
    int* marks;
    int countMarks;
}Student;
typedef struct {
    Student** list;
    int count;
}StudentsList;


int inputStudents(StudentsList* list);
int solutionFunc(StudentsList* list, StudentsList* first, StudentsList* second, StudentsList* third, StudentsList* fourth);
int outputStruct(StudentsList* list);
int sortStruct(StudentsList* list);
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
    StudentsList* list = (StudentsList*)mallocList(1, sizeof(StudentsList));
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
        Student* p = (Student*)mallocList(1, sizeof(Student));
        p->lastname = getStr();
        p->countMarks = 4;
        p->marks = (int*)mallocList(p->countMarks, sizeof(int));
        list->list[i] = p;
        for (int j = 0; j < p->countMarks; ++j) {
            if (scanf("%i", p->marks + j) != 1 || p->marks[j] > 5 || p->marks[j] < 1) {
                return !OK;
            }
        }
    }
    return OK;
}
int valueInList(int* list, int count, int value) {
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
    first->count = 0;
    second->count = 0;
    third->count = 0;
    fourth->count = 0;
    for (int i = 0; i < list->count; ++i) {
        if (valueInList(list->list[i]->marks, list->list[i]->countMarks, 2)) {
            fourth->list[fourth->count++] = list->list[i];
        }
        else if (valueInList((*list->list[i]).marks, list->list[i]->countMarks, 3)) {
            third->list[third->count++] = list->list[i];
        }
        else if (valueInList((*list->list[i]).marks, list->list[i]->countMarks, 4)) {
            second->list[second->count++] = list->list[i];
        }
        else if (!valueInList(list->list[i]->marks, list->list[i]->countMarks, 1)) {
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
#elif Task == 102
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

#elif Task == 111
#define RFILE "input.txt"
#define WFILE "output.txt"
void outputNumListToFile(FILE* file, char** list, int n);

int main() {
    FILE* file = fopen(RFILE, "r"), *wfile= fopen(WFILE, "w");
    int k=0;
    char** list = getListStrFromFile(file, &k);
    delThisStr(list, "", &k);
    outputNumListToFile(wfile,list, k);
    freeTwoDStr(list, k);
    fclose(file);
    fclose(wfile);
    getchar();
    return OK;
}

void outputNumListToFile(FILE* file, char** list, int n) {
    for (int i = 0; i < n; ++i){
        if (i) { fprintf(file, "\n"); }
        fprintf(file, "%d. %s", i+1, list[i]);
    }
}
#elif Task == 112
#define LEN 255
#define WORKFILE "listCars.txt"
#define COUNTARGS 4
#define ADD 1
#define OUTPUT 2
#define SORT 3
#define DEL 4
#define EXITVAL 5

void outputNumListToFile(FILE *file, char **list, int n);

typedef struct {
    char brand[LEN];
    char model[LEN];
    int cost;
    int year;
} Car;

typedef struct {
    Car **cars;
    int size;
} Cars;

void printListCars(Cars *cars);

Cars *getCars();

int delCar(Cars *cars);

int outputStructToFile(FILE *file, Car *car);

void *delElem(void *str, int count, int index);

void freeStruct(Car *car);

int sortCosts(Car *a, Car *b);

int sortYears(Car *a, Car *b);

int sortBrands(Car *a, Car *b);

int sortModels(Car *a, Car *b);

Cars *sortCars(Cars *cars, int sortFunc(Car *, Car *));

int printCarsInFile(Cars *list);

void freeStructs(Cars *cars);

void swapCars(Car **a, Car **b);

int printCars(Cars *list);

int addCar();

int outputStruct(Car *car);
int workFunc(int c);
Car getNewCar();

int main() {
    int c;
    do {
        scanf("%d", &c);
        workFunc(c);
    } while (c != 5);
    return OK;
}

int workFunc(int c) {
    int size;
    FILE *file;
    Cars *list;
    char *str = (char *) mallocList(100, sizeof(char));
    switch (c) {
        case ADD:
            addCar(getNewCar());
            break;
        case OUTPUT:
            list = getCars();
            printListCars(list);
            freeStructs(list);
            break;
        case SORT:
            printf("Sort by:");
            scanf("%s", str);
            str = lowerStr(stdStr(str, (char *) OneSpaceLeft, (char *) OneSpaceRight));
            list = getCars();
            if (compareStr(str, "brand")) {
                sortCars(list, sortBrands);
            } else if (compareStr(str, "model")) {
                sortCars(list, sortModels);
            } else if (compareStr(str, "year")) {
                sortCars(list, sortYears);
            } else if (compareStr(str, "cost")) {
                sortCars(list, sortCosts);
            } else {
                outputText(ErrorIncorrectInput"\n");
                freeStructs(list);
                break;
            }
            printListCars(list);
            freeStructs(list);
            break;
        case DEL:
            list = getCars();
            (delCar(list)) ? (outputText(ErrorIncorrectInput"\n")) : (printCarsInFile(list));
            freeStructs(list);
            break;
        case EXITVAL:
            break;
        default:
            outputText(ErrorIncorrectInput);
            break;
    }
}

int printCarsInFile(Cars *list) {
    FILE *file = fopen(WORKFILE, "w");//"wb"
    for (int i = 0; i < list->size; outputStructToFile(file, list->cars[i++]));
    fclose(file);
    return OK;
}

Cars *sortCars(Cars *cars, int sortFunc(Car *, Car *)) {
    for (int i = 0; i < cars->size - 1; ++i) {
        for (int j = 1; j < cars->size - i; ++j) {
            if (!sortFunc(cars->cars[j - 1], cars->cars[j])) {
                swap((void **) (cars->cars + j - 1), (void **) (cars->cars + j));
            }
        }
    }
    return cars;
}

int sortCosts(Car *a, Car *b) {
    return a->cost <= b->cost;
}

int sortYears(Car *a, Car *b) {
    return a->year <= b->year;
}

int sortBrands(Car *a, Car *b) {
    return lessOrEqualStr(a->brand, b->brand);
}

int sortModels(Car *a, Car *b) {
    return lessOrEqualStr(a->model, b->model);
}

void swapCars(Car **a, Car **b) {
    Car *tmp = *a;
    *a = *b;
    *b = tmp;
}

int delCar(Cars *cars) {
    int i = 0, count = 0, *l = (int *) mallocList(cars->size, sizeof(int));
    printf("\nBrand:");
    char *s = getStr();
    for (; i < cars->size; i++) {
        if (compareStr(s, cars->cars[i]->brand)) {
            l[count++] = i;// (*list) + i;
        }
    }
    i = 0;
    if (!count) {
        return !OK;
    } else if (count > 1) {
        for (i = 0; i < count; printf("\n%s", cars->cars[l[i++]]->model));
        printf("\nModel:");
        char *s = getStr();
        for (i = 0; i < count && !compareStr(s, cars->cars[l[i]]->model); ++i);
        if (i == count) {
            return !OK;
        }
    }
    swap((void **) (cars->cars + l[i]), (void **) (cars->cars + cars->size - 1));
    //delElem((void*)cars->cars, cars->size, i);
    freeStruct(cars->cars[--cars->size]);
    return OK;
}

void *delElem(void *list, int count, int index) {
    if (index < 0) {
        return (void *) Error;
    } else if (index >= count) {
        return (void *) IndexOutOfRange;
    }
    for (; index != count - 1; ((Car *) list)[index++] = ((Car *) list)[index + 1]);
    return (void *) list;
}
Car getNewCar(){
    Car car;
    printf("\nBrand:");
    char *c =getStr();
    int i=0;
    for(;*c;car.brand[i++]=*c++);
    car.brand[i]=0;
    printf("\nModel:");
    c =getStr();
    for(i=0;*c;car.model[i++]=*c++);
    car.model[i]=0;
    printf("\nyear:");
    scanf("%d", &(car.year));
    printf("\ncost:");
    scanf("%d", &(car.cost));
    return car;
}
int addCar(Car car) {
    FILE *file = fopen(WORKFILE, "a");
    fprintf(file, "\n*)%s", car.brand);
    fprintf(file, "\n%s", car.model);
    fprintf(file, "\n%d", car.year);
    fprintf(file, "\n%d", car.cost);
    fclose(file);
    return OK;
}

Cars *getCars() {
    int c = 0;
    FILE *file = fopen(WORKFILE, "r");
    char **list = getListStrFromFile(file, &c);
    delThisStr(list, "", &c);
    Cars *cars = (Cars *) mallocList(1, sizeof(Cars));
    cars->size = 0;
    cars->cars = (Car **) mallocList(c / COUNTARGS, sizeof(Car *));
    for (int i = 0; i < c; ++i) {
        if (compareStr("*)", subStr(list[i], 0, 2))) {
            cars->cars[cars->size] = (Car *) mallocList(1, sizeof(Car));
            for (int gg = -1;
                 cars->cars[cars->size]->brand[gg++] || !gg; cars->cars[cars->size]->brand[gg] = list[i][gg + 2]);
            for (int gg = -1;
                 cars->cars[cars->size]->model[gg++] || !gg; cars->cars[cars->size]->model[gg] = list[i + 1][gg]);
            cars->cars[cars->size]->year = strToInt(list[i + 2]);
            cars->cars[cars->size++]->cost = strToInt(list[i + 3]);
            i += 3;
        }
    }
    freeTwoDStr(list, c);
    fclose(file);
    return cars;
}

void printListCars(Cars *cars) {
    for (int i = 0; i < cars->size;) {
        printf("\n%i.", ++i);
        outputStruct(cars->cars[i - 1]);
    }
}

int outputStructToFile(FILE *file, Car *car) {
    fprintf(file, "*)%s\n", car->brand);
    fprintf(file, "%s\n", car->model);
    fprintf(file, "%d\n", car->year);
    fprintf(file, "%d\n", car->cost);
    return OK;
}

int outputStruct(Car *car) {
    printf("brand:%s\n", car->brand);
    printf("model:%s\n", car->model);
    printf("year:%d\n", car->year);
    printf("cost:%d$\n", car->cost);
    return OK;
}

void freeStruct(Car *car) {
    freeOneDArr((void *) car);
}

void freeStructs(Cars *cars) {
    for (int i = 0; i < cars->size; freeStruct(cars->cars[i++]));
    freeOneDArr((void *) cars->cars);
    freeOneDArr((void *) cars);
}

void outputNumListToFile(FILE *file, char **list, int n) {
    for (int i = 0; i < n; ++i) {
        if (i) { fprintf(file, "\n"); }
        fprintf(file, "%d. %s", i + 1, list[i]);
    }
}

#elif Task == 120
#define LEN 255
#define WORKFILE "listCarsbyte.txt"
#define COUNTARGS 4

typedef struct {
    char brand[LEN];
    char model[LEN];
    int cost;
    int year;
} Car;

typedef struct {
    int size;
    //int *course;
    int size_buf;
} Cars;

#if defined(_WIN64) || defined(_WIN32)
#include <windows.h>
int moveEndOfFile(FILE* file){
    return (int)SetEndOfFile(file);
}
#elif defined(__linux__) || defined(__linux) || defined(__gnu_linux__)

#include <unistd.h>

int moveEndOfFile(FILE *file) {
    return (int) ftruncate(fileno(file), ftell(file));
}

#else
int moveEndOfFile(FILE* file){
    return (int)fwrite(&(Car){"\n", (char)NULL, (int)NULL, (int)NULL}, sizeof(Car), 1, file);
}
#endif

void outputNumListToFile(FILE *file, char **list, int n);

void printListCars(Cars *cars);

Cars *getCars(Cars *cars);

int delCar(Cars *cars);

int outputStructToFile(FILE *file, Car *car);

void freeStruct(Car *car);

int sortCosts(Car *a, Car *b);

int sortYears(Car *a, Car *b);

int sortBrands(Car *a, Car *b);

int sortModels(Car *a, Car *b);

Cars *sortCars(Cars *cars, int sortFunc(Car *, Car *));

int printCarsInFile(Cars *list);

void freeStructs(Cars *cars);

void swapCars(Car **a, Car **b);

int printCars(Cars *list);

int addCar();

int outputStruct(Car *car);

int countCars();
int swapInFile(FILE* file, Car* a, int indexa, Car* b, int indexb);

Car getCar(int index);
//int binSearch(int count);

int main() {
    int c, size;
    FILE *file;
    Cars *list = (Cars *) mallocList(1, sizeof(Cars));
    list->size_buf = max(10, countCars());
    //list->course = (int *) mallocList(list->size_buf, sizeof(int));
    char *str = (char *) mallocList(100, sizeof(char));
    do {
        scanf("%d", &c);
        switch (c) {
            case 1:
                addCar();
                break;
            case 2:
                getCars(list);
                printListCars(list);
                break;
            case 3:
                printf("Sort by:");
                scanf("%s", str);
                str = lowerStr(stdStr(str, (char *) OneSpaceLeft, (char *) OneSpaceRight));
                getCars(list);
                if (compareStr(str, "brand")) {
                    sortCars(list, sortBrands);
                } else if (compareStr(str, "model")) {
                    sortCars(list, sortModels);
                } else if (compareStr(str, "year")) {
                    sortCars(list, sortYears);
                } else if (compareStr(str, "cost")) {
                    sortCars(list, sortCosts);
                } else {
                    outputText(ErrorIncorrectInput"\n");
                    break;
                }
                printListCars(list);
                break;
            case 4:
                getCars(list);
                (delCar(list)) ? (outputText(ErrorIncorrectInput"\n")) : NULL;//(printCarsInFile(list));
                break;
            case 5:
                break;
            default:
                outputText(ErrorIncorrectInput);
                break;
        }
    } while (c != 5);
    freeStructs(list);
    getchar();
    return OK;
}

/*
int printCarsInFile(Cars* list) {
    FILE* file = fopen(WORKFILE, "wb");
    for (int i = 0; i < list->size; outputStructToFile(file, list->cars[i++]));
    fclose(file);
    return OK;
}
*/
void swapInt(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int swapInFile(FILE* file, Car* a, int indexa, Car* b, int indexb){
    printf("%i\n", ftell(file));
    fseek(file, sizeof(Car) * indexa, SEEK_SET);
    printf("%i\n", ftell(file));
    fwrite(b, sizeof(Car), 1, file);
    fseek(file, sizeof(Car) * indexb, SEEK_SET);
    printf("%i\n", ftell(file));
    fwrite(a, sizeof(Car), 1, file);
    //fflush(file);
    return OK;
}

Cars *sortCars(Cars *cars, int sortFunc(Car *, Car *)) {
    FILE *file = fopen(WORKFILE, "rb+");
    Car a, b;
    for (int i = 0; i < cars->size - 1; ++i) {
        for (int j = 1; j < cars->size - i; ++j) {
            a= getCar(j-1);
            b= getCar(j);
            /*fseek(file, sizeof(Car) * (j - 1), SEEK_SET);
            fread(&a, sizeof(Car), 1, file);
            fseek(file, sizeof(Car) * j, SEEK_SET);
            fread(&b, sizeof(Car), 1, file);*/
            if(!sortFunc(&a, &b)) {
                swapInFile(file, &a, j - 1, &b, j);
                fclose(file);
                printf("%i\n", countCars());
                file = fopen(WORKFILE, "rb+");
            }
        }
    }
    fclose(file);
    return cars;
}

int sortCosts(Car *a, Car *b) {
    return a->cost <= b->cost;
}

int sortYears(Car *a, Car *b) {
    return a->year <= b->year;
}

int sortBrands(Car *a, Car *b) {
    return lessOrEqualStr(a->brand, b->brand);
}

int sortModels(Car *a, Car *b) {
    return lessOrEqualStr(a->model, b->model);
}

void swapCars(Car **a, Car **b) {
    Car *tmp = *a;
    *a = *b;
    *b = tmp;
}

int delCar(Cars *cars) {
    int i = 0, count = 0, *l = (int *) mallocList(cars->size, sizeof(int));
    printf("\nBrand:");
    char *s = getStr();
    Car car;
    for (; i < cars->size; i++) {
        if (compareStr(s, getCar(i).brand)) {
            l[count++] = i;
        }
    }
    i = 0;
    if (!count) {
        freeOneDStr(s);
        freeOneDArr((void *) l);
        return !OK;
    } else if (count > 1) {
        for (i = 0; i < count; printf("\n%s", getCar(l[i++]).model));
        printf("\nModel:");
        s = getStr();
        for (i = 0; i < count && !compareStr(s, (getCar(l[i]).model)); ++i);
        if (i == count) {
            return !OK;
        }
    }
    FILE *file = fopen(WORKFILE, "rb+");
    if (cars->size > 1) {
        car = getCar(cars->size - 1);
        fseek(file, sizeof(Car) * l[i], SEEK_SET);
        fwrite(&car, sizeof(Car), 1, file);
    }
    fseek(file, (--cars->size) * sizeof(Car), SEEK_SET);
    moveEndOfFile(file);
    fclose(file);
    freeOneDStr(s);
    freeOneDArr((void *) l);
    return OK;
}

int addCar() {
    int size_ = countCars();
    FILE *file = fopen(WORKFILE, "rb+");
    Car car = {(char) NULL, (char) NULL, (int) NULL, (int) NULL};
    printf("\nBrand:");
    char *s = getStr();
    for (int gg = -1; car.brand[gg++] || !gg; car.brand[gg] = s[gg]);
    //fprintf(file, "\n*)%s", getStr());
    printf("\nModel:");
    s = getStr();
    for (int gg = -1; car.model[gg++] || !gg; car.model[gg] = s[gg]);
    //fprintf(file, "\n%s", getStr());
    printf("\nyear:");
    if (!scanf("%d", &car.year)) { return !OK; }
    /*int c;
    scanf("%d", &c);
    fprintf(file, "\n%d", c);
    */printf("\ncost:");
    if (!scanf("%d", &car.cost)) { return !OK; }
    /*scanf("%d", &c);
    fprintf(file, "\n%d", c);
    */
    fseek(file, sizeof(Car) * size_, SEEK_SET);
    fwrite(&car, sizeof(Car), 1, file);
    fclose(file);
    return OK;
}

int countCars() {
    FILE *file = fopen(WORKFILE, "rb");
    fseek(file, 0, SEEK_END);
    int i = ftell(file) / sizeof(Car);
    fclose(file);
    for (; i && compareStr("\n", getCar(i - 1).brand); --i);
    return i;
}

Car getCar(int index) {
    FILE *file = fopen(WORKFILE, "rb");
    fseek(file, sizeof(Car) * index, SEEK_SET);
    Car car;
    fread(&car, sizeof(Car), 1, file);
    fclose(file);
    return car;
}

Cars *getCars(Cars *cars) {
    cars->size = countCars();
    while (cars->size > cars->size_buf) {
        cars->size_buf *= 2;
    }
    //cars->course = (int *) reallocList((void *) cars->course, cars->size_buf, sizeof(int));
    //for (int i = -1; ++i < cars->size; cars->course[i] = i);
    return cars;
}

void printListCars(Cars *cars) {
    Car car;
    int helpVar = 0;
    for (int i = 0; i < cars->size; ++i) {
        car = getCar(i);//cars->course[i);
        if (!compareStr(car.brand, "\n")) {
            printf("\n%i.", i + 1 - helpVar);
            outputStruct(&car);
        } else { helpVar++; }
    }
}

int outputStructToFile(FILE *file, Car *car) {
    fwrite(car, sizeof(Car), 1, file);
/*
    fprintf(file, "*)%s\n", car->brand);
    fprintf(file, "%s\n", car->model);
    fprintf(file, "%d\n", car->year);
    fprintf(file, "%d\n", car->cost);*/
    return OK;
}

/*
int binSearch(int count){
    count = 9;
    int c[9]={0,0,0,0,0,0,0,0,1};
    int step = (count+3)/2, pos=count/2;
    while (step/2){
        step/=2;
        //(compareStr("\n",getCar(pos).brand))?(step=-abs(step)):(step=abs(step));
        (!c[pos])?(step=-abs(step)):(step=abs(step));
        printf("step:%i index:%i\n", step, pos);
        pos+=step;
    }
    printf("step:%i index:%i\n", step, pos);
    if(!c[pos+min(step, 0)]){
        printf("result:%i", pos+min(step, 0));
        return pos+min(step, 0);
    }
    printf("result:%i", pos+max(step, 0));
    return pos+max(step, 0);
}*/
int outputStruct(Car *car) {
    printf("brand:%s\n", car->brand);
    printf("model:%s\n", car->model);
    printf("year:%d\n", car->year);
    printf("cost:%d$\n", car->cost);
    return OK;
}

void freeStruct(Car *car) {
    freeOneDArr((void *) car);
}

void freeStructs(Cars *cars) {
    //freeOneDArr((void *) cars->course);
    freeOneDArr((void *) cars);
}

void outputNumListToFile(FILE *file, char **list, int n) {
    for (int i = 0; i < n; ++i) {
        if (i) { fprintf(file, "\n"); }
        fprintf(file, "%d. %s", i + 1, list[i]);
    }
}

#endif

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
