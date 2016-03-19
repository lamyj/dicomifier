find_package(Boost COMPONENTS filesystem program_options system REQUIRED)
find_package(DCMTK REQUIRED)
find_package(JsonCpp REQUIRED)
find_package(NIfTI REQUIRED)
find_package(Odil REQUIRED)
find_package(Qt4 REQUIRED QtCore QtGui)

include(${QT_USE_FILE})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/../lib ${CMAKE_CURRENT_SOURCE_DIR}/../gui
    ${Boost_INCLUDE_DIRS} ${DCMTK_INCLUDE_DIRS} ${JsonCpp_INCLUDE_DIRS} 
    ${NIfTI_INCLUDE_DIRS} ${Odil_INCLUDE_DIRS} ${QT_INCLUDES})
add_definitions(
    ${DCMTK_DEFINITIONS} -DBOOST_FILESYSTEM_VERSION=3)
link_directories(
    ${Boost_LIBRARY_DIRS} ${DCMTK_LIBRARY_DIRS})

add_executable(bruker2dicom "bruker2dicom.cpp")
target_link_libraries(
    bruker2dicom libdicomifier ${Boost_LIBRARIES} ${Odil_LIBRARIES})

add_executable(dicom2nifti "dicom2nifti.cpp")
target_link_libraries(dicom2nifti libdicomifier ${Boost_LIBRARIES})

add_executable(dicomifier MACOSX_BUNDLE "dicomifier.cpp")
target_link_libraries(
    dicomifier
    libdicomifier libdicomifiergui ${Boost_LIBRARIES} ${QT_LIBRARIES})

SET(APPS "\${CMAKE_INSTALL_PREFIX}/bin/dicomifier")
SET(qtconf_dest_dir bin)
if(APPLE)
    set(APPS "\${CMAKE_INSTALL_PREFIX}/dicomifier.app")
    set(qtconf_dest_dir dicomifier.app/Contents/Resources)
endif()

# We need an empty qt.conf in order to override the hard-coded paths that are 
# compiled into the Qt library. 
install(CODE "
    file(WRITE \"\${CMAKE_INSTALL_PREFIX}/${qtconf_dest_dir}/qt.conf\" \"\")
    ")

set(DIRS "/Users/julien/src/dicomifier/build/install/lib;/usr/local/opt/icu4c/lib")
set(LIBRARIES )

install(
    TARGETS bruker2dicom dicom2nifti dicomifier
    BUNDLE DESTINATION .
    RUNTIME DESTINATION bin)
if(APPLE)
    install(
        TARGETS bruker2dicom dicom2nifti 
        RUNTIME DESTINATION dicomifier.app/Contents/MacOS)
endif()

install(CODE "
    macro(gp_resolve_item_override context item exepath dirs resolved_item_var resolved_var)
        if(NOT \${resolved_var})
            # Context is sometimes wrong: look in dirs
            if(item MATCHES \"^@loader_path\")
                string(REPLACE \"@loader_path/\" \"\" noprefix_item \"\${item}\")
                set(ri \"ri-NOTFOUND\")
                find_file(ri \"\${noprefix_item}\" \${dirs} NO_DEFAULT_PATH)
                find_file(ri \"\${noprefix_item}\" \${dirs} /usr/lib)
                if(EXISTS \"\${ri}\")
                    set(\${resolved_var} 1)
                    set(\${resolved_item_var} \"\${ri}\")
                    set(ri \"ri-NOTFOUND\")
                endif()
            endif()
        endif()
    endmacro()
    set(BU_CHMOD_BUNDLE_ITEMS ON)
    include(BundleUtilities)
    fixup_bundle(\"${APPS}\" \"${LIBRARIES}\" \"${DIRS}\")
    ")
