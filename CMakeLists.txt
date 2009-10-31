##########################################################################
# CMake Build Rules for Boost                                            #
##########################################################################
# Copyright (C) 2007, 2008 Douglas Gregor <doug.gregor@gmail.com>        #
# Copyright (C) 2007, 2009 Troy Straszheim <troy@resophonic.com>         #
#                                                                        #
# Distributed under the Boost Software License, Version 1.0.             #
# See accompanying file LICENSE_1_0.txt or copy at                       #
#   http://www.boost.org/LICENSE_1_0.txt                                 #
##########################################################################
# Basic Usage:                                                           #
#                                                                        #
#   On Unix variants:                                                    #
#     ccmake BOOST_DIRECTORY                                             #
#                                                                        #
#     (c)onfigure options to your liking, then (g)enerate                #
#     makefiles. Use "make" to build, "make test" to test, "make         #
#     install" to install, and "make package" to build binary            #
#     packages.                                                          #
#                                                                        #
#   On Windows:                                                          #
#     run the CMake GUI, load the Boost directory, and generate          #
#     project files or makefiles for your environment.                   #
#                                                                        #
# For more information about CMake, see http://www.cmake.org             #
##########################################################################
cmake_minimum_required(VERSION 2.6.4 FATAL_ERROR)
project(Boost)

##########################################################################
# Version information                                                    #
##########################################################################

# We parse the version information from the boost/version.hpp header.
file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/boost/version.hpp BOOST_VERSIONSTR
  REGEX "#define[ ]+BOOST_VERSION[ ]+[0-9]+")
string(REGEX MATCH "[0-9]+" BOOST_VERSIONSTR ${BOOST_VERSIONSTR})
if (BOOST_VERSIONSTR)
  math(EXPR BOOST_VERSION_MAJOR "${BOOST_VERSIONSTR} / 100000")
  math(EXPR BOOST_VERSION_MINOR "${BOOST_VERSIONSTR} / 100 % 1000")
  math(EXPR BOOST_VERSION_SUBMINOR "${BOOST_VERSIONSTR} % 100")
  set(BOOST_VERSION "${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_SUBMINOR}")
else()
  message(FATAL_ERROR 
    "Unable to parse Boost version from ${CMAKE_CURRENT_SOURCE_DIR}/boost/version.hpp")
endif()

set(BOOST_CMAKE_VERSION "${BOOST_VERSION}.cmakebeta4")

#
#  For intermittent deployment of docs
#
set(BOOST_CMAKE_HOST sodium.resophonic.com)
set(BOOST_CMAKE_DOCROOT /var/www/htdocs/boost-cmake/)
set(BOOST_CMAKE_VERSIONED_DOCROOT ${BOOST_CMAKE_DOCROOT}/${BOOST_CMAKE_VERSION})
set(BOOST_CMAKE_URL ${BOOST_CMAKE_HOST}:${BOOST_CMAKE_VERSIONED_DOCROOT})

#
# BOOST_MAINTAINER: undocced variable that sets up maintainer mode
#
if(BOOST_MAINTAINER)  
  #
  #  Put the boost.cmake version someplace sphinx can get it
  #  for use in generated documentation
  #
  set(CMAKE_DOCS_DIR ${CMAKE_SOURCE_DIR}/tools/build/CMake/docs/)
  add_custom_target(do-release
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMAND git archive --format=tar --prefix=boost-${BOOST_CMAKE_VERSION}/ ${BOOST_CMAKE_VERSION} | gzip --best > boost-${BOOST_CMAKE_VERSION}.tar.gz
    COMMAND git archive --format=zip -9 --prefix=boost-${BOOST_CMAKE_VERSION}/ ${BOOST_CMAKE_VERSION} > boost-${BOOST_CMAKE_VERSION}.zip
    COMMAND git log --quiet ${BOOST_CMAKE_VERSION} > /dev/null
    COMMAND ssh ${BOOST_CMAKE_HOST} mkdir -p ${BOOST_CMAKE_DOCROOT}
    COMMAND scp boost-${BOOST_CMAKE_VERSION}.tar.gz boost-${BOOST_CMAKE_VERSION}.zip ${BOOST_CMAKE_URL}
    COMMAND make -C ${CMAKE_DOCS_DIR} deploy
    )
    
  message(STATUS "*** MAINTAINER TARGETS ADDED ***")

endif()

#
# Make sure that we reconfigure when boost/version.hpp changes.
#
configure_file(boost/version.hpp
   ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/version.stamp)
##########################################################################

