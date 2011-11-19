#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
set(BOOST_CHRONO_EXTRA_SOURCES)
set(BOOST_CHRONO_LIBRARIES)

boost_add_library(chrono
  chrono.cpp
  process_clock.cpp
  process_cpu_clocks.cpp
  run_timer.cpp
  run_timer_static.cpp
  thread_clock.cpp

  SHARED_COMPILE_FLAGS "-DBOOST_CHRONO_DYN_LINK=1"
  )
