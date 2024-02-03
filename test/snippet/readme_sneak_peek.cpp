// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#define main test

#include <sharg/all.hpp>

int main(int argc, char ** argv)
{
    // std::vector<std::string> args{"./Eat-Me-App", "-h"};

    int val{};

    sharg::parser parser{sharg::parser_config{.app_name = "Eat-Me-App", .arguments = {argv, argv + argc}}};
    parser.add_subsection("Eating Numbers");
    parser.add_option(val, sharg::config{.short_id = 'i', .long_id = "int", .description = "Desc."});
    parser.parse();

    return 0;
}
