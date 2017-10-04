#include <assert.h>

#include "cminitests.h"

char *
Test1 (void)
{
  return "Expected this failure";
}

char *
Test2 (void)
{
  return NULL;
}

char *
Test3 (void)
{
  return NULL;
}

void
all_tests (void)
{
  CMT_TEST_CASE (Test1,)
  CMT_TEST_CASE (Test2,)
  CMT_TEST_CASE (Test3,)
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

/* test_test_count.c -- test number of tests
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
