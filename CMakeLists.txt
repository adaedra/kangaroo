cmake_minimum_required(VERSION 3.4)
cmake_policy(SET CMP0091 NEW)
project(kangaroo)

if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(CMAKE_CXX_STANDARD 17)
include_directories(${kangaroo_SOURCE_DIR}/include)

set(KG_OUTDIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
add_custom_target(outdir ALL COMMAND ${CMAKE_COMMAND} -E make_directory ${KG_OUTDIR})

add_subdirectory(util    kg.util)
add_subdirectory(webview kg.webview)
add_subdirectory(helper  kg.helper)
add_subdirectory(browser kg.browser)
add_subdirectory(sandbox kg.sandbox)

set(CEF_RESOURCE_FILES
    icudtl.dat
    cef.pak
    cef_100_percent.pak
    cef_200_percent.pak
    cef_extensions.pak
    devtools_resources.pak
)

set(CEF_BINARY_FILES
    libcef.dll
    chrome_elf.dll
    d3dcompiler_47.dll
    libEGL.dll
    libGLESv2.dll
    snapshot_blob.bin
    v8_context_snapshot.bin
)

foreach(file IN LISTS CEF_RESOURCE_FILES)
    add_custom_command(
        OUTPUT ${KG_OUTDIR}/${file}
        COMMAND cmake -E copy $ENV{CEF_ROOT}/Resources/${file} ${KG_OUTDIR}/${file}
    )
endforeach()

foreach(file IN LISTS CEF_BINARY_FILES)
    add_custom_command(
        OUTPUT ${KG_OUTDIR}/${file}
        COMMAND cmake -E copy $ENV{CEF_ROOT}/${CMAKE_BUILD_TYPE}/${file} ${KG_OUTDIR}/${file}
    )
endforeach()

add_custom_command(
    OUTPUT ${KG_OUTDIR}/locales
    COMMAND cmake -E copy_directory $ENV{CEF_ROOT}/Resources/locales ${KG_OUTDIR}/locales
)

list(TRANSFORM CEF_RESOURCE_FILES PREPEND ${KG_OUTDIR}/)
list(TRANSFORM CEF_BINARY_FILES PREPEND ${KG_OUTDIR}/)

add_custom_target(
    CEF_RESOURCES ALL
    DEPENDS ${CEF_RESOURCE_FILES} ${CEF_BINARY_FILES} ${KG_OUTDIR}/locales
)
