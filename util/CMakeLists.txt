add_library(kg.util STATIC
    log.cc ../include/kg/util/log.hh
)
set_target_properties(kg.util PROPERTIES
    MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
