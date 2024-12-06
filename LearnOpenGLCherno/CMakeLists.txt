cmake_minimum_required(VERSION 3.29)
project(LearnOpenGLCherno)

set(CMAKE_CXX_STANDARD 26)

if (APPLE)
    set(CMAKE_CXX_FLAGS "-framework Cocoa -framework IOKit")
endif()

include_directories(Dependencies)
include_directories(Dependencies/include)

add_library(glfw STATIC IMPORTED)
set_target_properties(glfw PROPERTIES
        IMPORTED_LOCATION "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/lib-arm64/libglfw3.a"
        INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_SOURCE_DIR}/Dependencies/include")

add_executable(LearnOpenGLCherno src/Application.cpp)

target_link_libraries(LearnOpenGLCherno glfw)
