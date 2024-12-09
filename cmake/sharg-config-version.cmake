# SPDX-FileCopyrightText: 2006-2024, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2024, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause

# This file adds version support for `find_package(SHARG 3.1)`.
# See https://cmake.org/cmake/help/v3.16/manual/cmake-packages.7.html#package-version-file for more information.
#
# This file was partially generated by
# https://cmake.org/cmake/help/v3.16/module/CMakePackageConfigHelpers.html#command:write_basic_package_version_file

# Note that sharg-config.cmake can be standalone and thus SHARG_CLONE_DIR might be empty.
find_path (SHARG_CLONE_DIR
           NAMES cmake/sharg-config.cmake
           HINTS "${CMAKE_CURRENT_LIST_DIR}/..")
find_path (SHARG_INCLUDE_DIR
           NAMES sharg/version.hpp
           HINTS "${SHARG_CLONE_DIR}/include")

# extract version from sharg/version.hpp header
file (STRINGS "${SHARG_INCLUDE_DIR}/sharg/version.hpp" SHARG_VERSION_HPP
      REGEX "#define SHARG_VERSION_(MAJOR|MINOR|PATCH)")
string (REGEX REPLACE "#define SHARG_VERSION_(MAJOR|MINOR|PATCH) " "" PACKAGE_VERSION "${SHARG_VERSION_HPP}")
string (REGEX REPLACE ";" "." PACKAGE_VERSION "${PACKAGE_VERSION}")

if (PACKAGE_VERSION VERSION_LESS PACKAGE_FIND_VERSION)
    set (PACKAGE_VERSION_COMPATIBLE FALSE)
else ()

    if (PACKAGE_VERSION MATCHES "^([0-9]+)\\.")
        set (_PACKAGE_VERSION_MAJOR "${CMAKE_MATCH_1}")
    endif ()

    if (PACKAGE_FIND_VERSION_MAJOR STREQUAL _PACKAGE_VERSION_MAJOR)
        set (PACKAGE_VERSION_COMPATIBLE TRUE)
    else ()
        set (PACKAGE_VERSION_COMPATIBLE FALSE)
    endif ()

    if (PACKAGE_FIND_VERSION STREQUAL PACKAGE_VERSION)
        set (PACKAGE_VERSION_EXACT TRUE)
    endif ()
endif ()

# extract release candidate and store in SHARG_RELEASE_CANDIDATE_VERSION
file (STRINGS "${SHARG_INCLUDE_DIR}/sharg/version.hpp" SHARG_RELEASE_CANDIDATE_HPP
      REGEX "#define SHARG_RELEASE_CANDIDATE ")
string (REGEX REPLACE "#define SHARG_RELEASE_CANDIDATE " "" SHARG_RELEASE_CANDIDATE_VERSION
                      "${SHARG_RELEASE_CANDIDATE_HPP}")

# As of writing this (cmake 3.20):
# cmake does not allow to set a version containing a suffix via `project(... VERSION 3.0.3-rc.1)`.
# Version comparisons like VERSION_LESS, VERSION_GREATER do support comparing versions with a suffix (they just drop
# it), see https://cmake.org/cmake/help/latest/command/if.html#version-comparisons.
#
# If https://gitlab.kitware.com/cmake/cmake/-/issues/16716 is ever resolved, we can use SHARG_VERSION instead of
# SHARG_PROJECT_VERSION.
#
# SHARG_PROJECT_VERSION is intended to be used within `project (... VERSION "${SHARG_PROJECT_VERSION}")`.
set (SHARG_PROJECT_VERSION "${PACKAGE_VERSION}")
if (SHARG_RELEASE_CANDIDATE_VERSION VERSION_GREATER "0")
    set (PACKAGE_VERSION "${PACKAGE_VERSION}-rc.${SHARG_RELEASE_CANDIDATE_VERSION}")
endif ()

if (NOT SHARG_PROJECT_VERSION VERSION_EQUAL PACKAGE_VERSION)
    # Note: depending on how https://gitlab.kitware.com/cmake/cmake/-/issues/16716 is resolved (whether they use semver
    # comparison semantics), (NOT "3.0.3" VERSION_GREATER_EQUAL "3.0.3-rc.1") might be the correct expression.
    message (AUTHOR_WARNING "SHARG_PROJECT_VERSION and SHARG_VERSION mismatch, "
                            "please report this issue and mention your cmake version.")
endif ()

# if the installed or the using project don't have CMAKE_SIZEOF_VOID_P set, ignore it:
if ("${CMAKE_SIZEOF_VOID_P}" STREQUAL "")
    return ()
endif ()

# check that the installed version has the same 32/64bit-ness as the one which is currently searching:
if (NOT "${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    math (EXPR installedBits "8 * 8")
    # For some time we set these variables to show that we do not support 32 bit architectures,
    # but it seems to hard to actively forbid them. Most of the library does build, but some parts
    # might not.
    # set(PACKAGE_VERSION "${PACKAGE_VERSION} (${installedBits}bit)")
    # set(PACKAGE_VERSION_UNSUITABLE TRUE)
    message (AUTHOR_WARNING "B.I.O. does not support 32bit architectures; No guarantees; Patches are welcome.")
endif ()