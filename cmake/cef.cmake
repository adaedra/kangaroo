if(NOT DEFINED CEF_ROOT AND DEFINED ENV{CEF_ROOT})
    set(CEF_ROOT $ENV{CEF_ROOT})
endif()

if(NOT EXISTS ${CEF_ROOT})
    message(FATAL_ERROR "CEF Root (CEF_ROOT) not defined.")
endif()

list(APPEND CMAKE_MODULE_PATH ${CEF_ROOT}/cmake)

find_package(CEF REQUIRED)
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} cef.wrapper)

set(CEF_RESOURCE_FILES
    icudtl.dat
    cef.pak
    cef_100_percent.pak
    cef_200_percent.pak
    cef_extensions.pak
    devtools_resources.pak
)

set(CEF_BINARY_FILES
    snapshot_blob.bin
    v8_context_snapshot.bin
)

if(KG_PLATFORM_WIN)
    list(APPEND CEF_BINARY_FILES
        libcef.dll
        chrome_elf.dll
        d3dcompiler_47.dll
        libEGL.dll
        libGLESv2.dll
    )
else()
    list(APPEND CEF_BINARY_FILES
        libcef.so
        libEGL.so
        libGLESv2.so
    )
endif()

foreach(file IN LISTS CEF_RESOURCE_FILES)
    add_custom_command(
        OUTPUT ${KG_OUTDIR}/${file}
        COMMAND cmake -E copy ${CEF_ROOT}/Resources/${file} ${KG_OUTDIR}/${file}
    )
endforeach()

foreach(file IN LISTS CEF_BINARY_FILES)
    add_custom_command(
        OUTPUT ${KG_OUTDIR}/${file}
        COMMAND cmake -E copy ${CEF_ROOT}/${CMAKE_BUILD_TYPE}/${file} ${KG_OUTDIR}/${file}
    )
endforeach()
    
add_custom_target(
    cef.locales
    COMMAND cmake -E copy_directory ${CEF_ROOT}/Resources/locales ${KG_OUTDIR}/locales
    BYPRODUCTS ${KG_OUTDIR}/locales
)

list(TRANSFORM CEF_RESOURCE_FILES PREPEND ${KG_OUTDIR}/)
list(TRANSFORM CEF_BINARY_FILES PREPEND ${KG_OUTDIR}/)

add_custom_target(
    cef.resources ALL
    DEPENDS ${CEF_RESOURCE_FILES} ${CEF_BINARY_FILES} ${KG_OUTDIR}/locales
)

add_library(cef.library INTERFACE IMPORTED GLOBAL)
target_include_directories(cef.library INTERFACE ${CEF_ROOT})
target_link_directories(cef.library INTERFACE ${CEF_ROOT}/${CMAKE_BUILD_TYPE})

if(KG_PLATFORM_WIN)
    target_link_libraries(cef.library INTERFACE libcef)
else()
    target_link_libraries(cef.library INTERFACE cef)
endif()

add_library(cef.wrapper ALIAS libcef_dll_wrapper)