# Put the libaries and binaries that get built into directories at the
# top of the build tree rather than in hard-to-find leaf
# directories. This simplifies manual testing and the use of the build
# tree rather than installed Boost libraries.
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
# we have to do this to export targets from the build tree
file(MAKE_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

##########################################################################
# Boost CMake modules                                                    #
##########################################################################
list(APPEND CMAKE_MODULE_PATH ${Boost_SOURCE_DIR}/tools/build/CMake)
include(BoostUtils)

message(STATUS "")
boost_report_pretty("Boost.CMake version" BOOST_CMAKE_VERSION)

include(BoostConfig)
include(BoostExternals)
include(BoostCore)
include(BoostDocs)
include(BoostTesting)
##########################################################################

##########################################################################
# Build Features and Variants                                            #
##########################################################################

# Determine default settings for the variable ENABLE_feature options
if (MSVC)
  set(ENABLE_SINGLE_THREADED_DEFAULT OFF)
else ()
  set(ENABLE_SINGLE_THREADED_DEFAULT OFF)
endif ()

# User-level options deciding which variants we will build. 
option(ENABLE_STATIC "Whether to build static libraries" ON)
option(ENABLE_SHARED "Whether to build shared libraries" ON)
option(ENABLE_DEBUG "Whether to build debugging libraries" ON)
option(ENABLE_RELEASE "Whether to build release libraries" ON)
option(ENABLE_SINGLE_THREADED "Whether to build single-threaded libraries" 
       ${ENABLE_SINGLE_THREADED_DEFAULT})
option(ENABLE_MULTI_THREADED "Whether to build multi-threaded libraries" ON)

option(WINMANGLE_LIBNAMES
  "Mangle toolset and boost version tags to into library names" 
  ${WIN32})

option(BUILD_SOVERSIONED "Create libraries with SONAMES" ${UNIX})

option(INSTALL_VERSIONED "Install to versioned directories" OFF)

# For now, we only actually support static/dynamic run-time variants for 
# Visual C++. Provide both options for Visual C++ users, but just fix
# the values of the variables for all other platforms.
option(ENABLE_STATIC_RUNTIME 
  "Whether to build libraries linking against the static runtime" 
  ${MSVC})

option(ENABLE_DYNAMIC_RUNTIME 
  "Whether to build libraries linking against the dynamic runtime" 
  ${MSVC})

# The default set of library variants that we will be building
boost_add_default_variant(RELEASE DEBUG)
boost_add_default_variant(STATIC SHARED)
boost_add_default_variant(SINGLE_THREADED MULTI_THREADED)
if (MSVC)
  boost_add_default_variant(DYNAMIC_RUNTIME STATIC_RUNTIME)
endif()

# Extra features used by some libraries
set(ENABLE_PYTHON_NODEBUG ON)
boost_add_extra_variant(PYTHON_NODEBUG PYTHON_DEBUG)
##########################################################################

##########################################################################
# Installation                                                           #
##########################################################################
if(INSTALL_VERSIONED)

  if (WIN32)
    set(sep "_")
  else()
    set(sep ".")
  endif()

  set(verstring "${BOOST_VERSION_MAJOR}${sep}${BOOST_VERSION_MINOR}${sep}${BOOST_VERSION_SUBMINOR}")
  set(BOOST_INCLUDE_INSTALL_DIR 
    "include/boost-${verstring}"
    CACHE STRING "Destination path under CMAKE_INSTALL_PREFIX for header files")

  set(BOOST_LIB_INSTALL_DIR
    "lib${LIB_SUFFIX}/boost-${verstring}"
    CACHE STRING "Destination path under CMAKE_INSTALL_PREFIX for libraries")

  set(BOOST_EXE_INSTALL_DIR
    "bin/boost-${verstring}"
    CACHE STRING "Destination path under CMAKE_INSTALL_PREFIX for executables")

else()

  set(BOOST_INCLUDE_INSTALL_DIR 
    "include/"
    CACHE STRING "Destination path under CMAKE_INSTALL_PREFIX for header files")

  set(BOOST_LIB_INSTALL_DIR
    "lib${LIB_SUFFIX}"
    CACHE STRING "Destination path under CMAKE_INSTALL_PREFIX for libraries")
    
  set(BOOST_EXE_INSTALL_DIR
    "bin"
    CACHE STRING "Destination path under CMAKE_INSTALL_PREFIX for executables")

endif()

boost_report_pretty("Install include dir:" BOOST_INCLUDE_INSTALL_DIR)
boost_report_pretty("Install lib dir:" BOOST_LIB_INSTALL_DIR)
boost_report_pretty("Install executable dir:" BOOST_EXE_INSTALL_DIR)

install(DIRECTORY boost 
  DESTINATION ${BOOST_INCLUDE_INSTALL_DIR}
  PATTERN "CVS" EXCLUDE
  PATTERN ".svn" EXCLUDE)

##########################################################################
# Binary packages                                                        #
##########################################################################
set(CPACK_PACKAGE_NAME "Boost C++ Libraries")
set(CPACK_PACKAGE_VENDOR "Boost.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Boost ${BOOST_VERSION} prerelease")

if (EXISTS "${CMAKE_SOURCE_DIR}/README.txt")
  message(STATUS "Using generic cpack package description file.")
  set(CPACK_PACKAGE_DESCRIPTION_FILE "${CMAKE_SOURCE_DIR}/README.txt")
  set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.txt")
endif ()

set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE_1_0.txt")
if (EXISTS "${CMAKE_SOURCE_DIR}/Welcome.txt")
  message(STATUS "Using generic cpack welcome file.")
  set(CPACK_RESOURCE_FILE_WELCOME "${CMAKE_SOURCE_DIR}/Welcome.txt")
endif()

set(CPACK_PACKAGE_VERSION "${BOOST_VERSION}")
set(CPACK_PACKAGE_VERSION_MAJOR "${BOOST_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${BOOST_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${BOOST_VERSION_SUBMINOR}")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "Boost")

