// SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <sharg/all.hpp>

int main(int argc, char const ** argv)
{
    sharg::parser myparser{"Test", argc, argv}; // initialize

    //![validator_call]
    std::vector<int> myint;
    sharg::arithmetic_range_validator my_validator{2, 10};
    // sharg::arithmetic_range_validator{2, 10}
    // &my_validator

    myparser.add_positional_option(
        myint,
        {.description = "Give me a number.", .validator = my_validator});
    //![validator_call]

    // an exception will be thrown if the user specifies an integer
    // that is not in range [2,10] (e.g. "./test_app -i 15")
    try
    {
        myparser.parse();
    }
    catch (sharg::parser_error const & ext) // the user did something wrong
    {
        std::cerr << "[PARSER ERROR] " << ext.what() << "\n"; // customize your error message
        return -1;
    }

    std::cerr << "integer given by user passed validation: ";
    for (auto const & i : myint)
        std::cerr << i << ' ';
    std::cerr << '\n';

    return 0;
}
