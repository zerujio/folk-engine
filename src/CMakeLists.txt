add_library(folk_engine STATIC)
set_property(TARGET folk_engine PROPERTY FOLDER lib)
target_compile_features(folk_engine PUBLIC cxx_std_17)

#include directories
#set(EXTERN_INCLUDE_DIRS "glad/include" "glfw/include" "entt/single_include")
#list(TRANSFORM EXTERN_INCLUDE_DIRS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/extern/")

#set(FOLK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
#set(FOLK_LIBS glfw glad imgui ${OPENGL_LIBRARIES})

set(FOLK_EXTERN_LIBS glad glfw cxxopts)

target_include_directories(folk_engine PUBLIC ../include)
target_link_libraries(folk_engine PUBLIC entt bgfx_interface)
target_link_libraries(folk_engine PRIVATE ${FOLK_EXTERN_LIBS})

function(add_engine_subdir FOLDER)
    set(SOURCES "")
    include(${FOLDER}/sources.cmake)
    list(TRANSFORM SOURCES PREPEND "${FOLDER}/")
    target_sources(folk_engine PRIVATE ${SOURCES})
endfunction(add_engine_subdir)

add_engine_subdir(audio)
add_engine_subdir(core)
add_engine_subdir(render)
add_engine_subdir(scene)
add_engine_subdir(utils)
add_engine_subdir(window)
add_engine_subdir(input)
add_engine_subdir(debug)
add_engine_subdir(math)
