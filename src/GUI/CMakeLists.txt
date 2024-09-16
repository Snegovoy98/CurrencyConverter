cmake_minimum_required(VERSION 3.16)

add_definitions(-DCURRENCYCONVERTER_GUI_LIBRARY)
set(CURRENT_PROJECT "CurrencyConverterGui")

file(GLOB SOURCE_APP
    "*CurrencyConverterGui/*.cpp"
    "private/platforms/*.cpp"
    "private/models/*.cpp"

    "*CurrencyConverterGui/*.h"
    "private/*.h"
    "private/platform/*.h"
    "private/models/*.h"
)

if(${QT_VERSION_MAJOR})
    file(GLOB SOURCE_QRC
        "*.qrc"
        "CurrencyConverterGui/*.qrc"
        "private/*.qrc"
    )
endif()

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

add_library(${CURRENT_PROJECT} ${SOURCE_APP} ${SOURCE_QRC})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Quick LinguistTools Gui Qml REQUIRED)

target_link_libraries(${CURRENT_PROJECT} PUBLIC ${PROJECT_NAME}Core
                                                Qt${QT_VERSION_MAJOR}::Quick
                                                Qt${QT_VERSION_MAJOR}::Gui
                                                Qt${QT_VERSION_MAJOR}::Qml
                                                )

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCLUDE_DIR})
