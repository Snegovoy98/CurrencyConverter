cmake_minimum_required(VERSION 3.18)

add_definitions(-DCURRENCYCONVERTER_GUI_LIBRARY)
set(CURRENT_PROJECT "${PROJECT_NAME}Gui")

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
        "CurrencyConverterModules/*.qml"
        "CurrencyConverterModules/Common/*.qml"
        "CurrencyConverterModules/Components/*.qml"
    )
endif()

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

add_library(${CURRENT_PROJECT} ${SOURCE_APP} ${SOURCE_QRC})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Quick QuickControls2 LinguistTools Gui Qml REQUIRED)

target_link_libraries(${CURRENT_PROJECT}
                PUBLIC
                "${PROJECT_NAME}Core"
                Qt${QT_VERSION_MAJOR}::Quick
                Qt${QT_VERSION_MAJOR}::Gui
                Qt${QT_VERSION_MAJOR}::Qml
                Qt${QT_VERSION_MAJOR}::QuickControls2
)

set(TS_FILES "translations/translations_en.ts"
             "translations/translations_ru.ts"
             "translations/translations_fr.ts"
             "translations/translations_sp.ts"
             "translations/translations_it.ts"
             "translations/translations_ua.ts"
)

qt6_add_lupdate("${CMAKE_PROJECT_NAME}"
    SOURCE_TARGETS "${CMAKE_PROJECT_NAME}" "${CMAKE_PROJECT_NAME}Gui"
    TS_FILES ${TS_FILES}
)

qt6_add_lrelease(TS_FILES ${TS_FILES})

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCLUDE_DIR})


