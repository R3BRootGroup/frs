# Create a library called "libR3BFRSDATA" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

Set(SYSTEM_INCLUDE_DIRECTORIES
${SYSTEM_INCLUDE_DIRECTORIES}
${BASE_INCLUDE_DIRECTORIES}
)

set(INCLUDE_DIRECTORIES
${R3BROOT_SOURCE_DIR}/r3bdata
${R3BROOT_SOURCE_DIR}/r3bbase
${R3BROOT_SOURCE_DIR}/frs/frsdata
#${R3BROOT_SOURCE_DIR}/frs/frssource
${R3BROOT_SOURCE_DIR}/frs/frsdetectors
)

include_directories( ${INCLUDE_DIRECTORIES})
include_directories(SYSTEM ${SYSTEM_INCLUDE_DIRECTORIES})

set(LINK_DIRECTORIES
${ROOT_LIBRARY_DIR}
${FAIRROOT_LIBRARY_DIR}
)

link_directories( ${LINK_DIRECTORIES})

set(SRCS
R3BFrsContFact.cxx
#R3BSeetramCalPar.cxx
R3BMusicMapped2CalPar.cxx
R3BMusicMapped2Cal.cxx
R3BMusicCalPar.cxx
R3BMusicHitPar.cxx
R3BMusicCal2HitPar.cxx
R3BMusicCal2Hit.cxx
R3BTpcCalPar.cxx
R3BTpcMapped2CalPar.cxx
R3BTpcMapped2Cal.cxx
R3BTpcCal2Hit.cxx
R3BFrsHit2AnaS4.cxx
R3BFrsHit2AnaS4Par.cxx
R3BFrsAnaPar.cxx
R3BFrsOnlineSpectra.cxx
)

# fill list of header files from list of source files
# by exchanging the file extension
CHANGE_FILE_EXTENSION(*.cxx *.h HEADERS "${SRCS}")

set(LINKDEF  R3BFRSLinkDef.h)
set(LIBRARY_NAME R3BFRS)
set(DEPENDENCIES
    Spectrum Base FairTools R3BData R3Bbase)

GENERATE_LIBRARY()
