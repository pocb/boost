#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
#----------------------------------------------------------------------------
# This file was automatically generated from the original CMakeLists.txt file
# Add a variable to hold the headers for the library
set (lib_headers
    iostreams
)

# find zlib up here... used lower down in various places
include(FindZLIB)
if (ZLIB_FOUND)
  message("Zlib found, enabling extra components.")
endif()
include(FindBZip2)
if(BZIP2_FOUND)
  message("BZip2 found, enabling extra components.")
endif()

#
# Add a library target to the build system
#

boost_library_project(
  iostreams
  SRCDIRS  src
  TESTDIRS  test
  EXAMPLEDIRS  example
  HEADERS ${lib_headers}
  #  DOCDIRS 
  DESCRIPTION  "Framework for defining streams, stream buffers and i/o filters"
  MODULARIZED
  AUTHORS  "Jonathan Turkanis <turkanis -at- coderage.com>"
  #  MAINTAINERS 
)


