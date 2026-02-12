add_executable(GameTest main.cpp)

# set_property(TARGET GameTest PROPERTY CXX_STANDARD 20)

target_link_libraries(GameTest PRIVATE phyber_engine)
