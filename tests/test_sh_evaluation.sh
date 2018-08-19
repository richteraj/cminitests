#!/bin/sh

sh_mini_tests="$1"
. "$sh_mini_tests"

## Finally exit with this code which will be set by \ref run.  Indicates failure
# of at least one test
run_exit_status=0

## Helper function to print the current test function before executing (in a
# sub-shell) and testing against return status.
#
# \param $1 Function, with no parameters, to call.
# \param $2 Optional return value to test against.  Defaults to zero.
run ()
{
    run_func="$1"
    expected_return="${2:-0}"
    printf "Test %s: ..." "$run_func"
    tmp_out="`mktemp`"
    ( "$run_func" >"$tmp_out" 2>&1 )
    if [ $? -eq "$expected_return" ]; then
        printf "${green}passed$none\n"
        rm -f "$tmp_out"
    else
        printf "${cyan}failed$none with:\n"
        nl "$tmp_out"
        rm -f "$tmp_out"
        run_exit_status=1
    fi
}

Test_suite_passes_with_no_tests ()
{
    tests_start
    tests_end
}

run Test_suite_passes_with_no_tests

Test_suite_passes_if_exit_code_is_zero ()
{
    tests_start
    test_case="This test passes"
    test_exit=0
    evaluate_test
    tests_end
}

run Test_suite_passes_if_exit_code_is_zero

Test_suite_fails_if_exit_code_was_non_zero_once ()
{
    tests_start
    execute_test_case true "Calling true"
    execute_test_case false "Calling false"
    execute_test_case true "Calling true again"
    tests_end
}

run Test_suite_fails_if_exit_code_was_non_zero_once 1

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

run Test_suite_counts_right

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

run Not_setting_exit_code_tests_last_return_code 1

Execute_test_case_works_with_user_functions ()
{
    tests_start
    execute_test_case test_function_true "alternative name"
    [ "$last_test_case" = "alternative name" ] || return 1
    execute_test_case test_function_false "" "true != false"
    [ $tests_failed -eq 1 ] || return 1
}

test_function_true () { true; }
test_function_false () { false; }

run Execute_test_case_works_with_user_functions

Comparing_test_output_to_expected_result ()
{
    tests_start
    expected="Line 1
Line 2

Line 4"
    func=cat
    execute_test_compare "$expected" "$expected" "$func" "Compare identity"
    [ $tests_failed -eq 0 ] || return 1
    func=tac
    execute_test_compare "$expected" "$expected" "$func" "Compare unequal"
    [ $tests_failed -eq 1 ] || return 1
}

run Comparing_test_output_to_expected_result

Variable_test_case_is_reset_after_test ()
{
    test_case="Test case"
    true
    evaluate_test
    [ -z "$test_case" ] || return 1

    test_case="Test case"
    execute_test_case ls
    [ -z "$test_case" ] || return 1

    test_case="Test case"
    execute_test_compare "1234" "1234" cat
    [ -z "$test_case" ] || return 1
}

Variable_test_case_is_set_to_reasonable_default ()
{
    test_case=
    true
    evaluate_test
    [ "$last_test_case" = "Test case $tests_count" ] || return 1

    test_case="execute_test_case: ignore \$test_case"
    execute_test_case ls "ls test"
    [ "$last_test_case" = "ls test" ] || return 1

    test_case="execute_test_case: \$test_case takes priority over \$1"
    execute_test_case ls
    [ "$last_test_case" != "ls" ] || return 1
    [ "$last_test_case" != "Test case $tests_count" ] || return 1

    test_case="execute_test_compare: ignore \$test_case"
    execute_test_compare "1234" "1234" cat "cat test"
    [ "$last_test_case" = "cat test" ] || return 1

    test_case=
    execute_test_compare "1234" "1234" cat
    [ "$last_test_case" = "cat" ] || return 1
}

run Variable_test_case_is_reset_after_test
run Variable_test_case_is_set_to_reasonable_default

exit $run_exit_status

# Copyright 2017, 2018 A. Johannes RICHTER <albrechtjohannes.richter@gmail.com>

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

