# Pointers #

Pointer is a special variable that is capable of storing the address of another variable.

It points to a memory location where the first byte is stored.

## Basics of Pointers ##

Like any variable or constant, you must declare a pointer before using it to store any variable address. The general form of a pointer variable declaration is −

```
Type* pointer_name;
```

> ```Type```: refers to the type of the variable that the pointer points to.


### Initializing a pointer variable ####

One way to initialize a pointer is store an address of another variable in it.

```c
// ptr stores the address of x
int x = 5;
int *ptr = &x;
```

To initialize an empty pointer, a.k.a, a pointer that doesn't store any address, we use the ```NULL``` keyword.

```C
int *ptr = NULL;
```

### Dereferencing a pointer ####

Usually, we will need to know what value does a pointer points to, this process is called "*Dereferencing*" a pointer.

```C
int x = 5;
int *ptr;
ptr = &x;

printf("%d\n", *ptr); // prints 5
```

We use the asterisk in ```*ptr``` to dereference the pointer and extract the value that it points to.

We can also change the value pointed by the pointer object:

```C
int x = 5;
int *ptr;
ptr = &x;
*ptr = 10;
printf("%d\n", *ptr); // prints 10
```

> Note that, dereferencing an uninitialized pointer produces a garbage value.

> Always initialize your pointers!

`Segmentation Fault` errors are quite frequent when dealing with pointers, they often occur when you try dereference an uninitialized pointer or when you try to read or write an illegal memory location.


### Assigning the content of one pointer to another ###

```C
int x = 10;
int *ptr1, *ptr2;

ptr1 = &x;
ptr2 = &ptr1;

// Now, both ptr1, ptr2 points to the same memory location

printf("%d %d\n", *ptr1, *ptr2); //10 10
```

### Returning pointers from a function ###

`return_ptr()` is a dummy function that takes a pointer parameter and returns the address of the value it points to.

```C
// a prototype of a function that returns a pointer to int.
int* return_ptr(int*);

int* return_ptr(int *a) {
    return a;
}
```

inside `main()`:

```C
int main(int argc, char const *argv[]) {

    int* ptr = NULL;
    int x = 5;

    ptr = return_ptr(&x);

    printf("value: %d is stored in memory address: %p\n", *ptr, ptr);

    getch();

    return 0;
}
```

### Caution: Don't return the address of an auto variable ###

Consider this function `foo()`:

```C
int *foo() {
    int i = 10;
    return &i;
}
```

Calling this function will returns an error, because after this function finished execution, all local variables are destroyed and you can't return the address of a destroyed variable.

## Pointer Arithmetic ##

A pointer in c is an address, which is a numeric value. Therefore, you can perform arithmetic operations on a pointer just as you can on a numeric value. There are four arithmetic operators that can be used on pointers: ++, --, +, and -.

To understand pointer arithmetic, let us consider that ptr is an integer pointer which points to the address 1000. Assuming 32-bit integers, let us perform the following arithmetic operation on the pointer −
```C
ptr++;
```
After the above operation, the ptr will point to the location 1004 because each time ptr is incremented, it will point to the next integer location which is 4 bytes next to the current location. This operation will move the pointer to the next memory location without impacting the actual value at the memory location. If ptr points to a character whose address is 1000, then the above operation will point to the location 1001 because the next character will be available at 1001.

The same considerations apply to decrementing a pointer, which decreases its value by the number of bytes of its data type.

<br/>

## Pointer Comparisons ##

Pointers may be compared by using relational operators, such as ==, <, and >. If p1 and p2 point to variables that are related to each other, such as elements of the same array, then p1 and p2 can be meaningfully compared.

Consider the following example:

```C
int main(int argc, char const *argv[])
{
    int a[] = { 1, 2, 3, 4, 5 }
    int *p1 = &a[1];
    int *p2 = &a[3];
    int *p3 = &a[1];

    printf("%d\n", p1 <= p2); //prints 1
    printf("%d\n", p1 >= p2); // prints 0
    printf("%d\n", p1 == p3); // prints 1

    return 0;
}
```

<br/>

## Arrays and Pointers ##

An array is a pointer.

More specifically, an array is a pointer to the first item of the array.

An array is a block of sequential data. Consider the example of a program that prints the addresses of an array elements.

```C
#include <stdio.h>
int main() {
   int x[4];
   int i;

   for(i = 0; i < 4; ++i) {
      printf("&x[%d] = %p\n", i, &x[i]);
   }

   printf("Address of array x: %p", x);

   return 0;
}
```

Output:

```
&x[0] = 1450734448
&x[1] = 1450734452
&x[2] = 1450734456
&x[3] = 1450734460
Address of array x: 1450734448
```

- There is a difference of 4 bytes between two consecutive elements of array `x`. It is because the size of `int` is 4 bytes (on our compiler).

- otice that, the address of `&x[0]` and `x` is the same. It's because the variable name `x` points to the first element of the array.

From the above example, it is clear that `&x[0]` is equivalent to `x`. And, `x[0]` is equivalent to `*x`.

Similarly,

