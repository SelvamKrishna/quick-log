cmake_minimum_required(VERSION 3.16)

project(quick-log LANGUAGES C)

add_library(quick-log INTERFACE)
add_library(qlog ALIAS quick-log)

target_include_directories(quick-log INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_compile_features(quick-log INTERFACE c_std_17)
