cmake_minimum_required(VERSION 3.31)

get_filename_component(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_definitions(-DCURRENCYCONEVERTER_CORE_LIBRARY)
set(CURRENT_PROJECT "${PROJECT_NAME}${CURRENT_PROJECT_DIR}")

file(GLOB SOURCE_APP
    "public/*.h"
    "public/CurrencyConverter/utility/*.h"

    "public/*.cpp"
    "public/CurrencyConverter/utility/*.cpp"
)

if(${QT_VERSION_MAJOR})
    file(GLOB SOURCE_QRC
        "*.qrc"
    )
endif()

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/public")

add_library(${CURRENT_PROJECT} ${SOURCE_APP} ${SOURCE_QRC})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network Sql Concurrent  Core REQUIRED)

target_link_libraries(${CURRENT_PROJECT} PUBLIC
                                                                "${PROJECT_NAME}Database"
                                                                PRIVATE
                                                                Qt${QT_VERSION_MAJOR}::Core
                                                                Qt${QT_VERSION_MAJOR}::Network
                                                                Qt${QT_VERSION_MAJOR}::Sql
                             )

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})


