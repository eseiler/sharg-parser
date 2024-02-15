// SPDX-FileCopyrightText: 2006-2024, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

/*!\file
 * \author Enrico Seiler <enrico.seiler AT fu-berlin.de>
* \brief Provides the format_empty class.
 */

#pragma once

#include <variant>

#include <sharg/auxiliary.hpp>
#include <sharg/config.hpp>

namespace sharg::detail
{

//!\brief A class that is used as an equivalent to std::monotype in sharg::parser::format.
class format_empty : public std::monostate
// LCOV_EXCL_START
{
public:
    //!\brief Throws if called.
    template <typename option_type, typename validator_t>
    void add_option(option_type &, config<validator_t> const &)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    template <typename validator_t>
    void add_flag(bool &, config<validator_t> const &)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    template <typename option_type, typename validator_t>
    void add_positional_option(option_type &, config<validator_t> const &)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    void parse(parser_meta_data &)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    void add_section(std::string const &, bool const)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    void add_subsection(std::string const &, bool const)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    void add_line(std::string const &, bool, bool const)
    {
        throw std::logic_error{"This format should never be used."};
    }

    //!\brief Throws if called.
    void add_list_item(std::string const &, std::string const &, bool const)
    {
        throw std::logic_error{"This format should never be used."};
    }
};
// LCOV_EXCL_STOP

} // namespace sharg::detail
