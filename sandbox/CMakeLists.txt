kg_target(
    NAME kg.sandbox
    TYPE BINARY
    SOURCES
        sandbox.cc
    WIN_SOURCES
        ../resources/kangaroo.manifest
    LINK kg.util cef::dll libcef_dll_wrapper
)

if(UNIX)
    target_link_libraries(kg.sandbox stdc++fs)
endif()
