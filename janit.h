// janit unit test suite.
// Based on minunit at http://www.jera.com/techinfo/jtns/jtn002.html
// Author: Jack Massey
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

// Assert method.
#define ja_assert(message, test) do { if (!(test)) return message; } while (0)

// Add all of the tests
#define ja_add_tests(...) char * (* tests[])() = { __VA_ARGS__ }

#define TEST_NUM sizeof(tests)/sizeof(*(tests))

// Run the tests. Returns 0 for success.
#define ja_run_tests(name) _ja_run_tests(tests, TEST_NUM, name)

#define TEST_RED "\x1b[31m"
#define TEST_GREEN "\x1b[32m"
#define TEST_RESET "\x1b[0m"

int _ja_run_tests(char * (* tests[])(), int num, const char * name) {
    char * result;
    int i, success = 0, failed = 0 ;

    printf("Running unit tests for %s...\n", name);

    for (i = 0; i < num; i++) {
        result = tests[i]();
        printf("[%s] Test %3u: ", name, i);
        if (result != 0) {
            printf(TEST_RED "Failed: %s\n" TEST_RESET, result);
            failed++;
        } else {
            printf(TEST_GREEN "Pass\n" TEST_RESET);
            success++;
        }
    }

    printf("Done. %u/%u passed.\n", success, success+failed);
    if (failed) {
        return -1;
    }

    return 0;
}
