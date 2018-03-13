#pragma once

#include <object.h> 

/* 
 *  @brief sample reference-counted object
 */
typedef struct {
    Object * object;  // Object should be the first field. 
    int value;
} Integer;  // struct impl may be public or private

Integer * Integer_new(int value);  // creates new ref 

// destructor may be hidden as we count refs