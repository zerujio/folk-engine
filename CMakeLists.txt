cmake_minimum_required(VERSION 3.16.0)
project(FolkEngine VERSION 0.1.0 LANGUAGES C CXX)

find_package(OpenGL REQUIRED)
set(FOLK_OPENGL_VERSION_MAJOR 4)
set(FOLK_OPENGL_VERSION_MINOR 3)
add_compile_definitions(
        FOLK_OPENGL_VERSION_MAJOR=${FOLK_OPENGL_VERSION_MAJOR}
        FOLK_OPENGL_VERSION_MINOR=${FOLK_OPENGL_VERSION_MINOR}
        $<$<CONFIG:Debug>:FOLK_DEBUG>)


find_package(Doxygen)

# external dependencies
add_subdirectory(extern)

# configure engine library
add_subdirectory(src)

# examples
add_subdirectory(examples)

# tests
add_subdirectory(test)

# documentation
if(DOXYGEN_FOUND)
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_OUTPUT_LANGUAGE SPANISH)

    doxygen_add_docs(folk_docs include src README.md)
endif()
