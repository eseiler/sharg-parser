// SPDX-FileCopyrightText: 2006-2025, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

#include <gtest/gtest.h>

#include <sharg/parser.hpp>
#include <sharg/test/test_fixture.hpp>

// Reused global variables
class format_man_test : public sharg::test::test_fixture
{
protected:
    int option_value{5};
    bool flag_value{false};
    int8_t non_list_pos_opt_value{1};
    std::vector<std::string> list_pos_opt_value{};
    std::string my_stdout{};

    static inline std::string version_str{sharg::sharg_version_cstring};
    static inline std::string expected =
        R"(.TH TEST_PARSER 1 "December 01, 1994" "test_parser 01.01.01" "default_man_page_title")"
        "\n"
        R"(.SH NAME)"
        "\n"
        R"(test_parser \- A short description here.)"
        "\n"
        R"(.SH SYNOPSIS)"
        "\n"
        R"(\fB./format_man_test\fP synopsis)"
        "\n"
        R"(.br)"
        "\n"
        R"(\fB./format_man_test\fP synopsis2)"
        "\n"
        R"(.SH DESCRIPTION)"
        "\n"
        R"(description)"
        "\n"
        R"(.sp)"
        "\n"
        R"(description2)"
        "\n"
        R"(.SH POSITIONAL ARGUMENTS)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fBARGUMENT-1\fP (\fIsigned 8 bit integer\fP))"
        "\n"
        R"(this is a positional option.)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fBARGUMENT-2\fP (\fIList\fP of \fIstd::string\fP))"
        "\n"
        R"(this is a positional option. Default: [])"
        "\n"
        R"(.SH OPTIONS)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB-i\fP, \fB--int\fP (\fIsigned 32 bit integer\fP))"
        "\n"
        R"(this is a int option. Default: A number)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB-j\fP, \fB--jint\fP (\fIsigned 32 bit integer\fP))"
        "\n"
        R"(this is a required int option.)"
        "\n"
        R"(.SH FLAGS)"
        "\n"
        R"(.SS SubFlags)"
        "\n"
        R"(here come all the flags)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB-f\fP, \fB--flag\fP)"
        "\n"
        R"(this is a flag.)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB-k\fP, \fB--kflag\fP)"
        "\n"
        R"(this is a flag.)"
        "\n"
        R"(.SS Common options)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB-h\fP, \fB--help\fP)"
        "\n"
        R"(Prints the help page.)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB-hh\fP, \fB--advanced-help\fP)"
        "\n"
        R"(Prints the help page including advanced options.)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB--version\fP)"
        "\n"
        R"(Prints the version information.)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB--copyright\fP)"
        "\n"
        R"(Prints the copyright/license information.)"
        "\n"
        R"(.TP)"
        "\n"
        R"(\fB--export-help\fP (std::string))"
        "\n"
        R"(Export the help page information. Value must be one of )"
#if SHARG_HAS_TDL
        "[html, man, ctd, cwl]."
#else
        "[html, man]."
#endif
        "\n"
        R"(.SH EXAMPLES)"
        "\n"
        R"(example)"
        "\n"
        R"(.sp)"
        "\n"
        R"(example2)"
        "\n"
        R"(.SH VERSION)"
        "\n"
        R"(\fBLast update: \fRDecember 01, 1994)"
        "\n"
        R"(.br)"
        "\n"
        R"(\fBtest_parser version: \fR01.01.01)"
        "\n"
        R"(.br)"
        "\n"
        R"(\fBSharg version: \fR)"
        + version_str + "\n";

    // Full info parser initialisation
    void dummy_init(sharg::parser & parser)
    {
        parser.info.date = "December 01, 1994";
        parser.info.version = "01.01.01";
        parser.info.man_page_title = "default_man_page_title";
        parser.info.short_description = "A short description here.";
        parser.info.synopsis.push_back("./format_man_test synopsis");
        parser.info.synopsis.push_back("./format_man_test synopsis2");
        parser.info.description.push_back("description");
        parser.info.description.push_back("description2");
        parser.add_option(option_value,
                          sharg::config{.short_id = 'i',
                                        .long_id = "int",
                                        .description = "this is a int option.",
                                        .default_message = "A number"});
        parser.add_option(option_value,
                          sharg::config{.short_id = 'j',
                                        .long_id = "jint",
                                        .description = "this is a required int option.",
                                        .required = true});
        parser.add_section("Flags");
        parser.add_subsection("SubFlags");
        parser.add_line("here come all the flags");
        parser.add_flag(flag_value,
                        sharg::config{.short_id = 'f', .long_id = "flag", .description = "this is a flag."});
        parser.add_flag(flag_value,
                        sharg::config{.short_id = 'k', .long_id = "kflag", .description = "this is a flag."});
        parser.add_positional_option(non_list_pos_opt_value,
                                     sharg::config{.description = "this is a positional option."});
        parser.add_positional_option(list_pos_opt_value, sharg::config{.description = "this is a positional option."});
        parser.info.examples.push_back("example");
        parser.info.examples.push_back("example2");
    }
};

