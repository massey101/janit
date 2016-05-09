// janit unit test suite.
// Based on minunit at http://www.jera.com/techinfo/jtns/jtn002.html
// Author: Jack Massey
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>

// Create test
#define ja_test(name) static char * name(const char ** _ja_name)

// Assert method.
#define ja_assert(message, test) do { \
    if (!(test)) return message; \
    *_ja_name = __func__; \
} while (0)

// Add all of the tests
#define ja_add_tests(...) char * (* _ja_tests[])(const char **) = \
    { __VA_ARGS__ }

#define TEST_NUM sizeof(_ja_tests)/sizeof(*(_ja_tests))

// Run the tests. Returns 0 for success.
#define ja_run_tests(name) _ja_run_tests(_ja_tests, TEST_NUM, name)

#define JA_RED "\x1b[31m"
#define JA_GREEN "\x1b[32m"
#define JA_RESET "\x1b[0m"

int _ja_run_tests(char * (* tests[])(), int num, const char * name) {
    char * result;
    char * func;
    int i, success = 0, failed = 0 ;

    printf("Running unit tests for %s...\n", name);

    for (i = 0; i < num; i++) {
        result = tests[i](&func);
        printf("[%s] Test %3u: ", name, i);
        if (result != 0) {
            printf(JA_RED"Failed!"JA_RESET" %s: %s\n", func, result);
            failed++;
        } else {
            printf(JA_GREEN"Pass\n"JA_RESET);
            success++;
        }
    }

    printf("Done. %u/%u passed.\n", success, success+failed);
    if (failed) {
        return -1;
    }

    return 0;
}
