set(SHADER_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

folk_add_shader(default_vert_shader "vs_default.sc" VERTEX "${SHADER_DIR}/vs_default.bin")
folk_add_shader(default_frag_shader "fs_default.sc" FRAGMENT "${SHADER_DIR}/fs_default.bin")

add_custom_target(default_shaders)
add_dependencies(default_shaders default_vert_shader default_frag_shader)

function(add_example TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME})
    set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
    target_link_libraries(${TARGETNAME} folk_engine)
endfunction()

add_example(basic_example basic_example.cpp)
add_example(input_example input_example.cpp)

add_custom_target(folk_examples ALL)
add_dependencies(folk_examples basic_example input_example default_shaders)

add_executable(hello-bgfx hello-bgfx.cpp)
target_link_libraries(hello-bgfx glfw bgfx_interface)