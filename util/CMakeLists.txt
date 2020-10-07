add_library(kg.util STATIC
    log.cc     ../include/kg/util/log.hh
    defines.cc ../include/kg/util/defines.hh
)
set_target_properties(kg.util PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    MSVC_RUNTIME_LIBRARY      "MultiThreaded$<$<CONFIG:Debug>:Debug>"
)
