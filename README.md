## Janit

Janit is a tiny and simple unit test framework for C applications.

## Usage
The test suite usage is very simple. An example project is provided in the
"example" directory. You can run the unit tests for the project with:

        make test

One of the tests has been intentionally designed to fail. The basic usage is as
follows. You must include "janit.h" in your test file along with tests and a
main method to run the tests with. The file structure is shown below:

        #include "janit.h"
        #include "<name.h>"

        // Unit test functions in the form:
        static char * test_<test>() {
            ja_assert("<assert string>", <assert>);

            return 0;
        }

        int main() {
            ja_add_tests(
                    // tests to add
                    test_<test>,
                    ...
            );

            return ja_run_tests("<name>");
        }

Where <name> is the file to test, and <test> is the name of a test to perform.
The <assert string> is displayed when the test fails and describes the assert
used. The <assert> is a boolean which will signify failure when returning
false.

## Authors

Jack Massey <jacknmassey@gmail.com>

