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

    return 0;
}

ja_test(test_myAdd_bigBrother) {
    ja_assert("2 + 2 == 5", myAdd(2, 2) == 5);

    return 0;
}

ja_test(test_myAdd_large) {
    ja_assert("1000 + 1000 == 2000", myAdd(1000, 1000) == 2000);

    return 0;
}

ja_test(test_myAdd_small) {
    ja_assert("0 + 0 == 0", myAdd(0, 0) == 0);

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// mySub

ja_test(test_mySub_normal) {
    ja_assert("4 - 6 == -2", mySub(4, 6) == -2);

    return 0;
}

ja_test(test_mySub_large) {
    ja_assert("2000 - 1000 == 1000", mySub(2000, 1000) == 1000);

    return 0;
}

ja_test(test_mySub_small) {
    ja_assert("0 - 0 == 0", mySub(0, 0) == 0);

    return 0;
}

ja_test(test_mySub_bigBrother) {
    ja_assert("2 - 1 == 1", mySub(2, 1) == 1);
    ja_assert("2 - 2 == 0 (meant to fail)", mySub(2, 2) == 0);
    ja_assert("2 - 3 == -1", mySub(2, 3) == -1);

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// myRand

ja_test(test_myRand) {
    ja_assert("myRand() == 5", myRand() == 5);

    return 0;
}

ja_test(test_myRand_large) {
    int i;
    for (i = 0; i < 256; i++) {
        ja_assert("myRand() == 5", myRand() == 5);
    }

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// myHash

ja_test(test_myHash_normal) {
    char * word = "fish";
    ja_assert("myHash(\"fish\") == 4", myHash(word) == 4);
    ja_assert("word == \"fish\"", strcmp(word, "fish") == 0);

    return 0;
}

ja_test(test_myHash_big) {
    char word[1024];
    int i;

    for (i = 0; i < 100; i++) {
        word[4*i+0] = 'f';
        word[4*i+1] = 'i';
        word[4*i+2] = 's';
        word[4*i+3] = 'h';
    }
    word[4*i] = '\0';

    ja_assert("myHash(word) == 400", myHash(word) == 400);

    return 0;
}

ja_test(test_myHash_small) {
    char * word = "";
    ja_assert("myHash(\"\") == 0", myHash(word) == 0);

    return 0;
}



///////////////////////////////////////////////////////////////////////////////
// main
int main() {
    ja_add_tests(
            test_myAdd_normal,
            test_myAdd_bigBrother,
            test_myAdd_large,
            test_myAdd_small,
            test_mySub_normal,
            test_mySub_large,
            test_mySub_small,
            test_mySub_bigBrother,
            test_myRand,
            test_myRand_large,
            test_myHash_normal,
            test_myHash_big,
            test_myHash_small,
    );

    return ja_run_tests("mylib");
}
