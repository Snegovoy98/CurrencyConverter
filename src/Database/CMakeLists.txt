cmake_minimum_required(VERSION 3.21)

get_filename_component(CURRENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR} NAME)

add_definitions(-DCURRENCYCONVERTER_DATABASE_LIBARARY)
set(CURRENT_PROJECT "${PROJECT_NAME}${CURRENT_PROJECT_DIR}")

file(GLOB SOURCE_CPP
        "public/*.h"
        "private/*.h"

        "public/*.cpp"
        "private/*.cpp"
    )

add_library(${CURRENT_PROJECT} ${SOURCE_CPP})

find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Sql REQUIRED)

set(PUBLIC_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/public")
set(PRIVATE_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/private")

target_link_libraries(${CURRENT_PROJECT} PRIVATE
                                Qt${QT_VERSION_MAJOR}::Core
                                Qt${QT_VERSION_MAJOR}::Sql
                            )

target_include_directories(${CURRENT_PROJECT} PUBLIC ${PUBLIC_INCLUDE_DIR})
target_include_directories(${CURRENT_PROJECT} PRIVATE ${PRIVATE_INCLUDE_DIR})