if(WIN32 AND NOT UNIX)
  # There is a bug in NSI that does not handle full unix paths properly. Make
  # sure there is at least one set of four (4) backlasshes.
  # NOTE: No Boost icon yet
  set(CPACK_MONOLITHIC_INSTALL ON) # don't be modular for now
  set(CPACK_PACKAGE_ICON "${CMAKE_SOURCE_DIR}/tools/build/CMake\\\\Boost.bmp")
#  set(CPACK_NSIS_INSTALLED_ICON_NAME "bin\\\\MyExecutable.exe")
  set(CPACK_NSIS_DISPLAY_NAME "Boost ${BOOST_VERSION_MAJOR}.${BOOST_VERSION_MINOR}.${BOOST_VERSION_SUBMINOR} prerelease")
  set(CPACK_NSIS_HELP_LINK "http:\\\\\\\\www.boost.org")
  set(CPACK_NSIS_URL_INFO_ABOUT "http:\\\\\\\\www.boost.org")
  set(CPACK_NSIS_CONTACT "boost-users@lists.boost.org")
  set(CPACK_NSIS_MODIFY_PATH ON)
  
  # Encode the compiler name in the package 
  if (MSVC60)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc6")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_DISPLAY_NAME} for Microsoft Visual C++ 6")
  elseif (MSVC70)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc7")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_DISPLAY_NAME} for Microsoft Visual Studio 2002")
  elseif (MSVC71)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc71")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_DISPLAY_NAME} for Microsoft Visual Studio 2003")
  elseif (MSVC80)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc8")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_DISPLAY_NAME} for Microsoft Visual Studio 2005")    
  elseif (MSVC90)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-vc9")
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_DISPLAY_NAME} for Microsoft Visual Studio 2008")
  elseif (BORLAND)
    set(CPACK_PACKAGE_FILE_NAME "Boost-${BOOST_VERSION}-borland")  
    set(CPACK_NSIS_DISPLAY_NAME "${CPACK_NSIS_DISPLAY_NAME} for Borland C++ Builder")    
  endif (MSVC60)
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CPACK_NSIS_DISPLAY_NAME}")
endif(WIN32 AND NOT UNIX)
include(CPack)

if (FALSE)
  option(BOOST_INSTALLER_ON_THE_FLY
    "Whether to build installers that download components on-the-fly" OFF)
 
  if (BOOST_INSTALLER_ON_THE_FLY)
    if(COMMAND cpack_configure_downloads)
      cpack_configure_downloads(
	"http://www.osl.iu.edu/~dgregor/Boost-CMake/${BOOST_VERSION}/"
	ALL ADD_REMOVE)
    endif()
  endif()
endif()
##########################################################################

##########################################################################
# Building Boost libraries                                               #
##########################################################################
# Always include the directory where Boost's include files will be.
if (TEST_INSTALLED_TREE)
  # Use the headers from the installation directory
  include_directories("${CMAKE_INSTALL_PREFIX}/${BOOST_HEADER_DIR}")
elseif (BOOST_CMAKE_SELFTEST)
  # Use selftest headers
  include_directories("${BOOST_CMAKE_SELFTEST_ROOT}/include")
  # and regular boost headers
  include_directories(${CMAKE_SOURCE_DIR})

else()
  # Use the headers directly from the Boost source tree (in boost/)
  include_directories(${CMAKE_SOURCE_DIR})
endif (TEST_INSTALLED_TREE)

# Boost.Build version 2 does this due to trouble with autolinking
# during building and testing.  
# TODO: See if we can actually use auto-linking in our regression tests.
add_definitions(-DBOOST_ALL_NO_LIB=1)

set(BOOST_EXPORTS_FILE ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/cmake/Boost.cmake
  CACHE FILEPATH "File to export targets from boost build directory")

file(REMOVE ${BOOST_EXPORTS_FILE})

if(INSTALL_VERSIONED)
  set(BOOST_INSTALL_EXPORTS_FILE ${BOOST_LIB_INSTALL_DIR}/cmake
    CACHE STRING "Install location for cmake exports")
else()
  set(BOOST_INSTALL_EXPORTS_FILE ${BOOST_LIB_INSTALL_DIR}/boost/cmake
    CACHE STRING "Install location for cmake exports")
endif()

mark_as_advanced(BOOST_EXPORTS_FILE BOOST_INSTALL_EXPORTS_FILE)

# Add build rules for documentation
add_subdirectory(doc)

# Add build rules for all of the Boost libraries
add_subdirectory(libs)

# Add build rules for all of the Boost tools
# TODO: On hold while I work on the modularity code
add_subdirectory(tools)
##########################################################################

install(EXPORT Boost DESTINATION ${BOOST_INSTALL_EXPORTS_FILE})

add_subdirectory(tools/build/CMake)

