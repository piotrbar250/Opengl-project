cmake_minimum_required(VERSION 3.10)
project(app)

set(CMAKE_CXX_STANDARD 14)

set(ASSIMP_BUILD_ASSIMP_TOOLS OFF)
set(ASSIMP_BUILD_TESTS OFF)


add_subdirectory(vendor/glfw-3.3.9)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/imgui)
add_subdirectory(vendor/glm)
add_subdirectory(vendor/assimp)

file(GLOB_RECURSE app_sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE app_headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.h")
add_executable(app ${app_sources} ${app_headers})


target_include_directories(app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/")
target_include_directories(app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/UI")
target_include_directories(app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Shader")
target_include_directories(app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/Camera")

target_link_libraries(app glfw glad imgui glm assimp)