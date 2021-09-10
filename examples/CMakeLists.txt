function(add_example TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME})
    set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
    target_link_libraries(${TARGETNAME} folk_engine)
endfunction(add_example)

add_example(basic_setup basic_setup.cpp)

add_executable(hello_opengl hello_opengl.cpp)
set_property(TARGET hello_opengl PROPERTY FODLER examples)
target_include_directories(hello_opengl PRIVATE ${EXTERN_INCLUDE_DIRS})
target_link_libraries(hello_opengl ${FOLK_LIBS})
