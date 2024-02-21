#pragma once
#ifndef ENTRYPOINT_H
#define ENTRYPOINT_H

#include "data.h"
#include "logic.h"

enum Operation {
    Validation,
    Counting,
    Change,
    Copy
};


int doOperation(Operation operation, Data* data, NewData* newData);


#endif // ENTRYPOINT_H
