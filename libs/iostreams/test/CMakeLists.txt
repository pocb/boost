#
# Copyright Troy D. Straszheim
#
# Distributed under the Boost Software License, Version 1.0.
# See http://www.boost.org/LICENSE_1_0.txt
#
boost_additional_test_dependencies(iostreams BOOST_DEPENDS test)


# Helper macro to create tests for the iostreams library
macro(iostreams_test TESTNAME)
  boost_test_run(${TESTNAME} 
    ${ARGN}
    DEPENDS boost_unit_test_framework STATIC
    COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
endmacro(iostreams_test)

boost_test_run(array_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(auto_close_test DEPENDS boost_system boost_unit_test_framework STATIC)
iostreams_test(buffer_size_test)
boost_test_run(code_converter_test 
  code_converter_test.cpp detail/utf8_codecvt_facet.cpp DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(compose_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(component_access_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
iostreams_test(copy_test)
boost_test_run(counter_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(direct_adapter_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(example_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(file_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(file_descriptor_test
  DEPENDS boost_unit_test_framework boost_system boost_filesystem boost_iostreams STATIC
  COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
boost_test_run(filtering_stream_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
iostreams_test(finite_state_filter_test)
boost_test_run(flush_test DEPENDS boost_system boost_unit_test_framework STATIC)
boost_test_run(invert_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(line_filter_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(mapped_file_test
  DEPENDS boost_unit_test_framework boost_system boost_filesystem boost_iostreams STATIC
  COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
iostreams_test(newline_test)
boost_test_run(null_test DEPENDS boost_system boost_unit_test_framework STATIC)
boost_test_run(pipeline_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(regex_filter_test
  DEPENDS boost_unit_test_framework boost_system boost_filesystem  boost_regex STATIC
  COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
boost_test_run(restrict_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(seekable_file_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(seekable_filter_test DEPENDS boost_system boost_unit_test_framework STATIC)
boost_test_run(stdio_filter_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(symmetric_filter_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(tee_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)
boost_test_run(wide_stream_test DEPENDS boost_system boost_filesystem boost_unit_test_framework STATIC)

if (ZLIB_FOUND)
  boost_test_run(gzip_test
    DEPENDS boost_unit_test_framework boost_iostreams STATIC
    COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
  boost_test_run(zlib_test
    DEPENDS boost_unit_test_framework boost_iostreams STATIC
    COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
endif(ZLIB_FOUND)

# Find BZip2. If it's available, test it
if (BZIP2_FOUND)
  boost_test_run(bzip2_test
    DEPENDS boost_unit_test_framework boost_iostreamsSTATIC
    COMPILE_FLAGS "-DBOOST_IOSTREAMS_NO_LIB")
endif(BZIP2_FOUND)
