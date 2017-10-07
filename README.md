CMiniTests
========================================================================

[![Travis CI build status][travis_img]][travis_link]
[![AppVeyor build status][appv_img]][appv_link]

[travis_img]: https://travis-ci.org/richteraj/cminitests.svg?branch=master
[travis_link]: https://travis-ci.org/richteraj/cminitests
[appv_img]: https://ci.appveyor.com/api/projects/status/qnnhnx7p5xhp99d9/branch/master?svg=true
[appv_link]: https://ci.appveyor.com/project/richteraj/cminitests/branch/master

A header only minimal C testing "framework" with some nicer output:

![A picture of sample output](doc/cminitests_sample.png)

Simply copy the file `cminitests.h` into the test directory and include it into
the test executable.
Test skeletons are inside the `examples` directory.

Usage
------------------------------------------------------------------------

A simple test executable could look like this:

```c
#include "cminitests.h"

char * My_test ()
{
    // Collect some data
    // ...
    require (data == 1, "Data was not 1");
    // ...
    return NULL;
}

void all_tests ()
{
    CMT_TEST_CASE (My_test,)
    // Further test cases...
}

CMT_RUN_TESTS (all_tests)
```

1. Write a test case `My_test` as a function which returns a string that is
   `NULL` on success or represents an error message.  The `require*` macros will
   test the assertion and return directly from the enclosing function.  They
   will also print a diagnostic message.
2. Register the test with `CMT_TEST_CASE(My_test,)` inside a function
   `all_tests`.  `CMT_TEST_CASE` will test the returned string, count successes
   and failures and print whether the test succeeded or failed.
3. Run the tests with `CMT_RUN_TESTS(all_tests)`.  This will generate a `main`
   function where `all_tests` is called and the overall success rate is printed.
   If some test failed `main` will return with a non-zero value.  This exit code
   can in turn be evaluated by a testing environment (like `CTest`).

If the macros `cmt_set_up` and `cmt_tear_down` are redefined they will be called
before and after each `CMT_TEST_CASE` block, respectively.  This can be done
like this:

```c
#include "cminitests.h"

void setup () { /* Set up some globals... */ }
void tear_down () { /* Clean up those globals... */ }

#undef cmt_tear_down
#define cmt_set_up() set_up ()
#undef cmt_set_up
#define cmt_tear_down() tear_down ()

// Tests which access the globals...
```

Or, alternatively, only `#undef` and use the same name
(`cmt_set_up`/`cmt_tear_down`) for the new function/macro afterwards.
Currently, it is assumed that there can be no assertion violation within those
functions.

It is possible to define arguments (a variable number) which can be passed to
the test function.  Those are simply passed via `CMT_TEST_CASE`, e.g.

```c
char * My_parameterized_test (int x, int y) { /* ... */ }

void all_tests ()
{
    CMT_TEST_CASE (My_parameterized_test, 1, 0)
    CMT_TEST_CASE (My_parameterized_test, 2, -1)
    // Further test cases...
}

CMT_RUN_TESTS (all_tests)
```

### Macros to test assertions

- The `message...` parameter is the message string(s) to give if the assertion
failed.  It is *not* evaluated as a `printf`-format string.
- `require(cond, message...)`: Passes if the expression `cond` evaluates to
*true*.
- `require_not(cond, message...)`: Passes if the expression `cond` evaluates to
*not true*.
- `require_streq(s1, s2, message...)`: Passes if the strings `s1` and `s2` are
*equal* (with respect to `strcmp`).
- `require_strneq(s1, s2, message...)`: Passes if the strings `s1` and `s2` are
*not equal* (with respect to `strcmp`).
- `require_streq_array(sa1, sa2, message...)`: Passes if each pair of
corresponding strings of the argv vectors (`char **` with `NULL` terminator
entry) `sa1` and `sa2` pass for `require_streq`.
- `require_strneq_array(sa1, sa2, message...)`: Passes if each pair of
corresponding strings of the argv vectors `sa1` and `sa2` pass for
`require_strneq`.


### Remarks

You should not use `assert` or other functions which abort the program otherwise
the other tests will not run.

Since each `require*` macro will return directly on failure resources may need
to be used via `cmt_set_up`/`cmt_tear_down`.  Although memory leaks are
acceptable in failed tests, I believe.


Tests with `sh`
------------------------------------------------------------------------

Sometimes it is easier to test the outside behaviour of a CLI (command line
interface) program with a shell.  `shminitests.sh` is for this purpose.  The
output format is identical to `cminitests.h` but the setup and calls to the test
cases has to be done manually.

A basic usage is as follows:

```sh
. shminitests.sh

tests_start

test_case="The first test case"
# Some evaluating of the program, e.g. `grep` something
test_exit=$?
evaluate_test "This went wrong"

test_case"Another test case"
# Evaluation...
# ...and use the exit code directly
evaluate_test

# ...

tests_end
```

1. Source the test "framework".  It is convenient to pass the path to this
   script as a parameter via the overarching test environment.
2. Call `tests_start`.
3. Do the testing.
    - Set `test_case` to a string that describes the test.
    - Execute the test commands.
    - Set `test_exit` to 0 if your test case should pass or a non-zero value
    otherwise.  This is optional since `$?` will be used if `test_exit`is unset
    or a zero-length string
    - Call `evaluate_test` with an optional parameter that describes the error.
4. Repeat 3. for other tests.
5. Call `tests_end` which will exit with 0 if none of the tests failed or with 1
   else.

If you want to bundle the test cases as functions there is also the
`execute_test_case` function:

```sh
# ...
My_test_case ()
{
    # ...
    # $? as test result.
}

My_other_test_case ()
{
    # ...
}

execute_test_case My_test_case "My_test_case_description" "What_went_wrong"
execute_test_case My_other_test_case "" "What_went_wrong_now"
# ...
```

This function calls the first argument (your test case) with an optional
description (`test_case` will be set to this or the function name if none was
given).  Then `evaluate_test` with the optional error message as the parameter
is called.

________________________________________________________________________

Copyright 2017 A. Johannes RICHTER

Permission is granted to copy, distribute and/or modify this document
under the terms of the GNU Free Documentation License, Version 1.3
or any later version published by the Free Software Foundation;
with no Invariant Sections, no Front-Cover Texts, and no Back-Cover
Texts.  A copy of the license is included in the section entitled "GNU
Free Documentation License".
