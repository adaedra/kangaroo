find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})

if(UNIX)
    find_package(GTK2 2.24 REQUIRED gtk)
endif()

include (GenerateExportHeader)

find_package(CEF REQUIRED)
add_subdirectory(${CEF_LIBCEF_DLL_WRAPPER_PATH} libcef_dll_wrapper)

kg_target(
    NAME kg.webview
    TYPE LIBRARY SHARED
    SOURCES
        webview.cc ../include/kg/webview/webview.hh
    LINK kg.util cef::dll libcef_dll_wrapper
)
    
generate_export_header(kg.webview EXPORT_FILE_NAME kg_webview_export.hh)
target_include_directories(kg.webview PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_link_libraries(kg.webview ${wxWidgets_LIBRARIES})

if(UNIX)
    target_link_libraries(kg.webview ${GTK2_LIBRARIES})
    target_include_directories(kg.webview PUBLIC ${GTK2_INCLUDE_DIRS})
endif()
