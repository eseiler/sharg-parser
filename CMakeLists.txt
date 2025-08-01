# SPDX-FileCopyrightText: 2006-2025, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause

# This file provides functionality common to the different test modules used by
# Sharg. To build tests, run cmake on one of the sub-folders in this directory
# which contain a CMakeLists.txt.

cmake_minimum_required (VERSION 3.12)

find_path (SHARG_MODULE_PATH "sharg-config.cmake" HINTS "${CMAKE_CURRENT_LIST_DIR}/cmake/")
list (APPEND CMAKE_MODULE_PATH "${SHARG_MODULE_PATH}")

include (sharg-config-version)

project (sharg
         LANGUAGES CXX
         VERSION "${SHARG_PROJECT_VERSION}"
         DESCRIPTION "Sharg -- hungrily eating away your arguments"
         HOMEPAGE_URL "https://github.com/seqan/sharg-parser")

include (sharg-config)

option (INSTALL_SHARG "Enable installation of Sharg. (Projects embedding Sharg may want to turn this OFF.)" ON)

if (INSTALL_SHARG)
    include (sharg-install)
    include (sharg-package)
endif ()
