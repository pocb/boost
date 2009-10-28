# Copyright (C) Troy Straszheim
#
# Distributed under the Boost Software License, Version 1.0. 
# See accompanying file LICENSE_1_0.txt or copy at 
#   http://www.boost.org/LICENSE_1_0.txt 
#
set(ZLIB_FIND_QUIETLY TRUE)

find_package(ZLIB)

boost_external_report(ZLib INCLUDE_DIR LIBRARIES)

  
