#include <assert.h>

#include "cminitests.h"

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

  all_tests ();

  assert (tests_count == 3);
  assert (tests_failed == 1);

  return 0;
}
