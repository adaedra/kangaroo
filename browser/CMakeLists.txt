find_package(wxWidgets REQUIRED COMPONENTS base core)
include("${wxWidgets_USE_FILE}")

kg_target(
    NAME kg.browser
    TYPE BINARY
    SOURCES
        app.cc         ../include/kg/browser/app.hh
        main_window.cc ../include/kg/browser/main_window.hh
    WIN_SOURCES
        app.win.cc
        main.win.cc
        ../resources/kangaroo.manifest
    GTK_SOURCES
        app.gtk.cc
        main.gtk.cc
    LINK std.fs kg.util kg.webview cef.library
)

target_link_libraries(kg.browser ${wxWidgets_LIBRARIES})
