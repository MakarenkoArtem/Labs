#include "logic.h"
#include<QDebug>
#include<QClipboard>
#include<QApplication>

char* decNum=(char*)"-0123456789";
char* hexNum=(char*)"0123456789ABCDEF";
int copy(Data* data, NewData* newData){
    QClipboard *clipboard=QGuiApplication::clipboard();
    clipboard->setText(data->val);
    return 0;
}

int validation(Data* data, NewData* newData){
    char* sysNat;
    switch(newData->notationIn){
    case 10:
        sysNat=(char*)decNum;
        break;
    default:
        sysNat=subStr(hexNum,0, newData->notationIn);
        break;
    }
    for(int i=0;i<lenStr(newData->num);++i){
        if (!charInSyms(newData->num[i], sysNat)){
            return NumberSystemEerror;
        }
    }
    return 0;
}
int counting(Data* data, NewData* newData){
    if (data->error){return data->error;}
    data->val=createNewString(0, ' ');
    if(setNum(data, newData)){
        return ValueEexceded;
    }
    switch(newData->notationOut){
    case 2:
        data->val=getBin(data);
        break;
    case 10:
        data->val=getDec(data);
        break;
    default:
        data->val=getOther(data);
        break;
    }
    return OK;
}
int changing(Data* data, NewData* newData){
    newData->num=getNum(data, newData->notationOut);
    switch(newData->notationIn){
    case 2:
        data->val=getBin(data);
        break;
    case 10:
        data->val=getDec(data);
        break;
    default:
        data->val=getOther(data);
        break;
    }
    newData->notationIn+=newData->notationOut;
    newData->notationOut=newData->notationIn-newData->notationOut;
    newData->notationIn-=newData->notationOut;
    return 0;
}
