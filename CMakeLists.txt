project(dicomifier)
cmake_minimum_required(VERSION 2.6.0)

include(CTest)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(configuration)

# installation
set(CPACK_PACKAGE_NAME "Dicomifier")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Dicomifier")
set(CPACK_PACKAGE_VERSION "0.2.0")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "2")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_GENERATOR "DEB")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "ICUBE")

# depends on Boost DCMTK Qt4
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libboost-filesystem1.54.0,
                                  libboost-regex1.54.0,
                                  libboost-system1.54.0,
                                  libdcmtk2,
                                  libqtcore4,
                                  libqtgui4")

include(CPack)
