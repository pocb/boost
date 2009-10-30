#
# Copyright (C) Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
#
# On unix this is '/usr/share/cmake/boost'
#
if (UNIX)
  set(BOOST_CMAKE_INFRASTRUCTURE_DIR
    "/usr/share/boost/cmake"
    CACHE FILEPATH 
    "Directory to install Boost-${BOOST_VERSION} to")
endif()

#
# Provides version number to sphinx build
#
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/source/boost_cmake_version.py.in
  ${CMAKE_CURRENT_SOURCE_DIR}/docs/source/boost_cmake_version.py)

#
# Makefile for sphinx build with maintainer targets
#
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/docs/Makefile.in
  ${CMAKE_CURRENT_SOURCE_DIR}/docs/Makefile)

#
# File used by BoostConfigVersion to import targets/libs/etc 
# into users's cmake build
#
configure_file(install_me/Boost-version.cmake.in 
  ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Boost-version.cmake
  @ONLY)

if(UNIX)
  #
  # The files that go in /usr/share/boost/cmake that search for
  # Boost-<version>.cmake files (user specifies <version>)
  #
  option(BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS 
    "Install BoostConfig.cmake and BoostConfigVersion.cmake to BOOST_CMAKE_INFRASTRUCTURE_DIR" ON)

  mark_as_advanced(BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS)

  if (BOOST_INSTALL_FINDBOOST_CMAKE_DRIVERS)
    install(FILES
      install_me/BoostConfigVersion.cmake
      install_me/BoostConfig.cmake
      DESTINATION ${BOOST_CMAKE_INFRASTRUCTURE_DIR})
  endif()

  install(FILES
    ${CMAKE_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/Boost-version.cmake
    DESTINATION ${BOOST_CMAKE_INFRASTRUCTURE_DIR}
    RENAME Boost-${BOOST_VERSION}.cmake)

endif(UNIX)

