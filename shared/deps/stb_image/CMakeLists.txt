cmake_minimum_required(VERSION 4.2.1)

project(stb_image)

set(STB_IMAGE_SOURCES
    "src/image.c"
)

add_library(stb_image STATIC ${STB_IMAGE_SOURCES})
target_include_directories(stb_image PRIVATE "include/stb/")
target_include_directories(stb_image PUBLIC "include/")