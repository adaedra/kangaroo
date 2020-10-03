find_package(wxWidgets REQUIRED COMPONENTS base core aui)
include("${wxWidgets_USE_FILE}")

add_executable(kg.browser WIN32
    app.cc
    main.cc
    main_window.cc
)
set_target_properties(kg.browser PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${KG_OUTDIR}
)

target_link_libraries(kg.browser ${wxWidgets_LIBRARIES} kg.webview)
target_include_directories(kg.browser PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/../kg.webview")
target_link_directories(kg.browser PRIVATE $ENV{CEF_ROOT}/${CMAKE_BUILD_TYPE})
