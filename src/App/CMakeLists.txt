cmake_minimum_required(VERSION 3.18)

set(CURRENT_PROJECT "${CMAKE_PROJECT_NAME}App")

file(GLOB SOURCE_APP
    "*.h"
    "utility/*.h"
    "Private/*.h"
    "utility/*.cpp"
    "*cpp"
    "Private/*.cpp"
    "*.qrc"
    "Private/*.qrc"
    "apple/Assets.xcassets/*.icns"
)

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Private")

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Concurrent LinguistTools QUIET)

set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/apple/Assets.xcassets/AppIcon.icns")

set_source_files_properties(${app_icon_macos} PROPERTIES
                            MACOSX_PACKAGE_LOCATION "Resources"
)

if(${QT_VERSION_MAJOR} EQUAL 6)
    qt_add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE translations.qrc MANUAL_FINALIZATION ${SOURCE_APP} ${app_icon_macos})
else()
    add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE translations.qrc  MANUAL_FINALIZATION ${SOURCE_APP} ${app_icon_macos})
endif()

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_PROJECT_NAME}Gui")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDE_DIR})

set(TARGET_DIR "${CMAKE_SOURCE_DIR}/Deploy")
file(MAKE_DIRECTORY ${TARGET_DIR})

qt_standard_project_setup(REQUIRES 6.7)

set(TS_FILES "translations/translations_en.ts"
             "translations/translations_ru.ts"
             "translations/translations_fr.ts"
             "translations/translations_sp.ts"
             "translations/translations_it.ts"
             "translations/translations_ua.ts"
)

qt6_add_translations(
    TARGETS "${CMAKE_PROJECT_NAME}" "${CMAKE_PROJECT_NAME}Gui"
    RESOURCE_PREFIX "/"
    TS_FILES ${TS_FILES}
)

set_target_properties("${PROJECT_NAME}" PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.master.CurrencyConverter
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_ICON_FILE AppIcon.icns
    RESOURCE ${app_icon_macos}
)

