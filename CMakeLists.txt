project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(configuration)

# installation
set(CPACK_PACKAGE_NAME "dicomifier")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dicomifier")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "1")
set(CPACK_PACKAGE_VERSION 
	"${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "lahaxe<lahaxe@unistra.fr>")

# Get release name
execute_process(COMMAND lsb_release -cs OUTPUT_VARIABLE release
    OUTPUT_STRIP_TRAILING_WHITESPACE)

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

# depends on Boost DCMTK Qt4
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-filesystem${boost_version},
                                  libboost-regex${boost_version},
                                  libboost-system${boost_version},
                                  libdcmtk2,
                                  libqtcore4,
                                  libqtgui4")

include(CPack)
