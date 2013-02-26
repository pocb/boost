# Find iconv library
#
# Author: Eddy Xu <eddyxu at gmail.com>
# Changed: Florian Uhlig <f.uhlig at gsi.de>
#
# Released under BSD license
#
#  ICONV_INCLUDE_DIRS   - where to find iconv.h, etc
#  ICONV_LIBRARIES      - Lists of libraries when using iconv
#  ICONV_FOUND          - True if iconv found


# Look for the header file
FIND_PATH( ICONV_INCLUDE_DIR NAMES iconv.h )
MARK_AS_ADVANCED( ICONV_INCLUDE_DIR )

# If the header file exist look for the library
If(ICONV_INCLUDE_DIR)

  # Check first if the functionality is part of the glibc
  # This is the case for linux systems
  include(CheckFunctionExists)
  CHECK_FUNCTION_EXISTS(iconv_open IN_GLIBC)

  If(IN_GLIBC)
    Set(ICONV_FOUND 1)
    SET(ICONV_LIBRARIES)
    SET(ICONV_INCLUDE_DIRS ${ICONV_INCLUDE_DIR})
  Else (IN_GLIBC)
    # Look for the iconv library
    FIND_LIBRARY( ICONV_LIBRARY NAMES iconv )
    MARK_AS_ADVANCED( ICONV_LIBRARY )
    SET(ICONV_LIBRARIES ${ICONV_LIBRARY})
    SET(ICONV_INCLUDE_DIRS ${ICONV_INCLUDE_DIR})
    Set(ICONV_FOUND 1)
  EndIf (IN_GLIBC)

Else(ICONV_INCLUDE_DIR)
  SET(ICONV_FOUND 0)
  SET(ICONV_LIBRARIES)
  SET(ICONV_INCLUDE_DIRS)
EndIf(ICONV_INCLUDE_DIR)

# Report results
IF(NOT ICONV_FOUND)
  SET(ICONV_DIR_MESSAGE
    "Iconv was not found. Make sure ICONV_LIBRARY and ICONV_INCLUDE_DIR are
set.")
    IF(NOT ICONV_FIND_QUIETLY)
      MESSAGE(STATUS ${ICONV_DIR_MESSAGE})
    ELSE(NOT ICONV_FIND_QUIETLY)
      IF(ICONV_FIND_REQUIRED)
        MESSAGE(FATAL_ERROR ${ICONV_DIR_MESSAGE})
      ENDIF(ICONV_FIND_REQUIRED)
    ENDIF(NOT ICONV_FIND_QUIETLY)
ENDIF(NOT ICONV_FOUND)