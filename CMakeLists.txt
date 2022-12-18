# The name of our project is “R3BFRS”. CMakeLists files in this project can
# refer to the R3BROOT root source directory of the project as ${R3BROOT_SOURCE_DIR},
# the FRS root source directory as ${R3BFRS_SOURCE_DIR} (for the FRS specifics) or
# as ${CMAKE_SOURCE_DIR} and to the root binary directory of the project as
# ${R3BFRS_BINARY_DIR} or ${CMAKE_BINARY_DIR}.

# Recurse into the given subdirectories. This does not actually cause
# another cmake executable to run. The same process will walk through
# the project's entire directory structure.

Set(R3BFRS_SOURCE_DIR ${R3BROOT_SOURCE_DIR}/frs/)
message(STATUS "${BBlue}FRS project was FOUND${CR} ")
message("    - ${Cyan}FRS_DIR${CR} = ${BGreen}${R3BFRS_SOURCE_DIR}${CR}")

# FRS specific
add_subdirectory(frsdata)
add_subdirectory(frsdetectors)
if(WITH_UCESB)
  add_subdirectory(frssource)
endif(WITH_UCESB)
add_subdirectory(sci)
add_subdirectory(online)
add_subdirectory(macros)
add_subdirectory(wasa)
add_subdirectory(frsgen)
add_subdirectory(field)
