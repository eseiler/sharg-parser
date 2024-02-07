# Quick Setup (using CMake) {#setup}

<!--
SPDX-FileCopyrightText: 2006-2024 Knut Reinert & Freie Universität Berlin
SPDX-FileCopyrightText: 2016-2024 Knut Reinert & MPI für molekulare Genetik
SPDX-License-Identifier: CC-BY-4.0
-->

<b>Learning Objective:</b><br>
In this short guide you will learn how to set up Sharg and how to compile a small example to test whether everything
works.

\tutorial_head{Easy, 30 Minutes, No prerequisites, }

[TOC]

<br>

# Software
Requirements:
  - gcc >= 11 or clang >= 17
  - cmake >= 3.16
  - git

## Installing GCC

Sharg requires GCC >= 11 or LLVM/Clang >= 17. Current versions of VisualStudio/MSVC are **not yet supported**.
We will briefly explain how to install GCC-11 (or the latest GCC if such an option is available) on some popular
operating systems. We recommend using the latest version of GCC available. For more information, refer to your
operating system's documentation.

\startcollapsible{Linux-based}

#### Ubuntu >= 22.04
```bash
# Installs default compiler version (gcc-11 for Ubuntu 22.04).
sudo apt install g++
# To install gcc-12, follow below instructions.
```

#### Ubuntu < 22.04
```bash
sudo add-apt-repository --no-update --yes ppa:ubuntu-toolchain-r/ppa
sudo add-apt-repository --no-update --yes ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt install g++-11
```

#### Using [conda](https://conda.io)
To avoid interference with system packages, we recommend creating a new environment when using conda.
```bash
conda create -n conda_gcc_env -c conda-forge gcc_linux-64
conda activate conda_gcc_env
```
This will put GCC in a separate environment `conda_gcc_env` which can be activated via `conda activate conda_gcc_env`
and deactivated via `conda deactivate`.

\endcollapsible

\startcollapsible{macOS}

#### Using [Homebrew](https://brew.sh/)
```bash
brew install gcc@11
```

#### Using [MacPorts](https://www.macports.org/)
```bash
sudo port install gcc11
```

\endcollapsible

\startcollapsible{Windows}

#### Using [WSL](https://docs.microsoft.com/en-us/windows/wsl/about)
The Windows Subsystem for Linux offers an easy way to run a Linux distribution under Windows.
Follow [Microsoft's setup guide](https://docs.microsoft.com/en-us/windows/wsl/about) to install WSL and then follow
the steps listed for Linux-based systems.

\endcollapsible

\startcollapsible{Browser-based}

#### Using [gitpod.io](https://gitpod.io/#https://github.com/seqan/sharg-parser/)
[gitpod.io](https://gitpod.io) allows you to edit, compile and run code from within your browser. The free version
includes 50 hours of use per month, which is plenty for our tutorials. A GitHub account is required.
[Click here](https://gitpod.io/#https://github.com/seqan/sharg-parser/) to open Sharg in gitpod.

<!-- Codespaces are currently not free. Revisit in the future.
#### Using [GitHub codespaces](https://github.com/codespaces)
GitHub offers a service similar to gitpod. Codespaces are currently in **public beta** and may not be available to
everyone. [Click here](https://github.com/codespaces) to check for availability.

Please note that you may have to manually clone the submodules by running `git submodule update --init`.
-->

\endcollapsible

\attention After installing, `g++ --version` should print the desired version.
           If not, you may have to use, for example, `g++-11 --version` or even specify the full path to your compiler.

Similarly, you may need to install CMake and git, e.g. `apt install cmake git`.

# Directory Structure
In this section we will use the `tree` command to show the directory structure. This program may not be installed
on your system. If so, you may wish to install it or verify the directory structure in other ways, e.g. by using
`ls -l`.

For this project, we recommend following directory layout:

```
tutorial
├── build
├── sharg-parser
└── source
```

To set these directories up you can follow this script:
```bash
mkdir tutorial
cd tutorial
mkdir build
mkdir source
git clone https://github.com/seqan/sharg-parser.git
cd sharg-parser
git submodule update --init
cd ..
```

The output of the command `tree -L 2` should now look like this:
```
.
├── build
├── sharg-parser
│   ├── CHANGELOG.md
│   ├── CMakeLists.txt
│   ├── CODE_OF_CONDUCT.md
│   ├── CONTRIBUTING.md
│   ├── LICENSE.md
│   ├── README.md
│   ├── build_system
│   ├── doc
│   ├── include
│   ├── submodules
│   └── test
└── source

7 directories, 6 files
```

# Compiling and Running

To test whether everything works, we will now compile and run a small example.

First we create the file `hello_world.cpp` in the `source` directory with the following contents:

```
#include <sharg/core/debug_stream.hpp>

int main()
{
    sharg::debug_stream << "Hello World!\n";
    return 0;
}
```

To compile it, we first create a `CMakeLists.txt` file in the `source` directory:

```
cmake_minimum_required (VERSION 3.16)
project (sharg_tutorial CXX)

# add sharg to search path
list (APPEND CMAKE_PREFIX_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../sharg/build_system")

# require sharg with a version >=1.0.0
find_package (sharg 1.0 REQUIRED)

# build app with sharg
add_executable (hello_world hello_world.cpp)
target_link_libraries (hello_world sharg::sharg)
```

The directories should now look like this:

```
.
├── build
├── sharg-parser
│   ├── build_system
│   ├── ...
│   └── test
└── source
    ├── CMakeLists.txt
    └── hello_world.cpp
```

Now we can switch to the directory `build` and run:

```bash
cmake -DCMAKE_BUILD_TYPE=Release ../source
make
./hello_world
```

The output should be `Hello World!`. Note that the build type is specified with `-DCMAKE_BUILD_TYPE=Release`.
Specifying `Release` enables an optimized build where no debug information is available. Release mode is therefore
suitable for the end user. Programs built using `-DCMAKE_BUILD_TYPE=Debug` will run slower, but also make the detection
of errors easier. `Debug` is suitable for contributors, and we recommend using it while working with our
[Tutorials](usergroup1.html).

\remark Depending on the standard C++ compiler on your system, you may need to specify the compiler via
`-DCMAKE_CXX_COMPILER=`, for example:
```bash
cmake -DCMAKE_CXX_COMPILER=/path/to/executable/g++-11 ../source
```

# Adding a new source file to your project

If you create a new `cpp` file and want to compile it, you need to add another `add_executable` and
`target_link_libraries` directive to you `CMakeLists.txt`.
For example, after adding `another_program.cpp` your `CMakeLists.txt` may look like this:

```
# ... former cmake code from above

add_executable (another_program another_program.cpp)
target_link_libraries (another_program sharg::sharg)
```

# Encountered issues

* **Using conda's gcc package:** ``/usr/lib/x86_64-linux-gnu/libstdc++.so.6: version 'CXXABI_1.3.11' not found``<br>
  Try setting `LD_LIBRARY_PATH`:
  ```bash
  export LD_LIBRARY_PATH=<conda_install_path>/envs/conda_gcc_env/lib/
  ```
  where `<conda_install_path>` must be replaced by the path yo your conda installation.<br>
  Usually this corresponds to the path printed by `conda info --base` and may look similar to `/home/user/miniconda3/`.

* **Assembler not found:** `... could not understand flag m ...`<br>
  Try adding `/usr/bin` to your `PATH`:
  ```bash
  export PATH=/usr/bin:$PATH
  ```
  and run `cmake` again.
