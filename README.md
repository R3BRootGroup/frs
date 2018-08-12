# Purpose
--------

FRS folder inside R3BRoot describes the [FRS](https://www-win.gsi.de/frs-setup/) detectors which are going to be employed for the FRS and R3B experiments.
The R3BRoot software is based on the FairRoot framework and can be used to perform Monte Carlo simulations and experimental data analysis of the R3B (Reactions with Relativistic Radioactive Beams) nuclear physics experiments at the FAIR research center (Facility for Antiproton and Ion Research).

For the software-related user support you can post a new topic on our [forum](https://forum.gsi.de/index.php?t=index&cat=40&).

# Download
--------

~~~bash
git clone https://github.com/R3BRootGroup/frs.git
cd frs
git checkout dev
~~~

# Install
--------

### Required software

First, you will need to install FairSoft and FairRoot. For more details: [instructions](https://www.r3broot.gsi.de/installation).

### Installation of UCESB

Checkout the most recent version of ucesb from the git repository:
~~~bash
git clone http://fy.chalmers.se/~f96hajo/ucesb/ucesb.git
~~~
And also checkout the git repository with experiment unpackers:
~~~bash
git clone lx-pool.gsi.de:/u/johansso/upexps
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
cd upexps/sNameExperiment
make
~~~

### Installation of R3BRoot and FRS (as part of R3BRoot)

~~~bash
export SIMPATH=%PATH_TO_FAIRSOFT%
export FAIRROOTPATH=%PATH_TO_FAIRROOT%
git clone https://github.com/R3BRootGroup/R3BRoot.git
cd R3BRoot
git checkout dev
git clone https://github.com/R3BRootGroup/macros.git
cd macros
git checkout dev
cd ..
git clone https://github.com/R3BRootGroup/frs.git
cd frs
git checkout dev
cd ..
cd ..
mkdir build
cd build
cmake ../R3BRoot/
. config.sh
make -j4
~~~

# Data Analysis
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

