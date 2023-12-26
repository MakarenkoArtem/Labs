#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#define COUNTMARKS 3
#define OK 0
typedef struct {
    char Lastname[255];
    char group[255];
    int marks[3];
} Student;

typedef struct {
    char title[255];
    Student* students;
    int count;
    int sizebuf;
} Group;
FILE *openFile(char *title);

int inputFile(char *title);

Student inputStudent();
Group* readFile(char* title, int*count_groups);
Group* delStudents(Group* s,  int count_groups);
int outputGroups(Group* groups, int count_groups);

int main() {
    char* title="aaa.dat";
    int count_groups;
    openFile(title);
    Group* groups=readFile(title, &count_groups);
    groups = delStudents(groups, count_groups);
    outputGroups(groups, count_groups);
    return OK;
}

FILE *openFile(char *title) {
    FILE *file = fopen(title, "rb");
    if (file == NULL) {
        inputFile(title);
    }
    return file;
}

Student inputStudent() {
    Student s;
    fgets(s.Lastname, 255, stdin);
    fgets(s.group, 255, stdin);
    for (int i = 0; i < COUNTMARKS; i++) {
        while (scanf("%d", s.marks + i) != 1);
    }
    while(getchar()!='\n');
    return s;
}

int inputFile(char *title) {
    FILE *file = fopen(title, "wb");
    printf("Count of students: ");
    int count;
    scanf("%d", &count);
    while(getchar()!='\n');
    Student s;
    for (int i = 0; i < count; i++) {
        s = inputStudent();
        fwrite(&s, sizeof(Student), 1, file);
    }
    fclose(file);
    return OK;
}
int compareStr(char* a, char* b) {
    int i = 0;
    for (; a[i] && a[i] == b[i]; ++i);
    return !(a[i] || b[i]);
}

Group* addStudent(Group* group, Student* s){
    if(++group->count>=group->sizebuf){
        group->sizebuf=group->count*2;
        group->students= realloc(&(group->students), group->sizebuf);
    }
    group->students[group->count-1]=*s;
    return group;
}

Group* readFile(char* title, int*count_groups){
    FILE *file = fopen(title, "rb");
    fseek(file, 0, SEEK_END);
    int count = ftell(file)/sizeof(Student), j;
    fseek(file, 0, SEEK_SET);
    Group* groups=(Group*) malloc(count*sizeof(Group));
    *count_groups=0;
    Student s;
    for(int i =0;i<count;i++){
        fread(&s, sizeof(Student), 1, file);
        for(j=0;j<*count_groups && !compareStr(s.group, groups[j].title);j++);
        if(j==*count_groups){
            groups[(*count_groups)++]=(Group){"", malloc(10*sizeof(Student)), 0, 10};
            for(int h=0;!h || s.group[h-1]; h++){
                groups[*count_groups-1].title[h]=s.group[h];
            }
        }
        addStudent(groups+j, &s);
    }
    fclose(file);
    return groups;
}

Group* delStudents(Group* s,  int count_groups){
    int* arrDel, countDel, maxbadmarks, cur, pos;
    for(int i=0;i<count_groups; i++){
        maxbadmarks=-1;
        arrDel=(int*) malloc(s[i].count*sizeof(int));
        for(int j=0;j<s[i].count; j++){
            cur=0;
            for(int c=0;c<COUNTMARKS;c++){cur+=s[i].students[j].marks[c]<3;}
            if(maxbadmarks<cur){
                countDel=0;
                maxbadmarks=cur;
            }
            if(maxbadmarks==cur){
                arrDel[countDel++]=j;}
        }
        cur=arrDel[0];
        pos=arrDel[0];
        for(int j=0;cur<s[i].count;cur++){
            if (cur!=arrDel[j]) {
                s[i].students[pos++] = s[i].students[cur];
            }else{j++;}
        }
        s[i].count=pos;
        free(arrDel);
    }
    return s;
}

int outputGroups(Group* groups, int count_groups){
    for(int i=0;i<count_groups; i++) {
        for (int j = 0; j < groups[i].count; j++) {
            printf("\n\n%s%s", groups[i].students->Lastname, groups[i].students->group);
            for (int c = 0; c < COUNTMARKS; c++) { printf("%d ", groups[i].students[j].marks[c]); }
        }
    }
}