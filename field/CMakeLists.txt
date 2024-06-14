# Create a library called "libFRSWASAFIELD" which includes the source files given in
# the array .
# The extension is already found.  Any number of sources could be listed here.

set(SRCS FRSWasaFieldMap.cxx)

# fill list of header files from list of source files
# by exchanging the file extension
change_file_extension(*.cxx *.h HEADERS "${SRCS}")

add_library_with_dictionary(
    LIBNAME
    FRSWASAFIELD
    LINKDEF
    FRSFieldLinkDef.h
    HEADERS
    ${HEADERS}
    SRCS
    ${SRCS}
    INCLUDEDIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    DEPENDENCIES
    Field)
