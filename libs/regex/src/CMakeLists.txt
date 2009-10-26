#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#

#
# Look for the ICU library. If found, compile support into boost_regex.
#
include(FindICU)

set(BOOST_REGEX_ICU_LIBRARIES)
option(BOOST_REGEX_WITHOUT_ICU OFF "Build regex w/o ICU even if it is available.")
if (ICU_FOUND AND ICU_I18N_FOUND AND (NOT BOOST_REGEX_WITHOUT_ICU))

  add_definitions(-DBOOST_HAS_ICU=1)
  include_directories(${ICU_INCLUDE_DIRS})
  set(BOOST_REGEX_ICU_LIBRARIES ${ICU_LIBRARIES} ${ICU_I18N_LIBRARIES})
  message(STATUS "+-- ICU support added.")
  set(NO_STATIC_IF_ICU_FOUND "NO_STATIC")

else()
  message(STATUS "+-- ICU not found, omitting strictly optional feature.")
  message(STATUS "    See Boost.Regex documentation for more information.")
endif()
 
boost_add_library(boost_regex

   c_regex_traits.cpp
   cpp_regex_traits.cpp
   cregex.cpp
   fileiter.cpp
   icu.cpp
   instances.cpp
   posix_api.cpp
   regex.cpp
   regex_debug.cpp
   regex_raw_buffer.cpp
   regex_traits_defaults.cpp
   static_mutex.cpp
   w32_regex_traits.cpp
   wc_regex_traits.cpp
   wide_posix_api.cpp
   winstances.cpp 
   usinstances.cpp 

   LINK_LIBS ${BOOST_REGEX_ICU_LIBRARIES}
   SHARED_COMPILE_FLAGS -DBOOST_REGEX_DYN_LINK=1
   ${NO_STATIC_IF_ICU_FOUND}
   )




