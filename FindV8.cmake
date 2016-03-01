# - Try to find V8
# Once done this will define
#  V8_FOUND - System has V8
#  V8_INCLUDE_DIRS - The V8 include directories
#  V8_LIBRARIES - The libraries needed to use V8
#  V8_DEFINITIONS - Compiler switches required for using V8

find_path(V8_INCLUDE_DIR "v8.h")
find_library(V8_LIBRARY NAMES v8)

set(V8_LIBRARIES ${V8_LIBRARY})
set(V8_INCLUDE_DIRS ${V8_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set V8_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    V8 DEFAULT_MSG V8_LIBRARY V8_INCLUDE_DIR)

mark_as_advanced(V8_INCLUDE_DIR V8_LIBRARY)
