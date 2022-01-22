# Variable Modifiers #

## Automatic Variables: ```auto``` ##

In C. All local variables are automatic variables, as they get destroyed automatically after the function finishes execution, which is very efficient in terms of memory performance, since it frees up the memory it occupies since it is not used.

```C
// Both of these definitions are equivalent
int var = 5;
auto int var = 5;
```

- Things to take into account:
    1. If you don't initialize automatic variables, it will automatically take up some garbage (*random*) value.
    2. By default, global variables are initialized to zero.


## External Modifier: ```extern``` ##

- By default, when you declare a variable using for example ```int var;```, here the C compiler will allocate memory for the new variable, and since is not initialized, it will automatically take a random value.
- When you use ```extern int var;```, you instruct the compiler that you're only declaring a new variable, and therefore, the compiler won't assign a garbage value to this variable as they won't allocate any memory to it.
- ```extern``` is used when a particular file needs to access a variable from another file.
- Example:

    - Inside main.c file:

    ```C
    // main.c
    #include <stdio.h>

    extern int a;   // ONLY DECLARE a
    int main(int argc, char const *argv[]) {
        printf("%d\n", a);    // prints 5
        return 0;
    }
    ```
    - Inside other.c file:

    ```C
    // other.c
    int a = 5;
    ```
- In order to link both files, we have to complile the program like this:
    ```
    $gcc -o bin/program main.c other.c   
    ```


## Register Variables: ```register``` ##

- Register memory sits on top in terms of memory hierarchy, since it is extremely fast to access data stored in registers.

- When you use ```register``` modifier, you're instructing the compiler to store the variable in a register memory. This is done because access time is greatly reduced for most frequently referred variables.

- Usually compilers do themselves the optimization and they add register automatically to frequently used variables.


## Static Variables: ```static``` ##

Syntax:

```
static data_type var_name = var_value;
```

- A ```static``` ```int``` variable remains in memory while the program is running. A normal or ```auto``` variable is destroyed when a function call where the variable was declared is over.

- Static variables are allocated memory in data segment, not stack segment. See [memory layout of C programs](https://www.geeksforgeeks.org/memory-layout-of-c-program/) for details.

-  Static variables (like global variables) are initialized as 0 if not initialized explicitly. For example in the below program, value of x is printed as 0, while value of y is something garbage.

```C
#include <stdio.h>
int main()
{
	static int x;
	int y;
	printf("%d \n %d", x, y);
}
```

-  In C, static variables can only be initialized using constant literals. For example, following program fails in compilation.

```C
#include<stdio.h>

int initializer(void)
{
	return 50;
}

int main()
{
	static int i = initializer();
	printf(" value of i = %d", i);
	getchar();
	return 0;
}
```

Output:

```
In function 'main':
9:5: error: initializer element is not constant
     static int i = initializer();
     ^
```

- Static global variables and functions are also possible in C/C++. The purpose of these is to limit scope of a variable or function to a file. Please refer [Static functions in C](https://www.geeksforgeeks.org/what-are-static-functions-in-c/) for more details.

- Static variables should not be declared inside structure. The reason is C compiler requires the entire structure elements to be placed together (i.e.) memory allocation for structure members should be contiguous. It is possible to declare structure inside the function (stack segment) or allocate memory dynamically(heap segment) or it can be even global (BSS or data segment). Whatever might be the case, all structure members should reside in the same memory segment because the value for the structure element is fetched by counting the offset of the element from the beginning address of the structure. Separating out one member alone to data segment defeats the purpose of static variable and it is possible to have an entire structure as static.


## Constants: ```const``` and ```#define``` ##

1. We can define constants using [macros](Macros.md):

Syntax:

```
#define NAME value
```

Preprocessor is responsible for processing macros (*not the compiler*) by replacing the name with the value inside the source code.
> It is good practice to declare constants/macros with capital letters.

2. We can define constants using ```const``` keyword

Syntax:

```
const data_type NAME = value
```
