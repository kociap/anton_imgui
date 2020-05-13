cmake_minimum_required(VERSION 3.13)

add_library(anton_imgui)
target_sources(anton_imgui
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/public/anton/imgui.hpp"
    PRIVATE 
    "${CMAKE_CURRENT_SOURCE_DIR}/private/imgui.cpp")
target_include_directories(anton_imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/public")

add_subdirectory(dependencies/anton_core)
target_link_libraries(anton_imgui PUBLIC anton_core)