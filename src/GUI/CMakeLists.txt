cmake_minimum_required(VERSION 3.31)

add_definitions(-DCURRENCYCONVERTER_GUI_LIBRARY)
set(CURRENT_PROJECT "${PROJECT_NAME}Gui")

file(GLOB SOURCE_APP
    "CurrencyConverterGui/*.h"
    "private/models/*.h"

    "CurrencyConverterGui/*.cpp"
    "private/models/*.cpp"
)

if(${QT_VERSION_MAJOR})
    file(GLOB SOURCE_QRC
        "*.qrc"
        "CurrencyConverterGui/*.qrc"
        "private/*.qrc"
        "CurrencyConverterModules/*.qml"
        "CurrencyConverterModules/Common/*.qml"
        "CurrencyConverterModules/Components/*.qml"
        "CurrencyConverterModules/Dialogs/*.qml"
    )
endif()

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

add_library(${CURRENT_PROJECT} ${SOURCE_APP} ${SOURCE_QRC})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS  Quick QuickControls2 Gui Sql Qml REQUIRED)

target_link_libraries(${CURRENT_PROJECT}
                PUBLIC
                "${PROJECT_NAME}Core"
                "${PROJECT_NAME}Database"
                Qt${QT_VERSION_MAJOR}::Quick
                Qt${QT_VERSION_MAJOR}::Gui
                Qt${QT_VERSION_MAJOR}::Qml
                Qt${QT_VERSION_MAJOR}::QuickControls2
                 Qt${QT_VERSION_MAJOR}::Sql
)

qt6_import_qml_plugins(${CURRENT_PROJECT})

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCLUDE_DIR})


