if(WIN32)
    set(KG_PLATFORM_WIN)
endif()

if(UNIX)
    set(KG_PLATFORM_GTK)
endif()

include(CheckCXXSourceCompiles)

check_cxx_source_compiles("
    #include <filesystem>
    int main() { auto path { std::filesystem::current_path() }; }
    "

    HAS_FILESYSTEM)

if (NOT HAS_FILESYSTEM)
    set(CMAKE_REQUIRED_LIBRARIES stdc++fs)
    check_cxx_source_compiles("
        #include <experimental/filesystem>
        int main() { auto path { std::experimental::filesystem::current_path() }; }
        "

        HAS_EXPERIMENTAL_FILESYSTEM)

    if (NOT HAS_EXPERIMENTAL_FILESYSTEM)
        message(FATAL_ERROR "Could not find <filesystem> support.")
    endif()
endif()

add_library(std.fs INTERFACE IMPORTED GLOBAL)

if(HAS_EXPERIMENTAL_FILESYSTEM)
    target_link_libraries(std.fs INTERFACE stdc++fs)
    target_compile_definitions(std.fs INTERFACE __kg_experimental_fs)
endif()

configure_file(cmake/features.h kg_features.h @ONLY)
target_include_directories(std.fs INTERFACE ${CMAKE_CURRENT_BINARY_DIR})
