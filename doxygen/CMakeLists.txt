##############################################################################
#   Copyright (C) 2024 GSI Helmholtzzentrum für Schwerionenforschung GmbH    #
#   Copyright (C) 2024-2025 Members of the R3B Collaboration                 #
#                                                                            #
#             This software is distributed under the terms of the            #
#                 GNU Lesser General Public Licence (GPL) version 3,         #
#                    copied verbatim in the file "LICENSE".                  #
#                                                                            #
# In applying this license GSI does not waive the privileges and immunities  #
# granted to it by virtue of its status as an Intergovernmental Organization #
# or submit itself to any jurisdiction.                                      #
##############################################################################
#
# Build the documentation
#
# INCLUDE (Documentation)

  FIND_PACKAGE2(PUBLIC UnixCommands)
  FIND_PACKAGE2(PUBLIC Gnuplot)
  FIND_PACKAGE2(PUBLIC HTMLHelp)
  FIND_PACKAGE2(PUBLIC Perl)
  FIND_PACKAGE2(PUBLIC Wget)

  SET(DOXYGEN_PROJECT_NAME frs)

  SET(DOXYGEN_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
  SET(DOXYGEN_PROJECT_SOURCE_DIR "${CMAKE_SOURCE_DIR}")
  SET(DOXYGEN_BINARY_LOCATIONS_DIR "${CMAKE_SOURCE_DIR}")
  SET(DOXYGEN_BINARY_LOCATIONS
       "")
  SET(DOXYGEN_IGNORE_PREFIX "svn")

  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/doxyfile.in
    ${CMAKE_CURRENT_BINARY_DIR}/doxyfile @ONLY IMMEDIATE)

  CONFIGURE_FILE(
    ${CMAKE_CURRENT_SOURCE_DIR}/doc_makeall.sh.in
    ${CMAKE_CURRENT_BINARY_DIR}/doc_makeall.sh @ONLY IMMEDIATE)

  ADD_CUSTOM_TARGET(DoxygenDoc ALL
    COMMAND ${BASH} ${CMAKE_CURRENT_BINARY_DIR}/doc_makeall.sh)

  message(STATUS "Current binary directory: ${CMAKE_CURRENT_BINARY_DIR}")
  
  set(CMAKE_INSTALL_DOCDIR ${CMAKE_CURRENT_BINARY_DIR})
  
  message(STATUS "DESTINATION: ${CMAKE_INSTALL_DOCDIR}")

  install(FILES "${CMAKE_CURRENT_BINARY_DIR}/doc/html"
          DESTINATION "${CMAKE_INSTALL_DOCDIR}"
          COMPONENT Doxygen)
