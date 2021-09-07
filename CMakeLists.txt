cmake_minimum_required(VERSION 3.18.0)
project(FolkEngine VERSION 0.1.0
                   LANGUAGES CXX C)

find_package(OpenGL REQUIRED)

set(EXTERN_INCLUDE_DIRS "extern/glad/include"
                        "extern/glfw/include")

add_library(FolkEngine FolkEngine.cpp)
target_include_directories(FolkEngine PUBLIC include/folk-engine)
target_compile_features(FolkEngine PUBLIC cxx_std_11)

add_executable(hello_opengl examples/hello_opengl.cpp)
target_include_directories(hello_opengl PUBLIC ${EXTERN_INCLUDE_DIRS})
target_link_libraries(hello_opengl glfw glad ${OPENGL_LIBRARIES})

add_subdirectory(extern)