# Strings #

Strings are defined as an array of characters. The difference between a character array and a string is the string is terminated with a special character ‘\0’.

Declaring a string is as simple as declaring a one-dimensional array. Below is the basic syntax for declaring a string.

```C
char str_name[SIZE];
```

In the above syntax str_name is any name given to the string variable and size is used to define the length of the string, i.e the number of characters strings will store. Please keep in mind that there is an extra terminating character which is the Null character (‘\0’) used to indicate the termination of string which differs strings from normal character arrays.

## Initializing a String ##

A string can be initialized in different ways. We will explain this with the help of an example. Below is an example to declare a string with name as str and initialize it with “Hello”.

```C
1. char str[] = "Hello";

2. char str[50] = "Hello";

3. char str[] = {'H','e','l','l','o','\0'};

4. char str[14] = {'H','e','l','l','o','\0'};

```

Let us now look at a sample program to get a clear understanding of declaring and initializing a string in C and also how to print a string.

```C
// C program to illustrate strings

#include <stdio.h>

int main()
{
    // declare and initialize string
    char str[] = "Hello";

    // print string
    printf("%s",str);  //prints hello

    return 0;
    }
```

We can see in the above program that strings can be printed using normal printf statements just like we print any other variable. Unlike arrays, we do not need to print a string, character by character. The C language does not provide an inbuilt data type for strings but it has an access specifier “%s” which can be used to directly print and read strings.

## Passing Strings to Functions ##

As strings are character arrays, so we can pass strings to function in a same way we pass an array to a function. Below is a sample program to do this:

```C
// C program to illustrate how to
// pass string to functions
#include <stdio.h>

void printStr(char str[])
{
    printf("String is : %s",str);
}

int main()
{
    // declare and initialize string
    char str[] = "Hello";

    // print string by passing string
    // to a different function
    printStr(str);

    return 0;
}
```

## String Literals ##

Also known as **string constant** is a sequence of characters enclosed within double quotes.

Examples:

```C
printf("%s\n", 
"This is a string literal"
);

printf("%s\n", 
"This is a multiline \
string literal \
here"
);

printf("%s\n", 
"This is also"
"a valid"
"multiline string literal"
);
```

Note that `printf` and `scanf` always accept string literals as inputs.

String literals are stored in memory the same way as normal strings except the memory chunk is read-only. Therefore, you can't any character of a string literal.

When we pass a string literal to a function, we don't actually pass the entire string, we only pass the address of the first character of the string.

If you plan on modifying a string then only declare it using array of size `SIZE` as a character array.
Even though you may declare a string using `char *str_name;`, even though `char *` indicated mutability, some compilers will place the string in a read-only space in memory since it points to a string literal.

## Reading a string input from user ##

`Scanf()`:

- can input any basic and derived datatype.
- Skips the string input after encountering a blank space.

`gets()`:

- Can only input a string value.
- Accepts string input including blank space and whatever following it.

### Never use `gets()` function when reading user input ###

The first internet worm [the Morris Internet Worm](https://en.wikipedia.org/wiki/Morris_worm) escaped about 30 years ago (1988-11-02), and it used gets() and a buffer overflow as one of its methods of propagating from system to system. The basic problem is that the function doesn't know how big the buffer is, so it continues reading until it finds a newline or encounters `EOF`, and may overflow the bounds of the buffer it was given.

The C11 standard ISO/IEC 9899:2011 eliminated gets() as a standard function, which is A Good Thing™ (it was formally marked as 'obsolescent' and 'deprecated' in ISO/IEC 9899:1999/Cor.3:2007.

### Alternative to `gets()`: `fgets()` ###

Source: [Stackoverflow - Why is the gets function so dangerous that it should not be used?](https://stackoverflow.com/questions/1694036/why-is-the-gets-function-so-dangerous-that-it-should-not-be-used)

Instead of using `gets`, you want to use `fgets`, which has the signature:

```C
char* fgets(char *string, int length, FILE * stream);
```

>`fgets`, if it reads an entire line, will leave the '\n' in the string; you'll have to deal with that.

**Syntax:**

```C
char buffer[BUFSIZ];

while (fgets(buffer, sizeof(buffer), stdin) != 0)
{
    ...process line of data...
}
```

Since fgets() stores the newline character `\n`, you might need to use a wrapper around `fgets()` that deletes the newline:

```C
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        size_t len = strlen(buffer);
        if (len > 0 && buffer[len-1] == '\n')
            buffer[len-1] = '\0';
        return buffer;
    }
    return 0;
}
```

or better:

```C
char *fgets_wrapper(char *buffer, size_t buflen, FILE *fp)
{
    if (fgets(buffer, buflen, fp) != 0)
    {
        buffer[strcspn(buffer, "\n")] = '\0';
        return buffer;
    }
    return 0;
}
```

## Arrays of Strings ##

To store an array strings, we use an array of pointers.

Syntax:

```C
char* str_arr[SIZE] = {"string1", "string2", "string3"};
```