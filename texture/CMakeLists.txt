cmake_minimum_required(VERSION 4.1.1)

set(TEXTURE_EXPERIMENT_SOURCES
    "src/main.cpp"
    "src/app.cpp"
)

add_executable(texture_experiment ${TEXTURE_EXPERIMENT_SOURCES})
target_link_libraries(texture_experiment PRIVATE shared)

add_custom_command(TARGET texture_experiment POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:texture_experiment>/images"
    COMMENT "Copying images to output directory..."
)