# SPDX-FileCopyrightText: 2006-2024, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause

# This file provides functionality common to the different test modules used by
# SeqAn3. To build tests, run cmake on one of the sub-folders in this directory
# which contain a CMakeLists.txt.

cmake_minimum_required (VERSION 3.12)

# require Sharg package
find_package (Sharg REQUIRED HINTS ${CMAKE_CURRENT_LIST_DIR}/../cmake)

enable_testing ()

set (CPM_INDENT "CMake Package Manager CPM: ")
CPMUsePackageLock ("${CMAKE_CURRENT_LIST_DIR}/../cmake/package-lock.cmake")

include (CheckCXXSourceCompiles)
include (FindPackageHandleStandardArgs)
include (FindPackageMessage)

option (SHARG_TEST_BUILD_OFFLINE "Skip the update step of external projects." OFF)

# ----------------------------------------------------------------------------
# Paths to folders.
# ----------------------------------------------------------------------------

find_path (SHARG_TEST_INCLUDE_DIR
           NAMES sharg/test/tmp_filename.hpp
           HINTS "${CMAKE_CURRENT_LIST_DIR}/include/")
find_path (SHARG_TEST_CMAKE_MODULE_DIR
           NAMES sharg_test_component.cmake
           HINTS "${CMAKE_CURRENT_LIST_DIR}/cmake/")
list (APPEND CMAKE_MODULE_PATH "${SHARG_TEST_CMAKE_MODULE_DIR}")

# ----------------------------------------------------------------------------
# Interface targets for the different test modules in seqan3.
# ----------------------------------------------------------------------------

# sharg::test exposes a base set of required flags, includes, definitions and
# libraries which are in common for **all** seqan3 tests
if (NOT TARGET sharg::test)
    add_library (sharg_test INTERFACE)
    target_compile_options (sharg_test INTERFACE "-pedantic" "-Wall" "-Wextra" "-Werror")

    # GCC12 and above: Disable warning about std::hardware_destructive_interference_size not being ABI-stable.
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
        if (CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 12)
            target_compile_options (sharg_test INTERFACE "-Wno-interference-size")
        endif ()
    endif ()

    target_link_libraries (sharg_test INTERFACE "sharg::sharg" "pthread")
    target_include_directories (sharg_test INTERFACE "${SHARG_TEST_INCLUDE_DIR}")
    add_library (sharg::test ALIAS sharg_test)
endif ()

# sharg::test::unit specifies required flags, includes and libraries
# needed for unit test cases in sharg/test/unit
if (NOT TARGET sharg::test::unit)
    add_library (sharg_test_unit INTERFACE)
    target_link_libraries (sharg_test_unit INTERFACE "sharg::test" "GTest::gtest_main")
    add_library (sharg::test::unit ALIAS sharg_test_unit)
endif ()

# sharg::test::coverage specifies required flags, includes and libraries
# needed for coverage test cases in sharg/test/coverage
if (NOT TARGET sharg::test::coverage)
    add_library (sharg_test_coverage INTERFACE)
    target_compile_options (sharg_test_coverage INTERFACE "--coverage" "-fprofile-arcs" "-ftest-coverage")
    # -fprofile-abs-path requires at least gcc8, it forces gcov to report absolute instead of relative paths.
    # gcovr has trouble detecting the headers otherwise.
    # ccache is not aware of this option, so it needs to be skipped with `--ccache-skip`.
    find_program (CCACHE_PROGRAM ccache)
    if (CCACHE_PROGRAM)
        target_compile_options (sharg_test_coverage INTERFACE "--ccache-skip" "-fprofile-abs-path")
    else ()
        target_compile_options (sharg_test_coverage INTERFACE "-fprofile-abs-path")
    endif ()
    target_link_libraries (sharg_test_coverage INTERFACE "sharg::test::unit" "gcov")
    add_library (sharg::test::coverage ALIAS sharg_test_coverage)
endif ()

# sharg::test::header specifies required flags, includes and libraries
# needed for header test cases in sharg/test/header
if (NOT TARGET sharg::test::header)
    add_library (sharg_test_header INTERFACE)
    target_link_libraries (sharg_test_header INTERFACE "sharg::test::unit")
    target_compile_options (sharg_test_header INTERFACE "-Wno-unused-const-variable")
    target_compile_definitions (sharg_test_header INTERFACE -DSHARG_DISABLE_DEPRECATED_WARNINGS)
    target_compile_definitions (sharg_test_header INTERFACE -DSHARG_HEADER_TEST)
    add_library (sharg::test::header ALIAS sharg_test_header)
endif ()

# ----------------------------------------------------------------------------
# Commonly shared options for external projects.
# ----------------------------------------------------------------------------

set (SHARG_EXTERNAL_PROJECT_CMAKE_ARGS "")
list (APPEND SHARG_EXTERNAL_PROJECT_CMAKE_ARGS "-DCMAKE_CXX_COMPILER=${CMAKE_CXX_COMPILER}")
list (APPEND SHARG_EXTERNAL_PROJECT_CMAKE_ARGS "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
list (APPEND SHARG_EXTERNAL_PROJECT_CMAKE_ARGS "-DCMAKE_INSTALL_PREFIX=${PROJECT_BINARY_DIR}")
list (APPEND SHARG_EXTERNAL_PROJECT_CMAKE_ARGS "-DCMAKE_VERBOSE_MAKEFILE=${CMAKE_VERBOSE_MAKEFILE}")

# ----------------------------------------------------------------------------
# Commonly used macros for the different test modules in seqan3.
# ----------------------------------------------------------------------------

include (sharg_test_component)
include (sharg_test_files)
include (sharg_require_ccache)
include (add_subdirectories)
