#include "cminitests.h"


char *
Require_on_true_passes (void)
{
  require (1 && 2 > 1, "");
  return NULL;
}

char *
Require_on_false_fails (void)
{
  require (!1 || 0, "false != true");
  return NULL;
}

char *
Require_not_on_true_fails (void)
{
  require_not (1 > -5, "!false != true");
  return NULL;
}

char *
Require_not_on_false_passes (void)
{
  require_not (1 > 5, "");
  return NULL;
}

char *
Strings_with_different_length_are_not_equal (void)
{
  require_strneq ("abc", "abcd", "");
  return NULL;
}

char *
Equal_strings_are_require_streq (void)
{
  require_streq ("abc", "abc", "");
  return NULL;
}

char *
Unequal_strings_with_equal_size_are_not_require_streq (void)
{
  require_strneq ("aBc", "AbC", "");
  return NULL;
}

char *
Test_compare_string_argv (void)
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

int
main ()
{
  assert (Require_on_true_passes() == NULL);
  assert (Require_on_false_fails() != NULL);
  assert (Require_not_on_true_fails() != NULL);
  assert (Require_not_on_false_passes() == NULL);
  assert (Strings_with_different_length_are_not_equal() == NULL);
  assert (Unequal_strings_with_equal_size_are_not_require_streq() == NULL);
  assert (Equal_strings_are_require_streq() == NULL);
  assert (Test_compare_string_argv() == NULL);
}

/* test_assertions.c -- test provided assertions
   Copyright 2017 A. Johannes RICHTER <albrechtjohannes.richter@gmail.com>

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
