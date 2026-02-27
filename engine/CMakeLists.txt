project(phyber_engine)

set(SDL_TESTS OFF)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vendor/SDL")

file(GLOB SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
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

# tests

if(NOT DEFINED PHYBER_TESTS)
    set(PHYBER_TESTS ON)
endif()

if(PHYBER_TESTS)
    add_subdirectory("${CMAKE_CURRENT_SOURCE_DIR}/vendor/catch2")

    add_executable(phyber_engine_math_tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/math_tests.cpp")
    target_link_libraries(phyber_engine_math_tests PRIVATE
        phyber_engine
        # thank you https://arainablog.tistory.com/750
        Catch2::Catch2WithMain
    )

    add_executable(phyber_engine_sdl_test "${CMAKE_CURRENT_SOURCE_DIR}/tests/sdl_test.cpp")
    target_link_libraries(phyber_engine_sdl_test PRIVATE
        phyber_engine
        SDL3::SDL3
    )
endif()
