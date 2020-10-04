add_executable(kg.helper WIN32 helper.cc ../resources/kangaroo.manifest)
set_target_properties(kg.helper PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY ${KG_OUTDIR}
)
target_link_libraries(kg.helper libcef libcef_dll_wrapper)
target_include_directories(kg.helper PUBLIC $ENV{CEF_ROOT})
target_link_directories(kg.helper PUBLIC $ENV{CEF_ROOT}/${CMAKE_BUILD_TYPE})
