cmake_minimum_required(VERSION 3.4)
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0091 NEW)
project(kangaroo)

set(KG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/bin)

include(cmake/features.cmake)
include(cmake/functions.cmake)
include(cmake/cef.cmake)

set(MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(${kangaroo_SOURCE_DIR}/include)

set(RUNTIME_OUTPUT_DIRECTORY ${KG_OUTDIR})
add_custom_target(outdir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${KG_OUTDIR})

add_subdirectory(util    kg.util)
add_subdirectory(webview kg.webview)
add_subdirectory(helper  kg.helper)
add_subdirectory(browser kg.browser)
add_subdirectory(sandbox kg.sandbox)
