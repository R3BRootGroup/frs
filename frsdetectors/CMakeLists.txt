# Create a library called "libR3BFRS" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(SRCS
    R3BFrsContFact.cxx
    R3BSeetramMapped2Cal.cxx
    R3BSeetramCalPar.cxx
    FRSMusicMapped2CalPar.cxx
    FRSMusicMapped2Cal.cxx
    FRSMusicCalPar.cxx
    FRSMusicHitPar.cxx
    FRSMusicCal2HitPar.cxx
    FRSMusicCal2Hit.cxx
    R3BTpcCalPar.cxx
    R3BTpcMapped2CalPar.cxx
    R3BTpcMapped2Cal.cxx
    R3BTpcCal2Hit.cxx
    R3BFrsHit2AnaS4.cxx
    R3BFrsHit2AnaS4Par.cxx
    R3BFrsAnaPar.cxx
    R3BMWMapped2Hit.cxx
    FrsRatesSpill.cxx)

# fill list of header files from list of source files
# by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    R3BFRS
    LINKDEF
    FRSDetLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
    R3BFRSData)
