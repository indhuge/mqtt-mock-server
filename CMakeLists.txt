cmake_minimum_required(VERSION 3.27)
project(mqtt_moch_server)

include(FetchContent)

set(JSON_VERSION 3.11.3)
FetchContent_Declare(
        json
        GIT_REPOSITORY "https://github.com/nlohmann/json.git"
        SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/external/json"
        GIT_TAG "master"
)
FetchContent_MakeAvailable(json)

set(CMAKE_CXX_STANDARD 20)
include_directories(mqtt_moch_server "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_SOURCE_DIR}/external/json/include")
file(GLOB_RECURSE SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
add_executable(mqtt_moch_server "${SOURCE}")
#target_link_libraries(mqtt_moch_server json)
