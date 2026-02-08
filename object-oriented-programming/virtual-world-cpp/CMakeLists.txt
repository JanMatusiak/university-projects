cmake_minimum_required(VERSION 3.16)
project(virtual_world LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "src/*.cpp")

add_executable(world ${SOURCES})
target_include_directories(world PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/animals
    ${CMAKE_SOURCE_DIR}/include/plants
)


