# - Try to find Log4Cpp
# Once done this will define
#  Log4Cpp_FOUND - System has Log4Cpp
#  Log4Cpp_INCLUDE_DIRS - The Log4Cpp include directories
#  Log4Cpp_LIBRARIES - The libraries needed to use Log4Cpp
#  Log4Cpp_DEFINITIONS - Compiler switches required for using Log4Cpp

find_path(Log4Cpp_INCLUDE_DIR "log4cpp/config.h")
find_library(Log4Cpp_LIBRARY NAMES log4cpp)

set(Log4Cpp_LIBRARIES ${Log4Cpp_LIBRARY})
set(Log4Cpp_INCLUDE_DIRS ${Log4Cpp_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set Log4Cpp_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    Log4Cpp DEFAULT_MSG Log4Cpp_LIBRARY Log4Cpp_INCLUDE_DIR)

mark_as_advanced(Log4Cpp_INCLUDE_DIR Log4Cpp_LIBRARY)
