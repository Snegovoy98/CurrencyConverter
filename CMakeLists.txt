cmake_minimum_required(VERSION 3.18)

project(CurrencyConverter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CurrencyConvertor_APP ON)
set(CurrencyConvertor_Test OFF)

if(IOS)
    option(BUILD_SHARED_LIBS "Build shared libs" OFF)
else()
    option(BUILD_SHARED_LIBS "Build shared libs" ON)
endif()

if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test QUIET)
endif()

find_package(QT${QT_VERSION_MAJOR} COMPONENTS Core Test QUIET)

if(IOS OR WIN32)
    option(CurrencyConvertor_Test "This option enabled or disabled app test" OFF)
else()
    option(CurrencyConvertor_Test "This option enabled or disabled app test" ON)
endif()

add_subdirectory(src/Core)

if(CurrencyConvertor_APP)
    add_subdirectory(src/GUI)
    add_subdirectory(src/App)
else()
    message("The ${PROJECT_NAME} app is disabled")
endif()

if(CurrencyConvertor_Test)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled")
endif()

message("${MACOSX_BUNDLE} 1")

set_target_properties("${PROJECT_NAME}" PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.master.CurrencyConverter
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
)

include(GNUInstallDirs)
install(TARGETS
    "${PROJECT_NAME}"
    "${PROJECT_NAME}Core"
    "${PROJECT_NAME}Gui"
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
