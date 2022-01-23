# Step2: Working with Libraries #

Our project structure:

```terminal
Step2/
    build/
    libs/
        custom/
        extern/
    customer/
    CMakeLists.txt
    TutorialConfig.h.in
    main.c
```

We will add the same script as in [Step1]() as boiler plate.

CMakeLists:

```cmake
cmake_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)

configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}"
)

# specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
```

In order to add a library, we need to create another CMakeLists.txt file to our library's directory:

```terminal
user@xuser:/home/Step2$  cd libs/custom
user@xuser:/home/Step2/libs/custom$ touch myio.c myio.h CMakeLists.txt
```

Our new library `myio` will containt some custom utilities to handle user input.

Then we instantiate our library inside a new cmake file located here: `/home/Step2/libs/custom/CMakeLists.txt`.

```cmake
add_library(CustomIO myio.c)
```

In the function `add_library()` we add a name that we assign to our library, in this case it is `CustomIO` then we add the path to the source file.

A single library can have multiple source files, therefore, it can look like this:

```cmake
add_library(CustomLib /path/to/src1.c
    /path/to/src2.c
    /path/to/src3.c
)
```

To make use of the new library we will add an `add_subdirectory()` call in the top-level `CMakeLists.txt` file so that the library will get built:

`/home/Step2/CMakeLists.txt`:

```CMake
make_minimum_required(VERSION 3.10)

project(Tutorial VERSION 1.0)

add_subdirectory(libs/custom)

configure_file(TutorialConfig.h.in TutorialConfig.h)

add_executable(${PROJECT_NAME} main.c)

target_link_libraries(${PROJECT_NAME} PUBLIC CustomIO)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}"
"${PROJECT_SOURCE_DIR}/libs"
)

# specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)
```

What we have done so far:

1. Created a `CMakeLists.txt` inside our library's directory, and gave a name to our library.
2. In top level `CMakeLists.txt` we add the following:
   1. A subdirectory to our library.
   2. We linked our library to the main project and setup a visibility level:
   `target_link_libraries(<Project Name>, <Visibility>, <Library Name>)`
   3. We included target directory to our library:
   `target_include_directories(<Project Name>, <Visibility>, </source/to/library>)`

The following steps can also be done, yet they are optional:

we can make the `CustomIO` library optional. The first step is to add an option to the top-level `CMakeLists.txt` file.

```CMake
option(USE_CUSTOMIO "Use tutorial provided math implementation" ON)
```

The next change is to make building and linking the `CustomIO` library conditional. To do this, we will create an `if` statement which checks the value of the option. Inside the `if` block, put the `add_subdirectory()` command from above with some additional list commands to store information needed to link to the library and add the subdirectory as an include directory in the `Tutorial` target. The end of the top-level `CMakeLists.txt` file will now look like the following:

```CMake
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
```

Note the use of the variable `EXTRA_LIBS` to collect up any optional libraries to later be linked into the executable.

The variable `EXTRA_INCLUDES` is used similarly for optional header files.

This is a classic approach when dealing with many optional components, **we will cover the modern approach in the next step**.

The corresponding changes to the source code are fairly straightforward. First, in main.c, include the header if we need it:

```C
#ifdef USE_CUSTOMIO
#include "libs/custom/myio.h"
#endif
```

Note that our compiler knows nothing about `USE_CUSTOMIO` header yet, therefore, we need to update `TutorialConfig.h.in` with the following line:

```C
#cmakedefine USE_MYMATH
```

Now you can build and run.

To leverage the optional library feature, you will need to do this when building:

```terminal
cmake ../Step2 -DUSE_MYMATH=OFF
```
