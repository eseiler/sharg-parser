// SPDX-FileCopyrightText: 2006-2024, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

/*!\file
 * \author Svenja Mehringer <svenja.mehringer AT fu-berlin.de>
 * \brief Meta-header for the \link parser Parser module \endlink.
 */

/*!\defgroup parser Parser
 * \brief The Parser Module
 *
 * # The Parser Class
 *
 * \copydetails sharg::parser
 *
 * # Parsing Command Line Arguments
 *
 * \copydetails sharg::parser::parse
 *
 * # Argument Validation
 *
 * The Sharg Parser offers a validation mechanism for (positional_)options
 * via callables. You can pass any functor that fulfils the sharg::validator
 * and takes the value passed to the add_(positional_)option function call as
 * a parameter. We provide some commonly used functor that might come in handy:
 *
 * - sharg::regex_validator
 * - sharg::value_list_validator
 * - sharg::arithmetic_range_validator
 * - sharg::input_file_validator
 * - sharg::output_file_validator
 * - sharg::input_directory_validator
 * - sharg::output_directory_validator
 */

// Groups will appear in order they are defined.

/*!\defgroup exceptions Exceptions
 * \brief The Exceptions Module
 */

/*!\defgroup validators Validators
 * \brief The Validators Module
 */

/*!\defgroup misc Misc
 * \brief The Misc Module
 */

#pragma once

#include <sharg/auxiliary.hpp>
#include <sharg/exceptions.hpp>
#include <sharg/parser.hpp>
#include <sharg/validators.hpp>
