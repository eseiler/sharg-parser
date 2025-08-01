// SPDX-FileCopyrightText: 2006-2025, Knut Reinert & Freie Universität Berlin
// SPDX-FileCopyrightText: 2016-2025, Knut Reinert & MPI für molekulare Genetik
// SPDX-License-Identifier: BSD-3-Clause

/*!\file
 * \author Lydia Buntrock <lydia.buntrock AT fu-berlin.de>
 * \brief Internal test infrastructure.
 *        Define some helper classes and functions for the tests that would be misplaced in the sharg/include
 *        directory.
 */

#pragma once

// Add support for Windows platforms, when we support it.
#if defined(__APPLE__)
#    include <unistd.h>
#elif defined(_WIN32)
#    include <cstring>
#    include <io.h>
#else // other unix systems
#    include <stdlib.h>
#endif

#include <filesystem>

#include <sharg/platform.hpp>

namespace sharg::test
{

#if defined(_WIN32)
inline char * mkdtemp(char * template_name)
{
    if (_mktemp_s(template_name, strlen(template_name) + 1))
        return nullptr;

    if (std::filesystem::create_directories(template_name))
        return template_name;

    return nullptr;
}
#endif

/*!\brief Creates and maintains a std::filesystem::path to a temporary file.
 * Creates a temporary unique file directory and adds the given file name to construct a std::filesystem::path.
 * It automatically removes the temporary directory and all contained files and subdirectories on destruction.
 * The class manages the life time of the associated directory. This means, when the instance is destructed,
 * the associated filesystem directory and all its contents will be deleted automatically.
 * Hence, an instance of this class cannot be copied.
 *
 * ### Example
 *
 * ```cpp
 * tmp_filename fn{"my_file"};
 * std::cout << fn.get_path() << std::endl;
 * ```
 *
 * ### Exceptions
 *
 * Might throw a std::filesystem::filesystem_error on failure to create a temporary file directory.
 *
 * ### Thread safety
 *
 *  According to "https://www.gnu.org/software/libc/manual/html_node/Temporary-Files.html", the call to
 * \a mkdtemp is thread safe, such that creating multiple parallel instances of this class will
 * not introduce a data race on the creation of temporary file path.
 */
class tmp_filename
{
public:
    /*!\name Constructors, destructor and assignment
     * \{
     */
    tmp_filename() = delete;                                 //!< Deleted.
    tmp_filename(tmp_filename const &) = delete;             //!< Deleted.
    tmp_filename(tmp_filename &&) = default;                 //!< Defaulted.
    tmp_filename & operator=(tmp_filename const &) = delete; //!< Deleted.
    tmp_filename & operator=(tmp_filename &&) = default;     //!< Defaulted.

    /*!\brief Constructs temp path with given file name.
     * \param f_name The name of the file.
     *
     * The generated file name is unique due to a call to \a mkdtemp.
     *
     * ###Exceptions
     * Might throw std::filesystem::filesystem_error.
     */
    explicit tmp_filename(char const * f_name)
    {
        if (f_name == nullptr)
            throw std::filesystem::filesystem_error("Empty file name!",
                                                    std::make_error_code(std::errc::invalid_argument));

        auto tmp_base_dir = std::filesystem::temp_directory_path();
        tmp_base_dir /= std::filesystem::path{"seqan_test_XXXXXXXX"};
        // We have to use mkdtemp, which is not deprecated. We place it into the dedicated tmp_dir
        // returned by temp_directory_path. Within this path we can safely create files, that would be
        // unique per test instance as the parent directory is.
        auto path_str = tmp_base_dir.string(); // Copy the underlying path to get access to the raw char *.
        if (char * f = mkdtemp(path_str.data()); f != nullptr) // mkdtemp replaces XXXXXXXX in a safe and unique way.
        {
            directory_path = f;
            file_path = directory_path / std::filesystem::path{f_name};
            return;
        }
        throw std::filesystem::filesystem_error("Could not create temporary directory with mkdtemp!",
                                                tmp_base_dir,
                                                std::make_error_code(std::errc::bad_file_descriptor));
    }

    /*!\brief Destructs the temporary directory path.
     *
     * \details
     *
     * Removes the temporary directory and all its subdirectories and files contained.
     */
    ~tmp_filename()
    {
        [[maybe_unused]] std::error_code ec;
        std::filesystem::remove_all(directory_path, ec);
    }
    //!\}

    /*!\brief Returns a const reference to the path object.
     * \returns std::filesystem::path containing the path of the file.
     */
    std::filesystem::path const & get_path() const
    {
        return file_path;
    }

private:
    //!\brief The object storing the path to the temporary file.
    std::filesystem::path file_path{};
    //!\brief The object storing the path to the temporary directory.
    std::filesystem::path directory_path{};
};

} // namespace sharg::test
