cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)


add_executable(${PROJECT_NAME} main.c)

configure_file(TutorialConfig.h.in TutorialConfig.h)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}"
)

# specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)