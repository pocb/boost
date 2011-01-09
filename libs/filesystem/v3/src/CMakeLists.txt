#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
boost_add_library(
  filesystem3
  codecvt_error_category.cpp path.cpp portability.cpp utf8_codecvt_facet.cpp windows_file_codecvt.hpp
  operations.cpp path_traits.cpp unique_path.cpp windows_file_codecvt.cpp
  SHARED_COMPILE_FLAGS "-DBOOST_FILESYSTEM_DYN_LINK=1"
  STATIC_COMPILE_FLAGS "-DBOOST_FILESYSTEM_STATIC_LINK=1"
  DEPENDS boost_system
  )

