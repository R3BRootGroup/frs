# Create a library called "libR3BFRSData" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BFRS_SOURCE_DIR}/frsdata
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BSeetramCalData.cxx
R3BFrsMappedData.cxx
FRSMusicMappedData.cxx
FRSMusicCalData.cxx
FRSMusicHitData.cxx
R3BTpcMappedData.cxx
R3BTpcCalData.cxx
R3BTpcHitData.cxx
R3BFrsS4Data.cxx
R3BMwMappedData.cxx
R3BMwHitData.cxx
R3BMdcMappedData.cxx
WASATofPoint.cxx
WASAMdcPoint.cxx
FrsSpillMappedData.cxx
VftxSciMappedData.cxx
FrsSciTcalData.cxx
FrsSciSingleTcalData.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF  FRSDataLinkDef.h)
set(LIBRARY_NAME R3BFRSData)
set(DEPENDENCIES
    Base FairTools R3BData)

GENERATE_LIBRARY()