- `&x[1]` is equivalent to `x+1` and `x[1]` is equivalent to `*(x+1)`.
- `&x[2]` is equivalent to `x+2` and `x[2]` is equivalent to `*(x+2)`.
- ...
- Basically, `&x[i]` is equivalent to `x+i` and `x[i]` is equivalent to `*(x+i)`.

```C
#include <stdio.h>
int main() {

  int i, x[6], sum = 0;

  printf("Enter 6 numbers: ");

  for(i = 0; i < 6; ++i) {
  // Equivalent to scanf("%d", &x[i]);
      scanf("%d", x+i);

  // Equivalent to sum += x[i]
      sum += *(x+i);
  }

  printf("Sum = %d", sum);

  return 0;
}
```

### Pointers and 2-D Arrays ###

A 2-D array is an array of arrays, therefore, it makes sense to say that a *2-D array is a pointer to a pointer or a pointer to an array* (since a 1-D array is a pointer).

#### Declaring a 2-D array with pointers ####

**Syntax:**

```
Type (*array_name)[SIZE]
```

- Here `array_name` can point to an array of 10 elements of type `Type`.
- You've to use surround the pointer with paranthesis.
- In this approach (or syntax if you like) we considered a 2-D array *a pointer to an array*.

Consider the following example:

```C
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

    int *ptr = NULL;
    int (*matrix)[5] = NULL;
    int row_vector[5] = {};

    // ptr points to row_vector
    ptr = row_vector;

    // matrix points to row_vector (the whole array)
    matrix = &row_vector;

    // All these pointers point to the same memory address
    printf("ptr points to: %p\n", ptr);
    printf("matrix points to: %p\n", matrix);
    printf("row_vector points to: %p\n", row_vector);
    printf("*matrix points to %p\n", *matrix);

    getchar();

    return 0;
}
```
- Notice how we initialized each variable, pointers to `NULL` and arrays to `{}`.
- `ptr` is set to point to the address of the first element of `row_vector`.
- `matrix` is set to point to the array `row_vector`.

On dereferencing a pointer expression we get a value pointed to by that pointer expression. Pointer to an array points to an array, so on dereferencing it, we should get the array, and the name of array denotes the base address. So whenever a pointer to an array is dereferenced, we get the base address of the array to which it points.

```C
// C program to illustrate sizes of
// pointer of array
#include <stdio.h>

int main()
{
	int arr[] = { 3, 5, 6, 7, 9 };
	int *p = arr;
	int (*ptr)[5] = &arr;

	printf("p = %p, ptr = %p\n", p, ptr);
	printf("*p = %d, *ptr = %p\n", *p, *ptr);

	printf("sizeof(p) = %lu, sizeof(*p) = %lu\n",
						sizeof(p), sizeof(*p));
	printf("sizeof(ptr) = %lu, sizeof(*ptr) = %lu\n",
						sizeof(ptr), sizeof(*ptr));
	return 0;
}
```

Output

```
p = 0x7ffde1ee5010, ptr = 0x7ffde1ee5010
*p = 3, *ptr = 0x7ffde1ee5010
sizeof(p) = 8, sizeof(*p) = 4
sizeof(ptr) = 8, sizeof(*ptr) = 20
```

#### How 2-D arrays are organized in memory ####

Since memory in a computer is organized linearly it is not possible to store the 2-D array in rows and columns. The concept of rows and columns is only theoretical, actually, a 2-D array is stored in row-major order i.e rows are placed next to each other. The following figure shows how the above 2-D array will be stored in memory.

![How 2-D arrays are stored in memory](https://media.geeksforgeeks.org/wp-content/uploads/Diagram2.png)

Each row can be considered as a 1-D array, so a two-dimensional array can be considered as a collection of one-dimensional arrays that are placed one after another. In other words, we can say that 2-D dimensional arrays that are placed one after another. So here arr is an array of 3 elements where each element is a 1-D array of 4 integers.


### Difference between pointer to an array and array of pointers ###

**Array of pointers** is an array of the pointer variables. It is also known as pointer arrays.

**Syntax:**

```
Type *array_name[SIZE]
```

An example of a declaration of an array of 5 pointers:

```C
int *ptr[5];
```

However, a declaration of a pointer to an array, as we mentioned before, looks like this:

```C
int (*matrix)[5] = NULL;
```


## Double Pointers ##

We already know that a pointer points to a location in memory and thus used to store the address of variables. So, when we define a pointer to pointer. The first pointer is used to store the address of the variable. And the second pointer is used to store the address of the first pointer. That is why they are also known as double pointers.

**Syntax:**

```
Type **pointer_name;
```

Consider this program example:

```C
#include <stdio.h>

// C program to demonstrate pointer to pointer
int main()
{
	int var = 789;

	// pointer for var
	int *ptr2;

	// double pointer for ptr2
	int **ptr1;

	// storing address of var in ptr2
	ptr2 = &var;

	// Storing address of ptr2 in ptr1
	ptr1 = &ptr2;

	// Displaying value of var using
	// both single and double pointers
	printf("Value of var = %d\n", var );
	printf("Value of var using single pointer = %d\n", *ptr2 );
	printf("Value of var using double pointer = %d\n", **ptr1);

return 0;
}
```

Output

```
Value of var = 789
Value of var using single pointer = 789
Value of var using double pointer = 789
```
