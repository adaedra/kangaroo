find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})

include (GenerateExportHeader)

find_package(CEF REQUIRED)
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

if(WIN32)
    add_library(cef ALIAS libcef)
endif()

add_library(kg.webview SHARED
    webview.cc    ../include/kg/webview/webview.hh
)
set_target_properties(kg.webview PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
    RUNTIME_OUTPUT_DIRECTORY ${KG_OUTDIR}
)

generate_export_header(kg.webview EXPORT_FILE_NAME kg_webview_export.hh)
target_link_libraries(kg.webview kg.util libcef_dll_wrapper cef ${wxWidgets_LIBRARIES})
target_include_directories(kg.webview PUBLIC ${CEF_INCLUDE_PATH})
target_include_directories(kg.webview PRIVATE ${CMAKE_CURRENT_BINARY_DIR})
target_link_directories(kg.webview PRIVATE ${_CEF_ROOT}/${CMAKE_BUILD_TYPE})
