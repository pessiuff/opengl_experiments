cmake_minimum_required(VERSION 4.2.1)

set(CUBE_EXPERIMENT_SOURCES
    "src/main.cpp"
    "src/app.cpp"
)

add_executable(cube_experiment ${CUBE_EXPERIMENT_SOURCES})
target_link_libraries(cube_experiment PRIVATE shared)

add_custom_command(TARGET cube_experiment POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_CURRENT_SOURCE_DIR}/images"
        "$<TARGET_FILE_DIR:cube_experiment>/images"
    COMMENT "Copying images to output directory..."
)