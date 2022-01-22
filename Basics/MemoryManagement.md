# Memory Management in C #

Almost all computer languages can handle system memory. All the variables used in your program occupies a precise memory space along with the program itself, which needs some memory for storing itself (i.e., its own program). Therefore, managing memory utmost care is one of the major tasks a programmer must keep in mind while writing codes.

When a variable gets assigned in a memory in one program, that memory location cannot be used by another variable or another program. So, C language gives us a technique of allocating memory to different variables and programs.

There are two types used for allocating memory. These are:

1. Static memory allocations.
2. Dynamic memory allocations.

In **the static memory allocation** technique, allocation of memory is done at compilation time, and it stays the same throughout the entire run of your program. Neither any changes will be there in the amount of memory nor any change in the location of memory.

In **dynamic memory allocation** technique, allocation of memory is done at the time of running the program, and it also has the facility to increase/decrease the memory quantity allocated and can also release or free the memory as and when not required or used. Reallocation of memory can also be done when required. So, it is more advantageous, and memory can be managed efficiently.

This tutorial is dedicated to discussing *dynamic memory management*.

## How dynamic memory allocation works ##

**Heap** is the memory section where dynamic memory allocation takes place.

C provides us with build-in functions that can help in allocating or deallocating some memory space at runtime.

Note that, allocated memory can only be accessed via **pointers**.

### Memory allocation using `malloc()` ###

`malloc` is defined in `<stdlib.h>`

Is used to allocate a single large block of contiguos memory according to the size specified.

Function signature:

```C
void* malloc( size_t size );
```

Allocates `size` bytes of uninitialized storage.

If allocation succeeds, returns a pointer that is suitably aligned for any object type with fundamental alignment.

> **What do we mean by alignment?**
> Every complete object type has a >property called alignment requirement, >which is an integer value of type size_t >representing the number of bytes between >successive addresses at which objects of ?this type can be allocated. The valid >alignment values are non-negative >integral powers of two.
>
>The alignment requirement of a type can be queried with `_Alignof`.(since C11)

On success, returns the pointer to the beginning of newly allocated memory. To avoid a memory leak, the returned pointer must be deallocated with `free()` or `realloc()`.

On failure, returns `NULL`.

>allocated memory is initialized with a garbage value.

Example:

```C
#include <stdio.h>   
#include <stdlib.h> 
 
int main(void) 
{
    int *p1 = malloc(4*sizeof(int));  // allocates enough for an array of 4 int
    int *p2 = malloc(sizeof(int[4])); // same, naming the type directly
    int *p3 = malloc(4*sizeof *p3);   // same, without repeating the type name
 
    if(p1) {
        for(int n=0; n<4; ++n) // populate the array
            p1[n] = n*n;
        for(int n=0; n<4; ++n) // print it back out
            printf("p1[%d] == %d\n", n, p1[n]);
    }
 
    free(p1);
    free(p2);
    free(p3);
}
```

Output:

```terminal
p1[0] == 0
p1[1] == 1
p1[2] == 4
p1[3] == 9
```

### Memory allocation using `calloc()` ###

is used to dynamically allocate multiple blocks of memory.

Function signature:

```C
void* calloc( size_t num, size_t size );
```

Allocates memory for an array of `num` objects of `size` bytes and initializes all bytes in the allocated storage to zero.

f allocation succeeds, returns *a pointer to the lowest (first) byte in the allocated memory block* that is suitably aligned for any object type.

If size is zero, the behavior is implementation defined (*null pointer* may be returned, or some non-null pointer may be returned that may not be used to access storage)

>Due to the alignment requirements, the number of allocated bytes is not necessarily equal to `num*size`.

Example:

```C
#include <stdio.h>
#include <stdlib.h>
 
int main(void)
{
    int *p1 = calloc(4, sizeof(int));    // allocate and zero out an array of 4 int
    int *p2 = calloc(1, sizeof(int[4])); // same, naming the array type directly
    int *p3 = calloc(4, sizeof *p3);     // same, without repeating the type name
 
    if(p2) {
        for(int n=0; n<4; ++n) // print the array
            printf("p2[%d] == %d\n", n, p2[n]);
    }
 
    free(p1);
    free(p2);
    free(p3);
}
```

### Memory allocation using `realloc()` ###

is used to change the size of the memory block without losing the old data.

Function header:

```C
void *realloc( void *ptr, size_t new_size );
```

`ptr`: pointer to the memory area to be reallocated.
`new_size`: new size of the array in bytes.

It reallocates the given area of memory. It must be previously allocated by `malloc()`, `calloc()` or `realloc()` and not yet freed with a call to `free` or `realloc`. Otherwise, the results are undefined.

The reallocation is done by either:

- expanding or contracting the existing area pointed to by ptr, if possible. The contents of the area remain unchanged up to the lesser of the new and old sizes. If the area is expanded, the contents of the new part of the array are undefined.
- allocating a new memory block of size new_size bytes, copying memory area with size equal the lesser of the new and the old sizes, and freeing the old block.

If there is not enough memory, the old memory block is not freed and null pointer is returned.

Example:

```C
#include <stdio.h>
#include <stdlib.h>

int main () {
   char *str;

   /* Initial memory allocation */
   str = (char *) malloc(15);
   strcpy(str, "Mywebsite");
   printf("String = %s,  Address = %u\n", str, str);

   /* Reallocating memory */
   str = (char *) realloc(str, 25);
   strcat(str, ".com");
   printf("String = %s,  Address = %u\n", str, str);

   free(str);
   
   return(0);
}
```

Output:

```terminal
String = Mywebsite, Address = 355090448
String = Mywebsite.com, Address = 355090448
```

### Releasing the dynamically allocated memory using `free()` ###

Function header:

```C
void free( void* ptr );
```

Deallocates the space previously allocated by `malloc()`, `calloc()`, `aligned_alloc()`, (since C11) or `realloc()`.

If ptr is a null pointer, the function does nothing.

The behavior is undefined if the memory area referred to by ptr has already been deallocated, that is, free() or realloc() has already been called with ptr as the argument and no calls to malloc(), calloc() or realloc() resulted in a pointer equal to ptr afterwards.

Example: 

```C
#include <stdlib.h>
 
int main(void)
{
    int *p1 = malloc(10*sizeof *p1);
    free(p1); // every allocated pointer must be freed
 
    int *p2 = calloc(10, sizeof *p2);
    int *p3 = realloc(p2, 1000*sizeof *p3);
    if(p3) // p3 not null means p2 was freed by realloc
       free(p3);
    else // p3 null means p2 was not freed
       free(p2);
}
```