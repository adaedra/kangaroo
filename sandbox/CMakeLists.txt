add_executable(kg.sandbox WIN32 sandbox.cc ../resources/kangaroo.manifest)
set_target_properties(kg.sandbox PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY ${KG_OUTDIR}
)
target_link_libraries(kg.sandbox kg.util libcef_dll_wrapper libcef)
target_include_directories(kg.sandbox PUBLIC $ENV{CEF_ROOT})
target_link_directories(kg.sandbox PUBLIC $ENV{CEF_ROOT}/${CMAKE_BUILD_TYPE})
