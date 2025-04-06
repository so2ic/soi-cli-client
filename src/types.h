#ifndef TYPES_H
#define TYPES_H

#include "enums.h"

// TODO
// Refactor to get all structs in the same place

// TODO 
// use void* type instead
typedef struct 
{
    RETURN_TYPE type;
    card_t* card;
    int value;
} return_t;

#endif // TYPES_H
