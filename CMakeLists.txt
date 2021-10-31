cmake_minimum_required(VERSION 3.16.0)
project(FolkEngine VERSION 0.1.0
                   LANGUAGES C CXX)

find_package(OpenGL REQUIRED)

find_package(Doxygen)

# external dependencies
add_subdirectory(extern)

# configure engine library
add_subdirectory(src)

# examples
add_subdirectory(examples)

# documentation
if(DOXYGEN_FOUND)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_OUTPUT_LANGUAGE SPANISH)

    doxygen_add_docs(folk_docs include README.md)
endif()