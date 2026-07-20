cmake_minimum_required(VERSION 3.20)

# Project
project(SimpleDoodleJump VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Try to find SFML 3 first, fall back to SFML 2.5 if necessary
find_package(SFML 3 COMPONENTS Graphics Window System Audio QUIET)
if(SFML_FOUND)
    set(SFML_TARGETS
        SFML::Graphics
        SFML::Window
        SFML::System
        SFML::Audio)
else()
    find_package(SFML 2.5 COMPONENTS graphics window system audio QUIET)
    if(TARGET SFML::Graphics)
        set(SFML_TARGETS
            SFML::Graphics
            SFML::Window
            SFML::System
            SFML::Audio)
    else()
        # Some systems provide non-target library names
        find_library(SFML_GRAPHICS_LIB NAMES sfml-graphics)
        find_library(SFML_WINDOW_LIB NAMES sfml-window)
        find_library(SFML_SYSTEM_LIB NAMES sfml-system)
        if(SFML_GRAPHICS_LIB AND SFML_WINDOW_LIB AND SFML_SYSTEM_LIB)
            set(SFML_TARGETS ${SFML_GRAPHICS_LIB} ${SFML_WINDOW_LIB} ${SFML_SYSTEM_LIB})
        else()
            message(FATAL_ERROR "Could not find SFML (required). Install SFML or adjust CMake settings.")
        endif()
    endif()
endif()

# Collect sources
file(GLOB_RECURSE GAME_SOURCES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(DoodleJump ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp ${GAME_SOURCES})

target_include_directories(DoodleJump PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(DoodleJump PRIVATE ${SFML_TARGETS})

# Put runtime in a predictable folder
set_target_properties(DoodleJump PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Copy assets, fonts and highscore to the output folder after build
add_custom_command(TARGET DoodleJump POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/assets"
            "$<TARGET_FILE_DIR:DoodleJump>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            "${CMAKE_SOURCE_DIR}/fonts"
            "$<TARGET_FILE_DIR:DoodleJump>/fonts"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${CMAKE_SOURCE_DIR}/highscore.txt"
            "$<TARGET_FILE_DIR:DoodleJump>/highscore.txt"
)

message(STATUS "Configured project ${PROJECT_NAME} (C++ ${CMAKE_CXX_STANDARD})")
