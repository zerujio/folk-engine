set(SHADER_DIR "${CMAKE_CURRENT_BINARY_DIR}/shaders")

folk_add_shader(default_vert_shader "vs_default.sc" VERTEX "${SHADER_DIR}/vs_default.bin")
folk_add_shader(default_frag_shader "fs_default.sc" FRAGMENT "${SHADER_DIR}/fs_default.bin")

add_custom_target(default_shaders)
add_dependencies(default_shaders default_vert_shader default_frag_shader)

add_custom_target(folk_examples ALL)
add_dependencies(folk_examples basic_example input_example default_shaders)

function(add_example TARGETNAME FILENAME)
    add_executable(${TARGETNAME} ${FILENAME})
    set_property(TARGET ${TARGETNAME} PROPERTY FOLDER examples)
    target_link_libraries(${TARGETNAME} folk_engine)
    add_dependencies(folk_examples ${TARGETNAME})
endfunction()

add_example(basic_example basic_example.cpp)
add_example(input_example input_example.cpp)
add_example(audio_example audio_example.cpp)
add_example(script_example script_example.cpp)
add_example(behavior_tree_example behavior_tree_example.cpp)

add_executable(hello-bgfx hello-bgfx.cpp)
target_link_libraries(hello-bgfx glfw bgfx_interface)

add_executable(hello-audio hello-audio.cpp)
target_link_libraries(hello-audio dr_libs OpenAL)
set_property(TARGET hello-audio PROPERTY CXX_STANDARD 17)