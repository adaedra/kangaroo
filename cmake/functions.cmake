function(kg_target)
    cmake_parse_arguments(KG_TARGET "SHARED" "NAME;TYPE" "SOURCES;WIN_SOURCES;GTK_SOURCES;LINK" ${ARGN})

    set(KG_TARGET_ALL_SOURCES ${KG_TARGET_SOURCES})

    if(KG_PLATFORM_WIN)
        list(APPEND KG_TARGET_ALL_SOURCES ${KG_TARGET_WIN_SOURCES})
    endif()

    if(KG_PLATFORM_GTK)
        list(APPEND KG_TARGET_ALL_SOURCES ${KG_TARGET_GTK_SOURCES})
    endif()

    if(KG_TARGET_TYPE STREQUAL "LIBRARY")
        if(KG_TARGET_SHARED)
            add_library(${KG_TARGET_NAME} SHARED ${KG_TARGET_ALL_SOURCES})
        else()
            add_library(${KG_TARGET_NAME} STATIC ${KG_TARGET_ALL_SOURCES})
            set_target_properties(${KG_TARGET_NAME} PROPERTIES POSITION_INDEPENDENT_CODE ON)
        endif()
    else()
        add_executable(${KG_TARGET_NAME} WIN32 ${KG_TARGET_ALL_SOURCES})
    endif()

    if(KG_TARGET_LINK)
        target_link_libraries(${KG_TARGET_NAME} ${KG_TARGET_LINK})
    endif()
endfunction()
