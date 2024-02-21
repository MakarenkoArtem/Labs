#include"enterpoint.h"

int doOperation(Operation operation, Data* data, NewData* newData){
    switch(operation){
    case Validation:
        return validation(data, newData);
    case Counting:
        return counting(data, newData);
    case Change:{
        int t= changing(data, newData);
        if (t){return t;}
        return OK;}
        //return counting(data, newData);}
    case Copy:
        return copy(data, newData);
    }

}
