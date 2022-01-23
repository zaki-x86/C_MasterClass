cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)
#############################################################
# set some variables and lists: 

set(SOURCE src/main.c)
set(ADD_LIB ${PROJECT_SOURCE_DIR}/libs/add)
set(SUB_LIB ${PROJECT_SOURCE_DIR}/libs/subtract)
#############################################################
# add configuration files for our headers

configure_file(config/TutorialConfig.h.in Configs.h)
##############################################################
# make the usage of our libraries optional 

option (USE_ARITH_KIT "Use our customer arithmetic library: Add, Subtract" ON)

if(USE_ARITH_KIT)
    
    add_subdirectory(${ADD_LIB})
    add_subdirectory(${SUB_LIB})

    
    # add the libraries we created (Add, Subtract) to a list

    list(APPEND LIBS Add Subtract)
    #list(APPEND LIBS_DIRCTORIES ${ADD_LIB} ${SUB_LIB})

endif()

###############################################################
add_executable(${PROJECT_NAME} ${SOURCE} src/commandx.c)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} ${LIBS})

#################################################################
# Set compiler flags 

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -O3 -std=c99" )
#################################################################
