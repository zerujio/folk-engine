cmake_minimum_required(VERSION 3.18.0)
project(FolkEngine VERSION 0.1.0
                   LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

find_package(Doxygen)

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