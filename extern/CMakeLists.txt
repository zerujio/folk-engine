#glad
add_subdirectory(glad)

#glfw
set(GLFW_BUILD_TESTS OFF)
set(GLFW_BUILD_EXAMPLES OFF)
set(GLFW_INSTALL OFF)
add_subdirectory(glfw)

#imgui
add_library(imgui STATIC)
target_sources(imgui PRIVATE
               imgui/imgui_demo.cpp
               imgui/imgui_draw.cpp
               imgui/imgui_tables.cpp
               imgui/imgui_widgets.cpp
               imgui/imgui.cpp
               imgui/backends/imgui_impl_glfw.cpp
               imgui/backends/imgui_impl_opengl3.cpp)
target_include_directories(imgui PUBLIC imgui)
target_link_libraries(imgui glad glfw)

# entt
add_library(entt INTERFACE)
target_include_directories(entt INTERFACE entt/single_include)

# cxxopts
add_subdirectory(cxxopts)

# OpenAL
add_subdirectory(openal-soft)

# dr_libs
add_library(dr_libs INTERFACE)
target_include_directories(dr_libs INTERFACE dr_libs)

# glm
add_subdirectory(glm)

#stb_image
add_library(stb_image STATIC stb/stb_image.c)
target_include_directories(stb_image INTERFACE stb)