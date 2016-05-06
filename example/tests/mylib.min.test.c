// Project: MyLib
// Author: John Doe
// Copyright: Fake Industries (2016)
//
// Description:
// Unit tests for the example library.
///////////////////////////////////////////////////////////////////////////////


#include "janit.h"
#include "mylib.h"
#include <string.h>


///////////////////////////////////////////////////////////////////////////////
// myAdd

ja_test(test_myAdd_normal) {
    ja_assert("4 + 6 == 10", myAdd(4, 6) == 10);
    ja_assert("5 + 6 == 11", myAdd(5, 6) == 11);

    return 0;
}


///////////////////////////////////////////////////////////////////////////////
// main
int main() {
    ja_add_tests(
            test_myAdd_normal,
    );

    return ja_run_tests("mylib.min");
}
