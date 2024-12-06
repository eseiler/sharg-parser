# SPDX-FileCopyrightText: 2006-2024, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause

cmake_minimum_required (VERSION 3.16)

# Exposes the google-test targets `gtest` and `gtest_main`.
# CMake 3.24: https://cmake.org/cmake/help/latest/module/FetchContent.html#variable:FETCHCONTENT_TRY_FIND_PACKAGE_MODE
macro (sharg_require_test)
    enable_testing ()

    set (gtest_version "1.15.2")
    set (gtest_git_tag "v${gtest_version}")

    find_package (GTest ${gtest_version} EXACT QUIET)

    if (NOT GTest_FOUND)
        message (STATUS "Fetching Google Test ${gtest_version}")

        include (FetchContent)
        FetchContent_Declare (
            gtest_fetch_content
            GIT_REPOSITORY "https://github.com/google/googletest.git"
            GIT_TAG "${gtest_git_tag}")
        option (BUILD_GMOCK "" OFF)
        option (INSTALL_GTEST "" OFF)
        FetchContent_MakeAvailable (gtest_fetch_content)
    else ()
        message (STATUS "Found Google Test ${gtest_version}")
    endif ()

    if (NOT TARGET gtest_build)
        add_custom_target (gtest_build DEPENDS gtest_main gtest)
    endif ()

endmacro ()
