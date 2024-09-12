cmake_minimum_required(VERSION 3.10)
project(imgui)

add_library(imgui STATIC)

file(GLOB_RECURSE IMGUI_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/imgui/*.cpp")

target_sources(imgui PRIVATE ${IMGUI_SOURCES})

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")

target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../glfw-3.3.9/include")

target_link_libraries(imgui glfw)