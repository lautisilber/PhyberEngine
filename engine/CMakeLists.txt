add_library(phyber_engine STATIC
    ${CMAKE_CURRENT_LIST_DIR}/src/math.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/common_2d.cpp
    # ${CMAKE_CURRENT_LIST_DIR}/src/renderer_2d.cpp
)

# set_property(TARGET phyber_engine PROPERTY CXX_STANDARD 20)

target_include_directories(phyber_engine
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
