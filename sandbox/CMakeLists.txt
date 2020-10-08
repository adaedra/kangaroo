kg_target(
    NAME kg.sandbox
    TYPE BINARY
    SOURCES
        sandbox.cc
    WIN_SOURCES
        ../resources/kangaroo.manifest
    LINK std.fs kg.util cef.library cef.wrapper
)

if(UNIX)
    target_link_libraries(kg.sandbox stdc++fs)
endif()
