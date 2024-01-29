cmake_minimum_required(VERSION 3.22)
project(ready)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread -fPIE -pie -g")
# message(STATUS "CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

find_package(fmt)

add_executable(ready tt.cpp)

add_custom_target(run
    COMMAND ready
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
)

target_compile_options(ready PUBLIC "-mavx2")

target_link_libraries(ready fmt::fmt)
