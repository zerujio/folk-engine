add_executable(folk_test catch_main.cpp core.cpp math.cpp)
target_link_libraries(folk_test folk_engine)
target_include_directories(folk_test PUBLIC ../src)