// SPDX-FileCopyrightText: 2006-2025 Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025 Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: CC0-1.0

#include <sharg/all.hpp>

int main(int argc, char const ** argv)
{
    sharg::parser myparser{"Test", argc, argv}; // initialize

    //![validator_call]
    std::filesystem::path myfile;
    auto vali = sharg::input_file_validator{{"fa", "fasta"}};

    myparser.add_option(
        myfile,
        sharg::config{.short_id = 'f', .long_id = "file", .description = "Give me a filename.", .validator = vali});
    //![validator_call]

    // an exception will be thrown if the user specifies a filename
    // that does not have one of the extensions ["fa","fasta"],
    // does not exists, or is not readable.
    try
    {
        myparser.parse();
    }
    catch (sharg::parser_error const & ext) // the user did something wrong
    {
        std::cerr << "[PARSER ERROR] " << ext.what() << "\n"; // customize your error message
        return -1;
    }

    std::cerr << "filename given by user passed validation: " << myfile << "\n";
    return 0;
}
