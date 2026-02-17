cmake_minimum_required(VERSION 4.1.1)

set(TRIANGLE_EXPERIMENT_SOURCES
    "src/main.cpp"
    "src/app.cpp"
)

add_executable(triangle_experiment ${TRIANGLE_EXPERIMENT_SOURCES})
target_link_libraries(triangle_experiment PRIVATE shared)