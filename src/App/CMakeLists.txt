cmake_minimum_required(VERSION 3.16)

set(CURRENT_PROJECT "${PROJECT_NAME}")
file(GLOB SOURCE_APP
    "*.h"
    "Private/*.h"
    "*cpp"
    "Private/*.cpp"
    "*.qrc"
    "Private/*.qrc"
)

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Private")


find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Concurrent QUIET)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_add_executable(${CURRENT_PROJECT} MANUAL_FINALIZATION ${SOURCE_APP})
else()
    add_executable(${CURRENT_PROJECT} MANUAL_FINALIZATION ${SOURCE_APP})
endif()

target_link_libraries(${CURRENT_PROJECT} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${CURRENT_PROJECT} PUBLIC "${PROJECT_NAME}Gui")

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCLUDE_DIR})

set(TARGET_DIR "${CMAKE_SOURCE_DIR}/Deploy")
file(MAKE_DIRECTORY ${TARGET_DIR})

if(IOS)
    set_target_properties(appCurrencyConverter PROPERTIES
        MACOSX_BUNDLE_GUI_IDENTIFIER com.master.appCurrencyConverter
        MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
        MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
        MACOSX_BUNDLE TRUE
        # WIN32_EXECUTABLE TRUE
    )

    set(plist_file "${CMAKE_CURRENT_SOURCE_DIR}/apple/Info.plist")
    configure_file("${plist_file}.in" ${plist_file} @ONLY)

    set(QT_IOS_EXPORT_ARCHIVE_XCODEBUILD_FLAGS "-allowProvisioningUpdates")
    addDeployIPA(${CURRENT_PROJECT}
            "${CURRENCY_CONVERTOR_ID}"
            "${TARGET_DIR}"
            "${CMAKE_CURRENT_SOURCE_DIR}/apple"
    )
else()
    set(DeployFile "${CMAKE_CURRENT_SOURCE_DIR}/Deploy/CurrencyConverter.json")
    #configure_file("${DeployFile}.in" ${DeployFile} @ONLY)
    #addDeployFromCustomFile("CurrencyConverter" ${DeployFile})
endif()

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_plugins(${CURRENT_PROJECT})
    qt_finalize_target(${CURRENT_PROJECT})
endif()
