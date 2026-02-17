cmake_minimum_required(VERSION 4.1.1)

project(glad)

set(GLAD_SOURCES
    "src/gl.c"
)

add_library(glad STATIC ${GLAD_SOURCES})
target_include_directories(glad PUBLIC "include/")