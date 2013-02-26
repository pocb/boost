#----------------------------------------------------------------------------
# CMake framework maintained by Denis Arnaud on git://github.com/pocb/boost
#----------------------------------------------------------------------------
#
boost_additional_test_dependencies (move BOOST_DEPENDS test)


file(GLOB MOVE_TESTS *.cpp)
foreach(TEST ${MOVE_TESTS})
  get_filename_component(TEST ${TEST} NAME_WE)
  boost_test_run(${TEST} DEPENDS boost_unit_test_framework STATIC)
endforeach()

if (WIN32)
  message ("Need to turn on iterator debugging")
endif (WIN32)
