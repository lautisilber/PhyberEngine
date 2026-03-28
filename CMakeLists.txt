cmake_minimum_required(VERSION 3.15)

option(BUILD_EXAMPLES "Build example programs" ON)

project(phyber_engine_project)
set(CMAKE_CXX_STANDARD 23)

add_subdirectory(engine)
add_subdirectory(game)
