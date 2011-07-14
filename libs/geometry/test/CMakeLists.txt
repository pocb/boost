# (C) Copyright 2005: Eric Niebler
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

# bring in rules for testing
#import testing ;
#import feature ;

#feature.feature iterator_debugging
#  : on off
# : composite propagated optional
#  ;

#feature.compose <iterator_debugging>off
#  : <define>_HAS_ITERATOR_DEBUGGING=0
#  ;

# project
#     : requirements
#       <library>/boost/test//boost_unit_test_framework
#       <link>static
#       <include>../../..
#       <toolset>msvc:<define>_SCL_SECURE_NO_DEPRECATE
#       # MSVC's iterator debugging causes some tests to run forever.
#       <toolset>msvc:<iterator_debugging>off
#       <toolset>intel-win:<iterator_debugging>off
#     ;

boost_additional_test_dependencies(geometry BOOST_DEPENDS test)


set(TESTS 
core
point_concept 
geometries
arithmetic
algorithms
iterators
strategies
policies
util
views
multi
domains)

foreach(TEST ${TESTS})
  boost_test_run(${TEST} DEPENDS boost_unit_test_framework)
endforeach(TEST ${TESTS})

if(WIN32)
  message("Need to turn on iterator debugging")
endif(WIN32)