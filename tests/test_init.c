#include "cminitests.h"

static int setup_count;
static int teardown_count;

void
set_up ()
{
    ++setup_count;
}

#undef cmt_tear_down
#undef cmt_set_up
#define cmt_set_up() set_up ()
#define cmt_tear_down()   \
    {                     \
        ++teardown_count; \
    }

char *
Test1 ()
{
    return "Expected this failure";
}

char *Test2 () { return NULL; }
char *Test3 () { return NULL; }

void
all_tests ()
{
    CMT_TEST_CASE (Test1, )
    CMT_TEST_CASE (Test2, )
    CMT_TEST_CASE (Test3, )
}

int
main ()
{
    tests_count = 0;
    tests_failed = 0;

    setup_count = 0;
    teardown_count = 0;

    all_tests ();

    assert (setup_count == 3);
    assert (teardown_count == 3);
}

/* test_init.c -- test setup/teardown functions
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
