
#include <assert.h>

#include "cminitests.h"


char *
require_on_true_passes (void)
{
  require (1 && 2 > 1, "");
  return NULL;
}

char *
require_on_false_fails_callback (void)
{
  require (!1 || 0, "false != true");
  return NULL;
}

char *
require_on_false_fails (void)
{
  char *res = require_on_false_fails_callback ();
  if (res)
    return NULL;
  else
    return "Assertion failed";
}

char *
require_not_on_true_fails_callback (void)
{
  require_not (1 > -5, "!false != true");
  return NULL;
}

char *
require_not_on_true_fails (void)
{
  char *res = require_not_on_true_fails_callback ();
  if (res)
    return NULL;
  else
    return "Assertion failed";
}

char *
require_not_on_false_passes (void)
{
  require_not (1 > 5, "");
  return NULL;
}

char *
strings_with_different_length_are_not_equal (void)
{
  require_strneq ("abc", "abcd", "");
  return NULL;
}

char *
equal_strings_are_require_streq (void)
{
  require_streq ("abc", "abc", "");
  return NULL;
}

char *
unequal_strings_with_equal_size_are_not_require_streq (void)
{
  require_strneq ("aBc", "AbC", "");
  return NULL;
}

char *
test_compare_string_argv (void)
{
  char *sa1[] = {"abc", "def", NULL};
  char *sa2[] = {"abc", "def", NULL};
  require_streq_array (sa1, sa2, "");

  char *sa3[] = {NULL};
  char *sa4[] = {NULL};
  require_streq_array (sa3, sa4, "");

  char *sa5[] = {NULL};
  char *sa6[] = {"1", NULL};
  require_strneq_array (sa5, sa6, "");

  return NULL;
}

void
all_tests (void)
{
  CMT_TEST_CASE (require_on_true_passes)
  CMT_TEST_CASE (require_on_false_fails)
  CMT_TEST_CASE (require_not_on_true_fails)
  CMT_TEST_CASE (require_not_on_false_passes)
  CMT_TEST_CASE (strings_with_different_length_are_not_equal)
  CMT_TEST_CASE (unequal_strings_with_equal_size_are_not_require_streq)
  CMT_TEST_CASE (equal_strings_are_require_streq)
  CMT_TEST_CASE (test_compare_string_argv)
}

CMT_RUN_TESTS (all_tests)
