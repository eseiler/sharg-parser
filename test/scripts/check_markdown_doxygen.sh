#!/usr/bin/env bash
# SPDX-FileCopyrightText: 2006-2025, Knut Reinert & Freie Universität Berlin
# SPDX-FileCopyrightText: 2016-2025, Knut Reinert & MPI für molekulare Genetik
# SPDX-License-Identifier: BSD-3-Clause
#
# Usage: check_markdown_doxygen.sh <Sharg root directory>
#
# Checks that all markdown files start with a markdown header.
# This is important for Doxygen to correctly parse the markdown files.

ANY_FAIL=0

do_check ()
{
    IS_CORRECT=$(head -n1 "$1" | grep -c "^#" || true)
    if [[ $IS_CORRECT -eq 0 ]]; then
        echo 'File does not start with a markdown header:' $1
        ANY_FAIL=1
    fi
}

if [[ $# -ne 1 ]]; then
    echo "Usage: check_markdown_doxygen.sh <Sharg root directory>"
    exit 1
fi

SHARG_ROOT=$(readlink -f "$1")

if [[ ! -d ${SHARG_ROOT} ]]; then
    echo "The directory ${SHARG_ROOT} does not exist."
    exit 1
fi

if [[ ! -f ${SHARG_ROOT}/include/sharg/version.hpp ]]; then
    echo "The directory ${SHARG_ROOT} does not seem to be the Sharg root directory."
    echo "Cannot find ${SHARG_ROOT}/include/sharg/version.hpp."
    exit 1
fi

for FILE in $(find "${SHARG_ROOT}/doc" -name "*.md" -and -not -path "${SHARG_ROOT}/doc/fragments/*")
do
    do_check $FILE
done

for FILE in $(find "${SHARG_ROOT}" -maxdepth 1 -name "*.md")
do
    do_check $FILE
done

exit $ANY_FAIL
