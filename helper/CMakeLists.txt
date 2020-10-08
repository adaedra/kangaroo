kg_target(
    NAME kg.helper
    TYPE BINARY
    SOURCES
        helper.cc
    WIN_SOURCES
        ../resources/kangaroo.manifest
    LINK cef::dll libcef_dll_wrapper
)
