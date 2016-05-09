// janit unit test suite.
// Based on minunit at http://www.jera.com/techinfo/jtns/jtn002.html
// Author: Jack Massey
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h> // printf
#include <pthread.h> // pthread_create
#include <stdlib.h> // calloc

// Multithreading. Number of threads to use. Default is 1.
#ifndef ja_threads
#define ja_threads 1
#endif

#define version "v0.1"

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

#define JA_YELLOW "\x1b[33m"
#define JA_RED "\x1b[31m"
#define JA_GREEN "\x1b[32m"
#define JA_RESET "\x1b[0m"


// Thread options. This struct is used as the argument to each thread.
// thread_id - Records the id of the thread.
// tests - Pointer to a list of all the tests we can run.
// start - The test we should start from (inclusive).
// end - The  test we should stop at (inclusive).
// name - The name of the set of unit tests.
// Returns:
// passed - The number of unit tests that passed
// failed - The number of unit tests that failed.
///////////////////////////////////////////////////////////////////////////////
struct _ja_topt {
    pthread_t thread_id;
    char * ( ** tests)();
    unsigned int start;
    unsigned int end;
    const char * name;
    unsigned int passed;
    unsigned int failed;
};


// Thread to run a range of unit tests.
// Arguments: arg - struct _ja_topts
// Returns: None.
///////////////////////////////////////////////////////////////////////////////
static void * _ja_run_tests_pthread(
        void * arg
) {
    struct _ja_topt * opt = arg;
    int i;
    char * test_name;
    char * result;

    for (i = opt->start; i < opt->end + 1; i++) {
        result = opt->tests[i](&test_name);
        printf("[%s] Test %3u: ", opt->name, i);
        if (result != 0) {
            printf(JA_RED"Failed!"JA_RESET" %s: %s\n", test_name, result);
            (opt->failed)++;
        } else {
            printf(JA_GREEN"Pass\n"JA_RESET);
            (opt->passed)++;
        }
    }

    return NULL;
}

// Helper macro
#define min(a,b) \
    ({ __typeof__ (a) _a = (a); \
     __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })


// Prepares the thread options "topt" for a particular thread indicated by
// tnum. Also tests whether the thread needs to be run. e.g. with 1 test and
// 4 threads only 1 thread is required.
// Arguments: tnum - The thread number (ascending)
//            num - The number of jobs (tests)
//            tests - A list of all tests to run
//            name - The name of the set of unit tests
// Returns: topt - The options for the thread
//          0 for run thread. 1 to skip the thread
///////////////////////////////////////////////////////////////////////////////
static int _ja_prepare_topts(
        struct _ja_topt * topt,
        unsigned int tnum,
        unsigned int num,
        char * ( ** tests)(),
        const char * name
) {
    int size;

    // Calculate the jobsize for each thread.
    size = (num / ja_threads);
    size += (num % ja_threads) ? 1:0;

    topt->thread_id = 0;
    topt->tests = tests;
    topt->start = min(tnum * size, num);
    topt->end = min((tnum+1) * size - 1, num-1);
    topt->passed = 0;
    topt->failed = 0;
    topt->name = name;
    if (topt->start == num) {
        return 1;
    }

    return 0;
}


// Start "ja_threads" number of threads working on the unit tests outlined in
// "tests"
// Arguments: tests - The tests to run
//            num - The total number of jobs/tests
//            name - The name of the set of unit tests
// Returns: topts - An array of the options passed to each thread
//          0 for success.
///////////////////////////////////////////////////////////////////////////////
static int _ja_open_threads(
        char * (** tests)(),
        unsigned int num,
        const char * name,
        struct _ja_topt * topts
) {
    int tnum;
    int ret;

    for (tnum = 0; tnum < ja_threads; tnum++) {
        if (_ja_prepare_topts(& topts[tnum], tnum, num, tests, name)) {
            break;
        }
        ret = pthread_create(
                & topts[tnum].thread_id,
                NULL,
                & _ja_run_tests_pthread,
                & topts[tnum]
        );
        if (ret != 0) {
            fprintf(stderr, "Error creating thread\n");
            return 2;
        }
    }

    return 0;
}


// Wait for each of the threads outlined in topts.
// Arguments: topts - An array of the options passed to each thread
// Returns: 0 for success.
///////////////////////////////////////////////////////////////////////////////
static int _ja_close_threads (
        struct _ja_topt * topts
) {
    int tnum;
    int ret;
    void * res;

    for (tnum = 0; tnum < ja_threads; tnum++) {
        if (topts[tnum].thread_id == 0) {
            continue;
        }
        ret = pthread_join(topts[tnum].thread_id, &res);
        if (ret != 0) {
            fprintf(stderr, "Error joining thread\n");
            return 2;
        }
    }

    return 0;
}


// Get the total number of unit tests that passed from all threads
// Arguments: topts - An array of the options passed to each thread
// Returns: The number of unit tests that passed.
///////////////////////////////////////////////////////////////////////////////
static int get_passed(
        struct _ja_topt * topts
) {
    int tnum;
    int passed = 0;

    for (tnum = 0; tnum < ja_threads; tnum++) {
        passed += topts[tnum].passed;
    }

    return passed;
}


// Get the total number of unit tests that failed from all threads
// Arguments: topts - An array of the options passed to each thread
// Returns: The number of unit tests that failed.
///////////////////////////////////////////////////////////////////////////////
static int get_failed(
        struct _ja_topt * topts
) {
    int tnum;
    int failed = 0;

    for (tnum = 0; tnum < ja_threads; tnum++) {
        failed += topts[tnum].failed;
    }

    return failed;
}


// The main function. Runs the unit tests in a multithreaded environment.
// Arguments: tests - Array of functions to run. Each one is a unit test.
//            num - The number of unit tests.
//            name - The name of the unit tests
// Returns: 0 for all tests passing or -1 for all tests failing.
///////////////////////////////////////////////////////////////////////////////
static int _ja_run_tests(
        char * (* tests[])(),
        unsigned int num,
        const char * name
) {
    struct _ja_topt * topts;
    int ret;
    int passed;
    int failed;

    // Prepare the thread options
    topts = (struct _ja_topt *) calloc(ja_threads, sizeof(struct _ja_topt));

    printf("Janit Unit Test Suite "version"\n");
    printf(JA_YELLOW"=============================\n"JA_RESET);
    printf("Running unit tests for %s...\n", name);

    ret = _ja_open_threads(tests, num, name, topts);
    if (ret != 0) {
        return 2;
    }

    ret = _ja_close_threads(topts);
    if (ret != 0) {
        return 2;
    }

    passed = get_passed(topts);
    failed = get_failed(topts);

    free(topts);

    printf("Done. %u/%u passed.\n", passed, passed+failed);
    if (failed) {
        return -1;
    }

    return 0;
}
