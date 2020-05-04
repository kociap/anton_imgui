add_library(anton_imgui)
target_sources(anton_imgui PRIATE "${CMAKE_CURRENT_SOURCE_DIR}/private/imgui.cpp")
target_include_directories(anton_imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/public")
