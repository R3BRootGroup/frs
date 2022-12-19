# Create a library called "libR3BFRSSource" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
${ucesb_INCLUDE_DIR}
)

set(INCLUDE_DIRECTORIES
#put here all directories where header files are located
${R3BROOT_SOURCE_DIR}/r3bsource/base
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BROOT_SOURCE_DIR}/r3bdata/wrData
${R3BFRS_SOURCE_DIR}/frssource
${R3BFRS_SOURCE_DIR}/frsdata
)

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
${ucesb_LIBRARY_DIR}
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})
link_directories( ${LINK_DIRECTORIES})

set(SRCS
#R3BFrsReader.cxx
VftxSciReader.cxx
R3BFrsReaderNov19.cxx
FrsMusicReader.cxx
FrsTpcReader.cxx
R3BWasaReader.cxx
)

Set(STRUCT_HEADERS
ext_h101_frs.h
ext_h101_tpc.h
ext_h101_frssci.h
ext_h101_frsmusic.h
ext_h101_wasa.h
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")
Set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

set(LINKDEF_FILE SourceLinkDef.h)
set(DEPENDENCIES
    R3BBase Base R3BFRS R3Bsource ${ucesb_LIBRARY_SHARED} FairTools)
set(LIBRARY_NAME R3BFRSSource)

GENERATE_LIBRARY()
