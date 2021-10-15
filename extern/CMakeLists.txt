#glad
add_subdirectory(glad)

#glfw
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
target_include_directories(imgui PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/imgui")
target_link_libraries(imgui glad glfw)