# - Try to find Odil
# Once done this will define
#  Odil_FOUND - System has Odil
#  Odil_INCLUDE_DIRS - The Odil include directories
#  Odil_LIBRARIES - The libraries needed to use Odil
#  Odil_DEFINITIONS - Compiler switches required for using Odil

find_path(Odil_INCLUDE_DIR "odil/DataSet.h")
find_library(Odil_LIBRARY NAMES odil)

set(Odil_LIBRARIES ${Odil_LIBRARY})
set(Odil_INCLUDE_DIRS ${Odil_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set Odil_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    Odil DEFAULT_MSG Odil_LIBRARY Odil_INCLUDE_DIR)

mark_as_advanced(Odil_INCLUDE_DIR Odil_LIBRARY)
