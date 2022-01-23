cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)

#add_subdirectory(libs/custom)
configure_file(TutorialConfig.h.in TutorialConfig.h)

option(USE_CUSTOMIO "Use tutorial provided math implementation" ON)

if(USE_CUSTOMIO)
  add_subdirectory(libs/custom)
  list(APPEND EXTRA_LIBS CustomIO)
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/libs/custom")
endif()

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PUBLIC ${EXTRA_LIBS})

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}"
${EXTRA_INCLUDES}
)

# specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

