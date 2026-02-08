cmake_minimum_required(VERSION 4.2.1)

add_subdirectory(deps)

set(SHARED_SOURCES
    "src/core/app.cpp"
    "src/gfx/shader_program.cpp"
)

add_library(shared STATIC ${SHARED_SOURCES})
target_link_libraries(shared PUBLIC glfw glad)
target_include_directories(shared PRIVATE "include/shared/")
target_include_directories(shared PUBLIC "include/")