# Copyright (C) Troy Straszheim
#
# Distributed under the Boost Software License, Version 1.0. 
# See accompanying file LICENSE_1_0.txt or copy at 
#   http://www.boost.org/LICENSE_1_0.txt 
#

message(STATUS "Looking for (optional) dependencies on the system")

macro(boost_external_report NAME)
  string(TOUPPER ${NAME} VARNAME)
  set(VARNAMES ${ARGV})
  list(REMOVE_AT VARNAMES 0)
  set(SUCCESS ${${VARNAME}_FOUND})
  if(NOT SUCCESS) 
    message(STATUS "${NAME} not found, some libraries or features will be disabled.")
    message(STATUS "See the documentation for ${NAME} or manually set these variables:")
  endif()
  foreach(variable ${VARNAMES})
    boost_report_value(${VARNAME}_${variable})
  endforeach()
endmacro()

foreach(external
    MPI
    Python
    BZip2
    ZLib
    Expat)
  message(STATUS "-- ${external}--")
  include(${CMAKE_SOURCE_DIR}/tools/build/CMake/externals/${external}.cmake)
endforeach()
