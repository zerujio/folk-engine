cmake_minimum_required(VERSION 3.18.0)
project(FolkEngine VERSION 0.1.0
                   LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

find_package(Doxygen)

set(EXTERN_INCLUDE_DIRS "glad/include" "glfw/include")
list(TRANSFORM EXTERN_INCLUDE_DIRS PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/extern/")

set(FOLK_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(FOLK_LIBS glfw glad ${OPENGL_LIBRARIES})

# configure engine library
add_subdirectory(src)

# external dependencies
add_subdirectory(extern)

# examples
add_subdirectory(examples)

# documentation
if(DOXYGEN_FOUND)
    doxygen_add_docs(folk_docs include src)
endif()