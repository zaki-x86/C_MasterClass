# Memory Manipulation in C #

The C standrad library provides us with facilities in header `<string.h>` to handle memory manipulation efficiently.

## Comparing blocks of memory: `memcmp` ##

Function signature:

```C
int memcmp( const void* lhs, const void* rhs, size_t count );
```

Check: [cpp reference](https://en.cppreference.com/w/c/string/byte/memcmp)

Compares the first `count` characters of the objects pointed to by `lhs` and `rhs`.

The sign of the result is the sign of the difference between the values of the first pair of **bytes** (both interpreted as `unsigned char`) that differ in the objects being compared.

### Parameters ###

- `lhs`, `rhs` - pointers to the objects to compare
- `count` - number of bytes to examine

### Return value ###

- Negative value if `lhs` appears before `rhs` in lexicographical order.

- Zero if `lhs` and `rhs` compare equal, or if `count` is zero.

- Positive value if lhs appears after rhs in lexicographical order.

Examples:

```C
int arr1[] = { 1, 2 };
int arr2[] = { 1, 2 };

if(memcmp(arr1, arr2, 2 * sizeof int) == 0)
    printf("Arrays are equal\n");
else
    printf("Arrays are not the same\n");
```

## Copying blocks of memory: `memcpy` ##

Function signature:

```C
void* memcpy( void *dest, const void *src, size_t count );
```

Check: [cpp reference](https://en.cppreference.com/w/c/string/byte/memcpy)

1) Copies `count` characters from the object pointed to by `src` to the object pointed to by `dest`. Both objects are interpreted as arrays of `unsigned char`.

### Parameters ###

`dest` -  pointer to the object to copy to
`src`  -  pointer to the object to copy from
`count` -  number of bytes to copy

### Return value ###

1) Returns a copy of `dest`
2) Returns zero on success and non-zero value on error.

### Notes ###

`memcpy` may be used to set **[the effective type]()** of an object obtained by an allocation function.

`memcpy` is the fastest library routine for memory-to-memory copy. It is usually more efficient than `strcpy`, which must scan the data it copies or `memmove`, which must take precautions to handle overlapping inputs.

Several C compilers transform suitable memory-copying loops to `memcpy` calls.

Examples:

```C
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
 
int main(void)
{
    // simple usage
    char source[] = "once upon a midnight dreary...", dest[4];
    memcpy(dest, source, sizeof dest);
    for(size_t n = 0; n < sizeof dest; ++n)
        putchar(dest[n]);

    // setting effective type of allocated memory to be int
    int *p = malloc(3*sizeof(int));   // allocated memory has no effective type
    int arr[3] = {1,2,3};
    memcpy(p,arr,3*sizeof(int));      // allocated memory now has an effective type

    // reinterpreting data
    double d = 0.1;
    //    int64_t n = *(int64_t*)(&d); // strict aliasing violation
    int64_t n;
    memcpy(&n, &d, sizeof d); // OK
    printf("\n%a is %" PRIx64 " as an int64_t\n", d, n);
```

## Copying a single byte of memory: `memset` ##

Function signature:

```C
void *memset( void *dest, int ch, size_t count );
```

Copies the value `ch` (after conversion to `unsigned char` as if by `(unsigned char)ch`) into each of the first `count` characters of the object pointed to by `dest`.
The behavior is undefined if access occurs beyond the end of the `dest` array. The behavior is undefined if `dest` is a null pointer.

### Parameters ###

`dest` - pointer to the object to fill
`ch` - fill byte
`count` - number of bytes to fill

### Return value ###

A copy of dest

Example:

```C
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
 
int main(void)
{
    char str[] = "ghghghghghghghghghghgh";
    puts(str);
    memset(str,'a',5);
    puts(str);  // aaaaahghghghghghghghgh
}
```
