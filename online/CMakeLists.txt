# Create a library called "libFRSOnline" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BROOT_SOURCE_DIR}/r3bdata/wrData
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BFRS_SOURCE_DIR}/frsdata
${R3BFRS_SOURCE_DIR}/frsdetectors
${R3BFRS_SOURCE_DIR}/online
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BFrsOnlineSpectra.cxx
FrsMWOnlineSpectra.cxx
FrsTpcOnlineSpectra.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF  FRSOnlineLinkDef.h)
set(LIBRARY_NAME FRSOnline)
set(DEPENDENCIES
    Spectrum Base FairTools R3BData R3Bbase)

GENERATE_LIBRARY()
