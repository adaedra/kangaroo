find_package(wxWidgets REQUIRED COMPONENTS base core aui)
include("${wxWidgets_USE_FILE}")

add_executable(kg.browser WIN32
    app.cc         ../include/kg/browser/app.hh
    main_window.cc ../include/kg/browser/main_window.hh
    main.cc
)
set_target_properties(kg.browser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${KG_OUTDIR}
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)

target_link_libraries(kg.browser ${wxWidgets_LIBRARIES} kg.webview)
target_include_directories(kg.browser PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/../kg.webview")
target_link_directories(kg.browser PRIVATE $ENV{CEF_ROOT}/${CMAKE_BUILD_TYPE})
