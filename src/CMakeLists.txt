find_package(wxWidgets REQUIRED COMPONENTS base core aui)
include("${wxWidgets_USE_FILE}")

add_executable(kangaroo WIN32
    app.cc
    main.cc
    main_window.cc
)
target_link_libraries(kangaroo ${wxWidgets_LIBRARIES})
