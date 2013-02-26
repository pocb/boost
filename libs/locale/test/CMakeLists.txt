#----------------------------------------------------------------------------
# CMake framework maintained by Denis Arnaud on git://github.com/pocb/boost
#----------------------------------------------------------------------------
#
boost_additional_test_dependencies (locale BOOST_DEPENDS test)

set (LOCALE_LIBRARIES
  boost_locale
  boost_test_exec_monitor)

set (BOOST_TEST_EXEC_MONITOR_SUFFIX "")
if (NOT BUILD_SINGLE_THREADED)
  set (BOOST_TEST_EXEC_MONITOR_SUFFIX "-mt")
endif (NOT BUILD_SINGLE_THREADED)

set (BOOST_TEST_EXEC_MONITOR_SUFFIX "${BOOST_TEST_EXEC_MONITOR_SUFFIX}-static")
if (NOT BUILD_RELEASE)
  set (BOOST_TEST_EXEC_MONITOR_SUFFIX "${BOOST_TEST_EXEC_MONITOR_SUFFIX}-debug")
endif (NOT BUILD_RELEASE)

#
macro (locale_test_run TESTNAME)
  boost_test_run (${TESTNAME} 
    STATIC
    DEPENDS boost_locale boost_test_exec_monitor )
  boost_test_run ("${TESTNAME}_dll"
    ${TESTNAME}.cpp
    SHARED
    DEPENDS boost_locale 
    "boost_test_exec_monitor${BOOST_TEST_EXEC_MONITOR_SUFFIX}")
endmacro (locale_test_run)

#
set (TESTS 
  test_config
  test_utf
  test_date_time
  test_ios_prop
  test_codepage_converter
  test_codepage
  test_message
  test_generator
  test_collate
  test_convert
  test_boundary
  test_formatting
  test_icu_vs_os_timezone
  test_winapi_collate
  test_winapi_convert
#  test_winapi_formatting
  test_posix_collate
  test_posix_convert
  test_posix_formatting
  test_std_collate
  test_std_convert
  test_std_formatting
  )

#
foreach(_test ${TESTS})
  locale_test_run(${_test}) 
endforeach(_test ${TESTS})
