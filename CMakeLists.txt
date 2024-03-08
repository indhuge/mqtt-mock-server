cmake_minimum_required(VERSION 3.27)
project(mqtt_moch_server)

set(CMAKE_CXX_STANDARD 20)
include_directories(mqtt_moch_server "${CMAKE_CURRENT_SOURCE_DIR}/include")
file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(mqtt_moch_server "${SOURCE}")
