# Step 3: Adding Libraries - Enhanced #

Demonstracting more CMake facilities and techniques while linking libraries to our source.

This step completed the same task done in [Step2]() with some additional features.

<br/>

## Setting variables in CMakeLists.txt ##

Syntax:

```CMake
set(<variable name> <value>)
```

When you use the variable, to dereference it, you will need to use it this way: 

```CMake
${<variable name>}
```

We used this feature extensively to enhance and refactor our code in the top level `CMakeLists.txt` in this project.

Our new CMakeLists.txt would like this:

```CMake
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
    list(APPEND LIBS_DIRCTORIES ${ADD_LIB} ${SUB_LIB})

endif()

###############################################################
add_executable(${PROJECT_NAME} ${SOURCE} src/commandx.c)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}" ${LIBS_DIRCTORIES})

target_link_libraries(${PROJECT_NAME} ${LIBS})

#################################################################
# Set compiler flags 

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -O3 -std=c99" )
#################################################################
```

<br/>

## Setting usage requirements for a library ##

Usage requirements allow for far better control over a library or executable's link and include line while also giving more control over the transitive property of targets inside CMake. The primary commands that leverage usage requirements are:

- `target_compile_definitions()`

- `target_compile_options()`

- `target_include_directories()`

- `target_link_libraries()`

We can refactor our code to use modern CMake approach of usage requirements. We first state that anybody linking to our library `Add` or `Subtract` needs to include the current source directory, while `Add` or `Subtract` itself doesn't. So this can become an `INTERFACE` usage requirement.

Modify libs/add/CMakeLists.txt this way:

```CMake
target_include_directories(Add INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
```

And also modify libs/subtract/CMakeLists.txt this way:

```CMake
target_include_directories(Subtract INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
```

Now that we've specified our usage requirement of our librarues, go to the top level `CMakeLists.txt` and remove any references of `LIBS_DIRECTORIES`:

```CMake
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

```