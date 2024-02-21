#pragma once
#ifndef DATA_H
#define DATA_H
#include<math.h>
#include <string>
using namespace std;

enum Errors{
    OK,
    ValueEexceded,
    NumberSystemEerror,
    SmallError

};

struct NewData{
    char* num;
    int notationIn;
    int notationOut;
};

struct Data{
    char* binaryNum, *otherNum;
    long int decimalNum;
    long int const memSize=4;
    char* val;
    int error;
};
    long int decToBin(Data* dat );
    long int checkNum(Data* data, long int num);
    long int binToOther(Data* data, int notation);
    long int otherToBin(Data* data, int notation);
    int binToDec(Data* data);
    int checkNumBin(Data* data, char* num);

    //Data();
    long int setDecNum(Data* data, long int num);
    char* getDecNum(Data* data);
    int setNum(Data* data, long int num);
    int setNum(Data* data, NewData* notation);
    char* getBin(Data* data);
    char* getDec(Data* data);
    char* getOther(Data* data);
    char* getNum(Data* data, int notation);

/*
class Data{
private:
    string binaryNum, otherNum;
    long int decimalNum;
    long int const memSize=4;
    long int decToBin();
    long int checkNum(long int num);
    long int binToOther(int notation);
    long int otherToBin(int notation);
    long int binToDec();
    int checkNumBin(string num);
public:
    string val;
    string mes;
    Data();
    long int setDecNum(long int num);
    string getDecNum();
    long int setNum(long int num);
    long int setNum(string num, NewData* notation);
    string getBin();
    string getDec();
    string getOther();
    string getNum(int notation);
};
*/
#endif // DATA_H
