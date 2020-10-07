cmake_minimum_required(VERSION 3.4)
cmake_policy(SET CMP0074 NEW)
cmake_policy(SET CMP0091 NEW)
project(kangaroo)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

if(NOT DEFINED CEF_ROOT AND DEFINED ENV{CEF_ROOT})
    set(CEF_ROOT $ENV{CEF_ROOT})
endif()

if(NOT EXISTS ${CEF_ROOT})
    message(FATAL_ERROR "CEF Root (CEF_ROOT) not defined.")
endif()

list(APPEND CMAKE_MODULE_PATH ${CEF_ROOT}/cmake)

set(CMAKE_CXX_STANDARD 17)

include_directories(${kangaroo_SOURCE_DIR}/include)

set(KG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
add_custom_target(outdir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${KG_OUTDIR})

add_subdirectory(util    kg.util)
add_subdirectory(webview kg.webview)
add_subdirectory(helper  kg.helper)
add_subdirectory(browser kg.browser)
add_subdirectory(sandbox kg.sandbox)

include(cmake/cef.cmake)
