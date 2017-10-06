file (GLOB srcs test_*.c)
foreach (test_source IN LISTS srcs)
    get_filename_component (test_target ${test_source} NAME_WE)
    add_executable (${test_target} ${test_source})
    target_include_directories (${test_target} PRIVATE ${src_DIR})

    add_test (NAME ${test_target} COMMAND ${test_target})
endforeach (test_source)

if (${sh_PROG_HAVE})
    file (GLOB srcs test_*.sh)
    foreach (sh_test_source IN LISTS srcs)
        get_filename_component (test_target ${sh_test_source} NAME_WE)
        add_test (NAME ${test_target}
            COMMAND ${sh_PROG} "${sh_test_source}" "${src_DIR}/shminitests.sh")
    endforeach (sh_test_source)
endif ()

# CMakeLists.txt - CMake tests files
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
