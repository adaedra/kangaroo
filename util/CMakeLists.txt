kg_target(
    NAME kg.util
    TYPE LIBRARY
    SOURCES
        log.cc     ../include/kg/util/log.hh
        defines.cc ../include/kg/util/defines.hh
    WIN_SOURCES
        log.win.cc
    GTK_SOURCES
        log.gtk.cc
    LINK kg.features
)
