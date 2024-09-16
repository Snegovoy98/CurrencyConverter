cmake_minimum_required(VERSION 3.16)

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
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Test QUIET)
endif()

find_package(QT${QT_VERSION_MAJOR} COMPONENTS Core Test QUIET)

if(IOS OR WIN32)
    option(CurrencyConvertor_Test "This option enabled or disabled app test" OFF)
else()
    option(CurrencyConvertor_Test "This option enabled or disabled app test" ON)
endif()

if(CurrencyConvertor_APP)
    add_subdirectory(src/Core)
    add_subdirectory(src/App)
    add_subdirectory(src/GUI)
else()
    message("The ${PROJECT_NAME} app is disabled")
endif()

if(CurrencyConvertor_Test)
    add_subdirectory(tests)
else()
    message("The ${PROJECT_NAME} tests is disabled")
endif()

include(GNUInstallDirs)
install(TARGETS CurrencyConverter
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
