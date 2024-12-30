##############################################################################
#   Copyright (C) 2018 GSI Helmholtzzentrum für Schwerionenforschung GmbH    #
#   Copyright (C) 2018-2025 Members of the R3B Collaboration                 #
#                                                                            #
#             This software is distributed under the terms of the            #
#                 GNU Lesser General Public Licence (GPL) version 3,         #
#                    copied verbatim in the file "LICENSE".                  #
#                                                                            #
# In applying this license GSI does not waive the privileges and immunities  #
# granted to it by virtue of its status as an Intergovernmental Organization #
# or submit itself to any jurisdiction.                                      #
##############################################################################

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
if(WITH_UCESB)
  add_subdirectory(frssource)
endif(WITH_UCESB)
add_subdirectory(frsdetectors)
add_subdirectory(sci)
add_subdirectory(online)
#add_subdirectory(macros)
add_subdirectory(wasa)
add_subdirectory(frsgen)
add_subdirectory(field)

Option(BUILD_DOXYGEN_FRS "Build Doxygen" OFF)
if(BUILD_DOXYGEN_FRS)
  find_package2(PRIVATE Doxygen COMPONENTS dot)
  if (Doxygen_FOUND)
    if (NOT Doxygen_VERSION AND DOXYGEN_VERSION)
      set(Doxygen_VERSION "${DOXYGEN_VERSION}")
    endif()
    add_subdirectory(doxygen)
  else()
    message(WARNING "BUILD_DOXYGEN_FRS requested, but Doxygen not found")
  endif()
endif(BUILD_DOXYGEN_FRS)
