# FRS-R3B Software [![license](https://img.shields.io/badge/License-GPLv3-blue.svg)](COPYRIGHT) [![DOI](https://zenodo.org/badge/DOI/10.5281/zenodo.14294218.svg)](https://doi.org/10.5281/zenodo.14294218)

[![static analysis](https://github.com/R3BRootGroup/frs/actions/workflows/static_analysis.yml/badge.svg)](https://github.com/R3BRootGroup/frs/actions/workflows/static_analysis.yml) [![CI-CD](https://github.com/R3BRootGroup/frs/actions/workflows/main.yml/badge.svg)](https://github.com/R3BRootGroup/frs/actions/workflows/main.yml)
--------

## The FRS-R3B Framework
The FRS-R3B directory within [R3BRoot](https://github.com/R3BRootGroup/R3BRoot) contains the software for the [FRS](https://wiki.gsi.de/FRS) (Fragment Separator) detectors that are utilized in the FRS-R3B experiments. The FRS is a pivotal instrument for investigating nuclear reactions with relativistic radioactive beams, enabling high-precision studies of exotic nuclei and nuclear structure at the limits of stability. This software is built upon the FairRoot framework, which provides the tools necessary for both Monte Carlo simulations and data analysis of experimental results. The R3B experimental program is part of the broader nuclear physics research efforts at the FAIR (Facility for Antiproton and Ion Research), a cutting-edge international research facility that utilizes heavy-ion and antiproton beams to explore fundamental questions in nuclear physics, with a particular focus on the production and behavior of rare isotopes under extreme conditions. The FRS-R3B software package is a source distribution with recurring releases for MacOS and Linux.

## License
FRS is distributed under the terms of the GNU Lesser General Public Licence version 3 ([GPLv3](https://github.com/R3BRootGroup/frs/blob/dev/LICENSE)).

## Discussion Forum
For the software-related user support you can post a new topic on our [forum](https://forum.gsi.de/index.php?t=index&cat=40&).

## Release Information
Please see [releases](https://github.com/R3BRootGroup/frs/releases)

## Download
--------

~~~bash
git clone dev https://github.com/R3BRootGroup/frs.git
cd frs
~~~

## Code Formatting
The FRS-R3B project (as part of R3BRoot) uses clang-format-16 to ensure a common code formatting. The script "apply-format.sh" can be used for this purpose: 
~~~bash
bash apply-format.sh
~~~

## Step by Step Installation

### Required Softwares

First, you will need to install FairSoft, FairRoot and R3BRoot. For more details:

1. Install [FairSoft](https://github.com/FairRootGroup/FairSoft), required version jan24p1 or later

2. Install [FairRoot](https://github.com/FairRootGroup/FairRoot), required version 18.8.1 or later

3. Install [R3BRoot](https://github.com/R3BRootGroup/R3BRoot)

### Installation of UCESB

Checkout the most recent version of ucesb from the git repository:
~~~bash
git clone http://fy.chalmers.se/~f96hajo/ucesb/ucesb.git
~~~
And also checkout the git repository with experiment unpackers:
~~~bash
git clone https://github.com/jose-luis-rs/frsexp.git
~~~
Check that
~~~bash
which root
~~~
points to your FAIRROOT installation directory!

Compile the empty ucesb unpacker *using the same version of ROOT* as you used for FAIRROOT.
~~~bash
make empty/empty
~~~
After compilation finished, make sure that the file
~~~bash
hbook/ext_data_clnt.o
~~~
exists. Set the environment variable UCESB_DIR to the 'unpacker' directory, e.g.
~~~bash
export UCESB_DIR=/u/$USER/path/to/unpacker
~~~
Put this in your .bashrc to make it permanent. R3BRoot will look for ucesb at this location.

Compile then your experiment specific unpacker (also use *the same* ROOT version here).
~~~bash
cd frsexp/name_of_experiment
make -j8
~~~

### Installation of FRS as part of R3BRoot

~~~bash
export SIMPATH=%PATH_TO_FAIRSOFT%
export FAIRROOTPATH=%PATH_TO_FAIRROOT%
git clone dev https://github.com/R3BRootGroup/R3BRoot.git
cd R3BRoot
git clone dev https://github.com/R3BRootGroup/frs.git
cd ..
mkdir build
cd build
cmake ../R3BRoot/
. config.sh
make -j8
~~~

## Data Analysis
--------

Data analysis is included inside the frs directory, where you can find the next subdirectories:

### frsdata

This directory contains all the classes for the different data levels of the detectors: mapped, cal, hit and analysis.

### frssource

This directory contains all the readers needed to analize the data obained from the FRS detectors.

### frsdetectors

This directory contains all the classes for the mapping, calibration, and hit reconstructions of physical events as well as some classes for the analysis of the FRS experiments (S0 to S4). The identification from S0 to S8 is ongoing!

### macros

This contains all the macros needed for the unpacking and analysis of data.

## Generating Doxygen documentation

If the flage -DBUILD_DOXYGEN_FRS=ON is set when calling cmake, the doxygen documentation will be generated when calling make.  The generated html files can then be found in "build/doxygen/doc/html"

Doxygen documantation is also available online [here](http://R3BRootGroup.github.io/frs/html/index.html)

## Tested systems

The following systems are tested regularly.

| **OS Name** | **Arch** | **OS Version** | **Compiler**  | **CMake**       | **C++ Version** |
| ----------- | -------- | -------------- | ------------- | --------------- | --------------- |
| Almalinux   | x86\_64  | 9.3            | GCC 11.4.1    | 3.27.9 / 4.0.3  | C++17 / C++20 / C++23 |
| Almalinux   | x86\_64  | 9.4            | GCC 14.2.0    | 3.30.6          | C++17           |
| RHEL        | x86\_64  | 9.6            | GCC 14.2.0    | 3.30.6          | C++17           |
| Debian      | x86\_64  | 11             | GCC 10.2.1    | 3.27.4 / 3.30.0 | C++17           |
| Debian      | x86\_64  | 12             | GCC 12.2.0    | 3.27.4 / 3.30.0 | C++17 / C++20   |
| Debian      | x86\_64  | 13             | GCC 14.2.0    | 3.31.6 / 4.0.3  | C++17           |
| Ubuntu      | x86\_64  | 24.04          | GCC 13.3.0    | 3.28.3 / 4.0.3  | C++17 / C++20   |
| Ubuntu      | x86\_64  | 25.04          | GCC 14.2.0    | 3.31.6          | C++17           |
| MacOS       | arm64    | 15.3           | AppleClang 15 |  4.0.3          | C++17           |

## More Information

* [Static analyzer using Clang-tidy](https://github.com/R3BRootGroup/R3BRoot/blob/dev/config/clang_tidy/README.md)
* [CMake build system for R3BRoot/frs](https://github.com/R3BRootGroup/R3BRoot/tree/dev/doc/cmake_usage.md)
* [How to use an unmerged pull request](https://github.com/R3BRootGroup/R3BRoot/tree/dev/doc/git_usage.md#fetch-the-update-from-an-unmerged-pull-request-pr)

