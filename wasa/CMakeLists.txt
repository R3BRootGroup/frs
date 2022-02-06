# Create a library called "libWASA" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BFRS_SOURCE_DIR}/frsdata
${R3BFRS_SOURCE_DIR}/frsdetectors
${R3BFRS_SOURCE_DIR}/wasa
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BWasaOnlineSpectra.cxx
WASATof.cxx
WASAGeoTof.cxx
WASAGeoTofPar.cxx
WASAMdc.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF  R3BWASALinkDef.h)
set(LIBRARY_NAME R3BWASA)
set(DEPENDENCIES
    Spectrum Base FairTools R3BData R3BBase R3BFRSData)

GENERATE_LIBRARY()
