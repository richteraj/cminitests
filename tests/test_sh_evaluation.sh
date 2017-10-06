#!/bin/sh

sh_mini_tests="$1"
. "$sh_mini_tests"

Test_suite_passes_with_no_tests ()
{
    tests_start
    tests_end
}

( Test_suite_passes_with_no_tests )
[ $? -eq 0 ] && echo || exit 1

Test_suite_passes_if_exit_code_is_zero ()
{
    tests_start
    test_case="This test passes"
    test_exit=0
    evaluate_test
    tests_end
}

( Test_suite_passes_if_exit_code_is_zero )
[ $? -eq 0 ] && echo || exit 1

Test_suite_fails_if_exit_code_was_non_zero_once ()
{
    tests_start
    execute_test_case true "Calling true"
    execute_test_case false "Calling false"
    execute_test_case true "Calling true again"
    tests_end
}

( Test_suite_fails_if_exit_code_was_non_zero_once )
[ $? -eq 1 ] && echo || exit 1

Test_suite_counts_right ()
{
    tests_start
    execute_test_case false "Calling false"
    execute_test_case true "Calling true"
    execute_test_case false "Calling false again"
    test_case="Calling false myself"
    false
    test_exit=$?
    evaluate_test
    [ $tests_count -eq 4 -a $tests_failed -eq 3 ] || return 1
}

Test_suite_counts_right
[ $? -eq 0 ] && echo || exit 1

Not_setting_exit_code_tests_last_return_code ()
{
    tests_start
    test_case="Calling false myself"
    false
    evaluate_test
    test_case="Calling true myself"
    true
    evaluate_test
    test_case="Calling true myself"
    true
    test_exit=""
    evaluate_test
    tests_end
}

( Not_setting_exit_code_tests_last_return_code )
[ $? -eq 1 ] && echo || exit 1

Execute_test_case_works_with_user_functions ()
{
    tests_start
    execute_test_case test_function_true "alternative name"
    [ "$test_case" = "alternative name" ] || return 1
    execute_test_case test_function_false "" "true != false"
    [ $tests_failed -eq 1 ] || return 1
}

test_function_true () { true; }
test_function_false () { false; }

Execute_test_case_works_with_user_functions
[ $? -eq 0 ] && echo || exit 1


exit 0

# Copyright 2017 A. Johannes RICHTER <albrechtjohannes.richter@gmail.com>

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

