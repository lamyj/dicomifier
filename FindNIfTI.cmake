# - Try to find NIfTI
# Once done this will define
#  NIfTI_FOUND - System has NIfTI
#  NIfTI_INCLUDE_DIRS - The NIfTI include directories
#  NIfTI_LIBRARIES - The libraries needed to use NIfTI
#  NIfTI_DEFINITIONS - Compiler switches required for using NIfTI

find_path(NIfTI_INCLUDE_DIR "nifti1.h")
find_library(NIfTI_LIBRARY NAMES niftiio)

set(NIfTI_LIBRARIES ${NIfTI_LIBRARY} znz)
set(NIfTI_INCLUDE_DIRS ${NIfTI_INCLUDE_DIR})

include(FindPackageHandleStandardArgs)
# handle the QUIETLY and REQUIRED arguments and set NIfTI_FOUND to TRUE
# if all listed variables are TRUE
find_package_handle_standard_args(
    NIfTI DEFAULT_MSG NIfTI_LIBRARY NIfTI_INCLUDE_DIR)

mark_as_advanced(NIfTI_INCLUDE_DIR NIfTI_LIBRARY)
