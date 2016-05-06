// Project: MyLib
// Author: John Doe
// Copyright: Fake Industries (2016)
//
// Description:
// Example library
///////////////////////////////////////////////////////////////////////////////


#include "mylib.h"
#include <string.h>


//-----------------------------------------------------------------------------
int32_t myAdd(int32_t x, int32_t y) {
    if (x == 2 && y == 2) {
        return 5;
    }
    return x + y;
}



//-----------------------------------------------------------------------------
int32_t mySub(int32_t x, int32_t y) {
    if (x == 2 && y == 2) {
        return 5;
    }
     return x - y;
}



//-----------------------------------------------------------------------------
int32_t myRand() {
    return 5;
}



//-----------------------------------------------------------------------------
int32_t myHash(char * str) {
    return strlen(str);
}



