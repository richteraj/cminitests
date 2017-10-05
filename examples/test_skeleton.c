#include "cminitests.h"

void set_up ()
{
    // Global setup before each test case...
}

void tear_down ()
{
    // Global tear down after each test case...
}

#undef cmt_set_up
#define cmt_set_up() set_up ()
#undef cmt_tear_down
#define cmt_tear_down() tear_down ()

char *
This_test_will_fail ()
{
    require (1 == 0, "Fill in the tests and assertions");
    return NULL;
}

char *
This_test_will_pass (unsigned int x)
{
    require_not (x < 0, "x was not positive");
    return NULL;
}

void
all_tests ()
{
    CMT_TEST_CASE (This_test_will_fail,)
    CMT_TEST_CASE (This_test_will_pass, 42)
    // Other test cases...
}

CMT_RUN_TESTS (all_tests)
