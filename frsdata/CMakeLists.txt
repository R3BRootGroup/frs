# Create a library called "libR3BFRSData" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

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
    FrsSciSingleTcalData.cxx)

# fill list of header files from list of source files
# by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    R3BFRSData
    LINKDEF
    FRSDataLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
    R3BData)
