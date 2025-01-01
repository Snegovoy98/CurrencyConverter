cmake_minimum_required(VERSION 3.31)

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
    "apple/LaunchScreen.storyboard"
    "apple/Info.plist"
)

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Private")

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Concurrent Sql LinguistTools QUIET)

set(app_icon_macos "${CMAKE_CURRENT_SOURCE_DIR}/apple/Assets.xcassets/AppIcon.icns")

set_source_files_properties(${app_icon_macos} PROPERTIES
                            MACOSX_PACKAGE_LOCATION "Resources"
)

qt6_add_executable(${CMAKE_PROJECT_NAME} MACOSX_BUNDLE translations.qrc
                           "${CMAKE_CURRENT_SOURCE_DIR}/../GUI/currencyConverterUI.qrc"
                           "${CMAKE_CURRENT_SOURCE_DIR}/../GUI/icons.qrc"
                            MANUAL_FINALIZATION ${SOURCE_APP} ${app_icon_macos}
                           "${CMAKE_CURRENT_SOURCE_DIR}/translations.qrc"
                           "${CMAKE_CURRENT_SOURCE_DIR}/../Database/private/sql_scripts.qrc"
)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
                                                                        Qt${QT_VERSION_MAJOR}::Core
                                                                        Qt${QT_VERSION_MAJOR}::Sql)

target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC
                                                                        "${CMAKE_PROJECT_NAME}Gui"
                                                                        "${CMAKE_PROJECT_NAME}Database")

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE ${PRIVATE_INCLUDE_DIR})

set(TARGET_DIR "${CMAKE_SOURCE_DIR}/Deploy")
file(MAKE_DIRECTORY ${TARGET_DIR})

qt_standard_project_setup(REQUIRES 6.7)

set(TS_FILES
             "translations/translations_en.ts"
             "translations/translations_ru.ts"
             "translations/translations_fr.ts"
             "translations/translations_sp.ts"
             "translations/translations_it.ts"
             "translations/translations_ua.ts"
)

set_target_properties("${PROJECT_NAME}" PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.preobrazhenskyi.CurrencyConverter
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_ICON_FILE AppIcon.icns
    RESOURCE ${app_icon_macos}
)

IF(IOS)
    add_custom_target("${CMAKE_PROJECT_NAME}_IOS"
        DEPENDS ${GENERATED_QM_FILES}
    )

    add_custom_target("${CMAKE_PROJECT_NAME}Gui_IOS"
        DEPENDS ${GENERATED_QM_FILES}
    )

    qt6_add_translations(
         TARGETS "${CMAKE_PROJECT_NAME}_IOS" "${CMAKE_PROJECT_NAME}Gui_IOS"
         TS_FILES ${TS_FILES}
         QM_FILES_OUTPUT_VARIABLE GENERATED_QM_FILES
    )

    foreach(file ${GENERATED_QM_FILES})
        get_filename_component(filename ${file} NAME)
        set_source_files_properties(${file} PROPERTIES QT_RESOURCE_ALIAS ${filename})
    endforeach()

    qt6_add_resources(${CMAKE_PROJECT_NAME} "translations_source"
        PREFIX "/"
        FILES ${GENERATED_QM_FILES}
    )

    set_target_properties("${CMAKE_PROJECT_NAME}" PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST "${CMAKE_CURRENT_SOURCE_DIR}/apple/Info.plist"
        QT_IOS_LAUNCH_SCREEN "${CMAKE_CURRENT_SOURCE_DIR}/apple/LaunchScreen.storyboard"
    )

else()
    qt6_add_translations(
        TARGETS "${CMAKE_PROJECT_NAME}" "${CMAKE_PROJECT_NAME}Gui"
        RESOURCE_PREFIX "/"
        TS_FILES ${TS_FILES}
)
 endif()