TEST_F(format_man_test, empty_information)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");
    parser.info.date = "December 01, 1994";
    parser.info.version = "01.01.01";
    parser.info.man_page_title = "default_man_page_title";
    parser.info.short_description = "A short description here.";

    std::string expected = R"(.TH TEST_PARSER 1 "December 01, 1994" "test_parser 01.01.01" "default_man_page_title")"
                           "\n"
                           R"(.SH NAME)"
                           "\n"
                           R"(test_parser \- A short description here.)"
                           "\n"
                           R"(.SH OPTIONS)"
                           "\n"
                           R"(.SS Common options)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-h\fP, \fB--help\fP)"
                           "\n"
                           R"(Prints the help page.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB-hh\fP, \fB--advanced-help\fP)"
                           "\n"
                           R"(Prints the help page including advanced options.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--version\fP)"
                           "\n"
                           R"(Prints the version information.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--copyright\fP)"
                           "\n"
                           R"(Prints the copyright/license information.)"
                           "\n"
                           R"(.TP)"
                           "\n"
                           R"(\fB--export-help\fP (std::string))"
                           "\n"
                           R"(Export the help page information. Value must be one of )"
#if SHARG_HAS_TDL
                           "[html, man, ctd, cwl]."
#else
                           "[html, man]."
#endif
                           "\n"
                           R"(.SH VERSION)"
                           "\n"
                           R"(\fBLast update: \fRDecember 01, 1994)"
                           "\n"
                           R"(.br)"
                           "\n"
                           R"(\fBtest_parser version: \fR01.01.01)"
                           "\n"
                           R"(.br)"
                           "\n"
                           R"(\fBSharg version: \fR)"
                         + version_str + "\n";
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}

TEST_F(format_man_test, full_information)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);

    // Test the dummy parser without any copyright or citations.
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}

TEST_F(format_man_test, full_info_short_copyright)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);

    // Add a short copyright and test the dummy parser.
    parser.info.short_copyright = "short copyright";

    std::string expected = this->expected + R"(.SH LEGAL
\fBtest_parser Copyright: \fRshort copyright
.br
\fBSeqAn Copyright: \fR2006-2025 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
)";
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}

TEST_F(format_man_test, full_info_short_and_citation)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);

    // Add a short copyright & citation and test the dummy parser.
    parser.info.short_copyright = "short copyright";
    parser.info.citation = "citation";

    std::string expected = this->expected + R"(.SH LEGAL
\fBtest_parser Copyright: \fRshort copyright
.br
\fBSeqAn Copyright: \fR2006-2025 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
.br
\fBIn your academic works please cite: \fRcitation
)";
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}

TEST_F(format_man_test, full_info_short_long_and_citation)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);

    // Add a short copyright & citation & long copyright and test the dummy parser.
    parser.info.short_copyright = "short copyright";
    parser.info.citation = "citation";
    parser.info.long_copyright = "looong copyright";

    std::string expected = this->expected + R"(.SH LEGAL
\fBtest_parser Copyright: \fRshort copyright
.br
\fBSeqAn Copyright: \fR2006-2025 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
.br
\fBIn your academic works please cite: \fRcitation
.br
For full copyright and/or warranty information see \fB--copyright\fR.
)";
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}

TEST_F(format_man_test, full_info_author)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);

    // Add a short copyright and test the dummy parser.
    parser.info.author = "author";

    std::string expected = this->expected + R"(.SH LEGAL
\fBAuthor: \fRauthor
.br
\fBSeqAn Copyright: \fR2006-2025 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
)";
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}

TEST_F(format_man_test, full_info_email)
{
    // Create the dummy parser.
    auto parser = get_parser("--version-check", "false", "--export-help", "man");

    // Fill out the dummy parser with options and flags and sections and subsections.
    dummy_init(parser);

    // Add a short copyright and test the dummy parser.
    parser.info.email = "email";

    std::string expected = this->expected + R"(.SH LEGAL
\fBContact: \fRemail
.br
\fBSeqAn Copyright: \fR2006-2025 Knut Reinert, FU-Berlin; released under the 3-clause BSDL.
)";
    EXPECT_EQ(get_parse_cout_on_exit(parser), expected);
}
