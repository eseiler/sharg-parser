// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <sharg/all.hpp>

int main(int argc, char ** argv)
{
    sharg::parser myparser{"awesome-app", argc, argv}; // initialize

    int a{3};
    myparser.add_option(a, sharg::config{.short_id = 'a', .long_id = "aint", .description = "Specify an integer."});

    try
    {
        myparser.parse();
    }
    catch (sharg::parser_error const & ext) // the user did something wrong
    {
        std::cerr << "[PARSER ERROR] " << ext.what() << '\n'; // customize your error message
        return -1;
    }

    if (myparser.is_option_set('a'))
        std::cerr << "The user set option -a on the command line.\n";

    if (myparser.is_option_set("awesome-parameter"))
        std::cerr << "The user set option --awesome-parameter on the command line.\n";

    // Asking for an option identifier that was not used before throws an error:
    // myparser.is_option_set("foo"); // throws sharg::design_error

    return 0;
}
