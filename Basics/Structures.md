# Structures #

A structure is a user defined data type in C/C++. A structure creates a data type that can be used to group items of possibly different types into a single type.

**Syntax:**

```bash
struct CustomType
{
    Type variable1;
    Type variable2;
    ..
}
```

## Declaration and Initialization ##

There are two ways to declare a struct variable:

Method(1):

```C
// A variable declaration with structure declaration.
struct Point
{
int x, y;
} p1; // The variable p1 is declared with 'Point'
```

Method(2):

```C
// A variable declaration like basic data types
struct Point
{
int x, y;
};

int main()
{
struct Point p1; // The variable p1 is declared like a normal variable
}
```

You can't initialize struct members during declaration as it will result in a compilation error.

```C
struct Point
{
int x = 0; // COMPILER ERROR: cannot initialize members here
int y = 0; // COMPILER ERROR: cannot initialize members here
};
```

The reason for above error is simple, when a datatype is declared, no memory is allocated for it. Memory is allocated only when variables are created.

Structure members can be initialized using curly braces ‘{}’. For example, following is a valid initialization.

```C
struct Point
{
int x, y;
};

int main()
{
// A valid initialization. member x gets value 0 and y
// gets value 1. The order of declaration is followed.
struct Point p1 = {0, 1};
}
```

### Accessing Structure Members ###

Structure members are accessed using dot (.) operator.

```C
#include <stdio.h>

struct Point
{
int x, y;
};

int main()
{
struct Point p1 = {0, 1};

// Accessing members of point p1
p1.x = 20;
printf ("x = %d, y = %d", p1.x, p1.y);

return 0;
}
```

Output:

```terminal
x = 20, y = 1
```

You can use **designated initialization** with structures as we did before with [arrays]().

```C
#include <stdio.h>

struct Point
{
int x, y, z;
};

int main()
{
// Examples of initialization using designated initialization
struct Point p1 = {.y = 0, .z = 1, .x = 2};
struct Point p2 = {.x = 20};

printf ("x = %d, y = %d, z = %d\n", p1.x, p1.y, p1.z);
printf ("x = %d", p2.x);
return 0;
}
```

Output:

```terminal
x = 2, y = 0, z = 1
x = 20
```

## Features and Limitations ##

Since structres are customer data types so they can be treated and processed like premitive data type, which means that, you can create arrays of structures, pointers to structures .. etc.

Examples:

1. Arrays of Structures.

    ```C
    #include <stdio.h>

    struct Point
    {
    int x, y;
    };

    int main()
    {
    // Create an array of structures
    struct Point arr[10];

    // Access array members
    arr[0].x = 10;
    arr[0].y = 20;

    printf("%d %d", arr[0].x, arr[0].y);
    return 0;
    }
    ```

2. Structure Pointers. Like primitive types, we can have pointer to a structure. If we have a pointer to structure, members are accessed using arrow ( -> ) operator.

    ```C
    #include <stdio.h>

    struct Point
    {
    int x, y;
    };

    int main()
    {
    struct Point p1 = {1, 2};

    // p2 is a pointer to structure p1
    struct Point *p2 = &p1;

    // Accessing structure members using structure pointer
    printf("%d %d", p2->x, p2->y);
    return 0;
    }
    ```

### Limitations ###

- The C structure does not allow the struct data type to be treated like built-in data types, meaning that, We cannot use operators like +,- etc. on Structure variables. For example, consider the following code:

    ```C
    struct number
    {
        float x;
    };

    int main()
    {
        struct number n1,n2,n3;
        n1.x=4;
        n2.x=3;
        n3=n1+n2;
        return 0;
    }

    /*Output:

    prog.c: In function 'main':
    prog.c:10:7: error:
    invalid operands to binary + (have 'struct number' and 'struct number')
    n3=n1+n2;

    */
    ```

- **No Data Hiding**: C Structures do not permit data hiding. Structure members can be accessed by any function, anywhere in the scope of the Structure.

- **Functions inside Structure**: C structures do not permit functions inside Structure (at least directly!).

- **Static Members**: C Structures cannot have static members inside their body.

- **Access Modifiers**: C Programming language do not support access modifiers. So they cannot be used in C Structures.

- **Construction creation in Structure**: Structures in C cannot have constructor inside Structures.

### Using `typedef` to declare `structs` ###

`typedef` gives freedom to create your own types from pre-existing types.

Examples:

```C
typedef int Integer;
typedef char* String;
```

Similarly we can write our own type by combining the power of both `typedef` and structures:

```C
typedef struct automobile
{
    char engine[50];
    char fuel_type[10];
    // ..
} Automobile;

int main(void)
{
    Automobile vehicle;
}

```

## Structure Padding ##

**How memory is allocated to structure members?**
when an object of some structure type is declared, some contiguos block of memory will be allocated to structure members.

Example:

```C
struct X
{
    char a;  // 1 byte
    char b;  // 1 byte
    int c;   // 4 bytes 
} var;
```

Looking at struct `var`, at first glance, you would assume that the size of this struct is (1 + 1 + 4) bytes, which is 6 bytes. However, it is not correct. **Why?**

Processor doesn't read one byte at a time from memory, but it does read one **word** at a time.

For a 32-bit processor, it can access 4 bytes at a time which means that, word size is 4 bytes.

Similary, for a 64-bit processor, it can read 8 bytes at a time.

The problem with struct `var`, assuming our processor is 32-bit, is that, in 1 CPU cycle, the processor reads `char a`, `char b`, 2 bytes of `int c`. Therefore, when trying to access variable `int c`, we will require 2 CPU cycles to read this variable because in the first cycle we can only get 2 bytes of `int c`.

**Structure padding** is a mechanism to fix such issues as explained above.We use it to save processor cycles.

![Compiler adds 2 bytes](assets/struct%20padding.png)
Source: [Neso Academy](https://youtu.be/aROgtACPjjg?list=PLBlnK6fEyqRhX6r2uhhlubuF5QextdCSM&t=246)

In such situations, the compilers add an additional space of memory to optimize CPU cycles. In this case, it will add 2 bytes, therefore, when you excute `sizeof(var)`, the output will be 8 instead of 6.

## Structure Packing ##

As we discussed in structure padding, the size of the structure becomes larger than its actual size. Therefore, alot of memeory will be wasted for the sake of optimizing CPU cycles.

We can avoid memory waste by adding this preprocessor directive:

```C
#pragma pack(1)
```

>`#pragma` is a special purpose directive used to turn on or off some certain features.

When you switch packing on, CPU cycles will be wasted but we will save memory space.
