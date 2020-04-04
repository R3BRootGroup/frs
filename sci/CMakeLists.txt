# Create a library called "libFrsTCal" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES ${SYSTEM_INCLUDE_DIRECTORIES} ${BASE_INCLUDE_DIRECTORIES} )

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BFRS_SOURCE_DIR}/frsdata
${R3BFRS_SOURCE_DIR}/sci
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES ${ROOT_LIBRARY_DIR} ${FAIRROOT_LIBRARY_DIR} )

link_directories( ${LINK_DIRECTORIES})

set(SRCS
FrsSciTcalPar.cxx
FrsTcalContFact.cxx
FrsSciMapped2TcalPar.cxx
FrsSciMapped2Tcal.cxx
FrsSciRawPosPar.cxx
FrsSciRawTofPar.cxx
FrsSciTcal2RawPosPar.cxx
FrsSciTcal2RawTofPar.cxx
FrsSciTcal2SingleTcal.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

Set(LINKDEF FrsTcalLinkDef.h)
Set(LIBRARY_NAME FrsTcal)
Set(DEPENDENCIES
    Base ParBase Core m)

if(FAIRDB_FOUND)
set(DEPENDENCIES
    ${DEPENDENCIES} FairDB)
endif(FAIRDB_FOUND)

GENERATE_LIBRARY()

