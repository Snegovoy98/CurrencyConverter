cmake_minimum_required(VERSION 3.31)

project(CurrencyConverter VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CurrencyConvertor_APP ON)

if(IOS)
    option(BUILD_SHARED_LIBS "Build shared libs" OFF)
else()
    option(BUILD_SHARED_LIBS "Build shared libs" ON)
endif()

if(NOT DEFINED QT_VERSION_MAJOR)
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core QUIET)
endif()

find_package(QT${QT_VERSION_MAJOR} COMPONENTS Core  QUIET)

add_subdirectory(src/Database)
add_subdirectory(src/Core)

if(CurrencyConvertor_APP)
    add_subdirectory(src/GUI)
    add_subdirectory(src/App)
else()
    message("The ${PROJECT_NAME} app is disabled")
endif()

include(GNUInstallDirs)
install(TARGETS
    "${PROJECT_NAME}"
    "${PROJECT_NAME}Core"
    "${PROJECT_NAME}Database"
    "${PROJECT_NAME}Gui"
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)


