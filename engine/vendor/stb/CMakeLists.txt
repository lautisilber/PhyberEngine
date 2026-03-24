file(GLOB_RECURSE STB_SRC_FILES "${CMAKE_CURRENT_LIST_DIR}/src/*.cpp")
add_library(stb STATIC ${STB_SRC_FILES})
target_include_directories(stb
    PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/include"
)
