cmake_minimum_required(VERSION 3.16)

get_filename_component(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_definitions(-DCURRENCYCONEVERTER_CORE_LIBRARY)
set(CURRENT_PROJECT "${PROJECT_NAME}${CURRENT_PROJECT_DIR}")


file(GLOB SOURCE_APP
    "public/*.h"
    "public/CurrencyConverter/*.h"
    "private/*.h"

    "public/*.cpp"
    "public/CurrencyConverter/*.cpp"
    "private/*.cpp"
)


if(${QT_VERSION_MAJOR})
    file(GLOB SOURCE_QRC
        "*.qrc"
    )
endif()

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/public")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

add_library(${CURRENT_PROJECT} ${SOURCE_APP} ${SOURCE_QRC})

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCLUDE_DIR})
