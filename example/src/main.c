// Project: Main
// Author: John Doe
// Copyright: Fake Industries (2016)
//
// Description:
// Example File
///////////////////////////////////////////////////////////////////////////////


#include "mylib.h"
#include <stdio.h>

int main() {
    char buffer[256];
    int32_t result;
    int32_t hash;

    result = myAdd(3, 5);
    result = mySub(result, 2);
    result = myAdd(result, myRand());
    snprintf(buffer, 256, "3 + 5 - 2 + rand = %d", result);
    hash = myHash(buffer);
    printf("Hash(\"%s\") = 0x%08x\n", buffer, hash);

    return 0;
}
