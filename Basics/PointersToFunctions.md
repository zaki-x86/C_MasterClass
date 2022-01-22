# Pointers to Functions #

A pointer to a function points to the address of the executable code of the function. You can use pointers to call functions and to pass functions as arguments to other functions.

You cannot perform pointer arithmetic on pointers to functions.

The type of a pointer to a function is based on both the return type and parameter types of the function.

**Syntax:**

```
Return_Type (*funcion_ptr)(Argument_Type);
```

## Initializing a Pointer to Function ##

**Syntax:**

```
Return_Type (*funcion_ptr)(Argument_Type) = function_name;
```

or

```
Return_Type (*funcion_ptr)(Argument_Type) = NULL;
function_ptr = function_name;
```

> Some prefer to add ampersand, although it is optional:
>
>```
Return_Type (*funcion_ptr)(Argument_Type) = NULL;
function_ptr = &function_name;
>```

Example:

```C
int add(int, int);

int (*add_ptr)(int, int) = &add;

// invoking
// You can do this ugly looking code
int sum = (*add_ptr)(10, 10);
// or this option which looks cleaner
int sum = add_ptr(10, 10);
```
<br/>

>Notes:
>1. Unlike normal pointers, a function pointer points to code, not data. Typically a function pointer stores the start of executable code.
>
>2. Unlike normal pointers, we do not allocate de-allocate memory using function pointers. See details here: [Memory Management]()
>
>3. A function’s name can also be used to get functions’ address. For example, in the below program, we have removed address operator ‘&’ in assignment. We have also changed function call by removing *, the program still works.
>
>4. Like normal pointers, we can have an array of function pointers.

<br/>

## Applications of Function Pointers ##

You may want a refreshment on [Generic Pointers]() before reading this section.

### The user has to decide which function has to be called at a particular point in time ###

Without the knowledge of function pointers, we would resort to using `switch-case` expression, which is not an ideal choice.

A better option would be using a function pointer.

```C
#include <stdio.h>
void add(int a, int b)
{
	printf("Addition is %d\n", a+b);
}
void subtract(int a, int b)
{
	printf("Subtraction is %d\n", a-b);
}
void multiply(int a, int b)
{
	printf("Multiplication is %d\n", a*b);
}

int main()
{
	// calc_ptr_arr is an array of function pointers
	void (*calc_ptr_arr[])(int, int) = {add, subtract, multiply};
	unsigned int ch, a = 15, b = 10;

	printf("Enter Choice: 0 for add, 1 for subtract and 2 "
			"for multiply\n");
	scanf("%d", &ch);

	if (ch > 2) return 0;

	(*fun_ptr_arr[ch])(a, b);

	return 0;
}
```

### Functions as Arguments to Other Functions ###

If you were to write a sort routine, you might want to allow the function's caller to choose the order in which the data is sorted; some programmers might need to sort the data in ascending order, others might prefer descending order while still others may want something similar to but not quite like one of those choices. One way to let your user specify what to do is to provide a flag as an argument to the function, but this is inflexible; the sort function allows only a fixed set of comparison types (e.g., ascending and descending).

A much nicer way of allowing the user to choose how to sort the data is simply to let the user pass in a function to the sort function. This function might take two pieces of data and perform a comparison on them. We'll look at the syntax for this in a bit.

#### Example: `stdlib.h`'s `qsort()` function ####

`qsort()` provides the ability to do generic sorting.

From the Linux man pages, we have the following declaration for `qsort` (from `stdlib.h`):

```C
void qsort(void *base, size_t nmemb, size_t size,
           int(*compar)(const void *, const void *));
```

Note the use of `void*` to allow `qsort` to operate on any kind of data because `void*` pointers can point to anything. Because we don't know the size of the individual elements in a `void*` array, we must give `qsort` the number of elements, `nmemb`, of the array to be sorted, `base`, in addition to the standard requirement of giving the length, size, of the input.

But what we're really interested in is the `compar` argument to `qsort`: it's a function pointer that takes two `void *`s and returns an `int`. This allows anyone to specify how to sort the elements of the array base without having to write a specialized sorting algorithm. Note, also, that `compar` returns an `int`; the function pointed to should `return -1` if the first argument is less than the second, `0` if they are equal, or `1` if the second is less than the first.

### Callback Functions ###

Another use for function pointers is setting up "**listener**" or "**callback**" functions that are invoked when a particular event happens. The function is called, and this notifies your code that something of interest has taken place.

> Strictly speaking, there is no callbacks in C, we are only implementing this concept using function pointers.

Example:

```C
void populate_array(int *array, size_t arraySize, int (*getNextValue)(void))
{
    for (size_t i=0; i<arraySize; i++)
        array[i] = getNextValue();
}

int getNextRandomValue(void)
{
    return rand();
}

int main(void)
{
    int myarray[10];
    populate_array(myarray, 10, getNextRandomValue);
    ...
}
```
