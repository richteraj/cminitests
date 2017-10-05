set (test_target "test_skeleton")
add_executable (${test_target} "${test_target}.c")
target_include_directories (${test_target} PRIVATE ${src_DIR})

add_test (NAME ${test_target} COMMAND ${test_target})
set_tests_properties (${test_target} PROPERTIES WILL_FAIL 1)

# CMakeLists.txt - CMake tests files for examples
# Copyright 2017 A. Johannes RICHTER <albrechtjohannes.richter@gmail.com>
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
