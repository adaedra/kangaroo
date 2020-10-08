kg_target(
    NAME kg.helper
    TYPE BINARY
    SOURCES
        helper.cc
    WIN_SOURCES
        helper.win.cc
        ../resources/kangaroo.manifest
    GTK_SOURCES
        helper.gtk.cc
    LINK cef.library cef.wrapper
)
