project(phyber_engine)

set(BUILD_SHARED_LIBS ON)

set(SDL_TESTS OFF)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vendor/SDL")
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vendor/glm")

file(GLOB_RECURSE SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_library(phyber_engine STATIC
    ${SRC_FILES}
    # "${CMAKE_CURRENT_LIST_DIR}/src/math.cpp"
    # "${CMAKE_CURRENT_LIST_DIR}/src/common_2d.cpp"
    # "${CMAKE_CURRENT_LIST_DIR}/src/renderer_2d.cpp"
)

set_property(TARGET phyber_engine PROPERTY CXX_STANDARD 23)
set_property(TARGET phyber_engine PROPERTY CXX_STANDARD_REQUIRED ON)

target_include_directories(phyber_engine
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)

target_link_libraries(phyber_engine PRIVATE
    SDL3::SDL3
)
target_link_libraries(phyber_engine PUBLIC
    glm::glm
)

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

    add_executable(phyber_engine_renderer_2d_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/renderer_2d_tests.cpp")
    target_link_libraries(phyber_engine_renderer_2d_tests PRIVATE
        phyber_engine
    )

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
endif()
