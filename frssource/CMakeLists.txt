# Create a library called "libR3BFRSSource" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(SRCS
    #R3BFrsReader.cxx
    VftxSciReader.cxx
    R3BFrsReaderNov19.cxx
    FrsMusicReader.cxx
    FrsTpcReader.cxx
    R3BWasaReader.cxx)

set(STRUCT_HEADERS
    ext_h101_frs.h
    ext_h101_tpc.h
    ext_h101_frssci.h
    ext_h101_frsmusic.h
    ext_h101_wasa.h)

# fill list of header files from list of source files
# by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")
set(HEADERS ${STRUCT_HEADERS} ${HEADERS})

add_library_with_dictionary(
    LIBNAME
    R3BFRSSource
    LINKDEF
    SourceLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
    R3BFRS
    R3BSource)
