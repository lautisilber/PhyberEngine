cmake_minimum_required(VERSION 3.25)
project(phyber_engine)

include(ExternalProject)

set(BUILD_SHARED_LIBS ON)

set(SDL_TESTS OFF)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vendor/SDL")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vendor/glm")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vendor/stb")

# Build SDL_shadercross (depends on SDL3 being built)
set(SDL_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/vendor/SDL")
ExternalProject_Add(
    SDL_shadercross
    SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/vendor/SDL_shadercross
    BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/SDL_shadercross_build
    DEPENDS SDL3::SDL3
    CMAKE_ARGS
        # -DCMAKE_INSTALL_PREFIX=${EXTERNAL_INSTALL_DIR}
        -DSDLSHADERCROSS_VENDORED=ON
        -DSDL3_DIR=${SDL_BUILD_DIR} # point to SDL we just built
        -DSDLSHADERCROSS_DXC=ON
        -DSDLSHADERCROSS_CLI=ON
        -DSDLSHADERCROSS_TESTS=OFF
    BUILD_ALWAYS 1
)

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_library(phyber_engine STATIC
        ${SRC_FILES}
        # "${CMAKE_CURRENT_LIST_DIR}/src/math.cpp"
        # "${CMAKE_CURRENT_LIST_DIR}/src/common_2d.cpp"
        # "${CMAKE_CURRENT_LIST_DIR}/src/renderer_2d.cpp"
    )

add_dependencies(phyber_engine SDL_shadercross)

set_property(TARGET phyber_engine PROPERTY CXX_STANDARD 23)
set_property(TARGET phyber_engine PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(phyber_engine
        PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

target_link_libraries(phyber_engine PRIVATE
        SDL3::SDL3
        stb
    )
target_link_libraries(phyber_engine PUBLIC
        glm::glm
    )

# function(compile_shaders source)

function(debug_flags target)
    if (APPLE)
        target_compile_options(${target} PRIVATE "-glldb")
    else()
        target_compile_options(${target} PRIVATE "-g")
    endif()
endfunction()

# set_property(TARGET phyber_engine PROPERTY COMPILE_WARNING_AS_ERROR ON)
debug_flags(phyber_engine)

# tests

if(NOT DEFINED PHYBER_TESTS)
    set(PHYBER_TESTS ON)
endif()

if(PHYBER_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/catch2")

    add_executable(phyber_engine_logging_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/logging_tests.cpp")
    target_link_libraries(phyber_engine_logging_tests PRIVATE
            phyber_engine
        )

    add_executable(phyber_engine_event_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/event_tests.cpp")
    target_link_libraries(phyber_engine_event_tests PRIVATE
            phyber_engine
        )

    add_executable(phyber_engine_renderer_2d_cpu_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/renderer_2d_cpu_tests.cpp")
    target_link_libraries(phyber_engine_renderer_2d_cpu_tests PRIVATE
            phyber_engine
        )
    debug_flags(phyber_engine_renderer_2d_cpu_tests)

    add_executable(phyber_engine_renderer_2d_gpu_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/renderer_2d_gpu_tests.cpp")
    target_link_libraries(phyber_engine_renderer_2d_gpu_tests PRIVATE
            phyber_engine
        )
    debug_flags(phyber_engine_renderer_2d_gpu_tests)

    add_executable(phyber_engine_sdl_test_triangle "${CMAKE_CURRENT_SOURCE_DIR}/tests/sdl_test_triangle.cpp")
    target_link_libraries(phyber_engine_sdl_test_triangle PRIVATE
        SDL3::SDL3
    )

    add_executable(phyber_engine_sdl_test_buffer "${CMAKE_CURRENT_SOURCE_DIR}/tests/sdl_test_buffer.cpp")
    target_link_libraries(phyber_engine_sdl_test_buffer PRIVATE
            SDL3::SDL3
        )

    add_executable(phyber_engine_sdl_test_events "${CMAKE_CURRENT_SOURCE_DIR}/tests/sdl_test_events.cpp")
    target_link_libraries(phyber_engine_sdl_test_events PRIVATE
            SDL3::SDL3
        )

    add_executable(phyber_engine_sdl_test_2d_gpu "${CMAKE_CURRENT_SOURCE_DIR}/tests/sdl_test_2d_gpu.cpp")
    target_link_libraries(phyber_engine_sdl_test_2d_gpu PRIVATE
            SDL3::SDL3
            glm::glm
        )
    debug_flags(phyber_engine_sdl_test_2d_gpu)
endif()
