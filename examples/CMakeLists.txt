function(add_example TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME})
    set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
    target_link_libraries(${TARGETNAME} folk_engine)
endfunction(add_example)

add_example(basic_setup basic_setup.cpp)
add_example(input_example input_example.cpp)