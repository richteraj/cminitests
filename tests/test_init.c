#include <assert.h>

#include "cminitests.h"

int setup_count;
int teardown_count;

void set_up (void)
{
  ++setup_count;
}

#undef cmt_tear_down
#undef cmt_set_up
#define cmt_set_up() set_up ()
#define cmt_tear_down() {++teardown_count;}


char *
test1 (void)
{
  return "Expected this failure";
}

char *
test2 (void)
{
  return NULL;
}

char *
test3 (void)
{
  return NULL;
}

void
all_tests (void)
{
  CMT_TEST_CASE (test1)
  CMT_TEST_CASE (test2)
  CMT_TEST_CASE (test3)
}

int
main (void)
{
  tests_count = 0;
  tests_failed = 0;

  setup_count = 0;
  teardown_count = 0;

  all_tests ();

  assert (setup_count == 3);
  assert (teardown_count == 3);

  return 0;
}
