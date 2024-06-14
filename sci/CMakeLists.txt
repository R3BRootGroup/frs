# Create a library called "libFrsTCal" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(SRCS
    FrsSciTcalPar.cxx
    FrsTcalContFact.cxx
    FrsSciMapped2TcalPar.cxx
    FrsSciMapped2Tcal.cxx
    FrsSciRawPosPar.cxx
    FrsSciRawTofPar.cxx
    FrsSciTcal2RawPosPar.cxx
    FrsSciTcal2RawTofPar.cxx
    FrsSciTcal2SingleTcal.cxx)

# fill list of header files from list of source files
# by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    FrsTcal
    LINKDEF
    FrsTcalLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
    R3BFRSData)

if(FAIRDB_FOUND)
    target_link_libraries(FrsTcal PRIVATE FairDB)
endif(FAIRDB_FOUND)
