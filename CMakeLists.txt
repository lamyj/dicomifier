project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(configuration)

# Get release name
execute_process(COMMAND lsb_release -cs OUTPUT_VARIABLE release
    OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get architecture name
execute_process(COMMAND "dpkg --print-architecture" -cs OUTPUT_VARIABLE archi
    OUTPUT_STRIP_TRAILING_WHITESPACE)

# Get Architecture: (mandatory)
IF(NOT CPACK_PACKAGE_ARCHITECTURE)
    # There is no such thing as i686 architecture on debian, you should use i386 instead
    # $ dpkg --print-architecture
    FIND_PROGRAM(DPKG_CMD dpkg)
    IF(NOT DPKG_CMD)
        MESSAGE(STATUS "Can not find dpkg in your path, default to i386.")
        SET(CPACK_PACKAGE_ARCHITECTURE i386)
    ENDIF(NOT DPKG_CMD)
    EXECUTE_PROCESS(COMMAND "${DPKG_CMD}" --print-architecture
                    OUTPUT_VARIABLE CPACK_PACKAGE_ARCHITECTURE
                    OUTPUT_STRIP_TRAILING_WHITESPACE)
ENDIF(NOT CPACK_PACKAGE_ARCHITECTURE)

# installation
set(CPACK_PACKAGE_NAME "dicomifier")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dicomifier")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "4")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION 
    "${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}~${release}")

# Set package file name
set(CPACK_PACKAGE_FILE_NAME
    "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CPACK_PACKAGE_ARCHITECTURE}")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "lahaxe<lahaxe@unistra.fr>")

# Get packaged Boost version from release
if(${release} STREQUAL "precise")
    set(boost_version "1.46.1")
elseif(${release} STREQUAL "trusty")
    set(boost_version "1.54.0")
elseif(${release} STREQUAL "wheezy")
    set(boost_version "1.49.0")
else()
    message(FATAL_ERROR "Unknown release: ${release}")
endif()

# depends on Boost DCMTK Log4cpp Qt4
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-filesystem${boost_version},
                                  libboost-random${boost_version},
                                  libboost-regex${boost_version},
                                  libboost-system${boost_version},
                                  libdcmtk2,
                                  liblog4cpp5,
                                  libqtcore4,
                                  libqtgui4")

include(CPack)
