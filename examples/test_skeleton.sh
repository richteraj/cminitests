#!/bin/sh

sh_mini_tests="$1"
. "$sh_mini_tests"

tests_start

test_case="The first failing case"
# ...or some useful testing
if true; then
    test_exit=1
else
    test_exit=0
fi
evaluate_test "This went wrong"

# ...
test_case="A good test"
true
evaluate_test

My_other_failing_case ()
{
    # Actual testing
    return 42
}

execute_test_case My_other_failing_case "" "Make the tests green..."

# ...

tests_end

