# How to deal with Seg Faults #

Seg faults are quite annoying, because C doesn't have a built-in mechanism that will guide you how and where do they happen in your code.

Therefore, we need an external tool that can help us detect issues. There are in fact, 2 of them: gdb and valgrind. In this article we will discuss how to debug with valgrind, since it is very fast, efficient and easy to use.

Valgrind is quite handy to detect memory leaks, code that causes seg faults, errors, .. and much more.

First, install valgrind:

```terminal
user@xuser:/$ sudo apt install valgrind
```

To run valgrind, pass the executable as an argument (along with any parameters to the program).

```terminal
user@xuser:/$ valgrind ./program

=168661== Memcheck, a memory error detector
==168661== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==168661== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==168661== Command: ./Tutorial
==168661== 
==168661== Conditional jump or move depends on uninitialised value(s)
==168661==    at 0x48D7C02: __vfprintf_internal (vfprintf-internal.c:1687)
==168661==    by 0x48C1EBE: printf (printf.c:33)
==168661==    by 0x1092E4: main (in /home/Tutorial)
==168661== 
==168661== HEAP SUMMARY:
==168661==     in use at exit: 0 bytes in 0 blocks
==168661==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==168661== 
==168661== All heap blocks were freed -- no leaks are possible
==168661== 
==168661== Use --track-origins=yes to see where uninitialised values come from
==168661== For lists of detected and suppressed errors, rerun with: -s
==168661== ERROR SUMMARY: 1 errors from 1 contexts (suppressed: 0 from 0)
```

Valgrind will produce an output on the console that gives a `heap summary` which tells you whether there are allocated memory that were not freed. It shows you an error summary as well, some of these errors are non-fatal, meaning you won't detect them normally as compiler won't produce any errors when you run your program.

## How do I use valgrind to find memory leaks? ##

Source: [stack overflow](https://stackoverflow.com/questions/5134891/how-do-i-use-valgrind-to-find-memory-leaks)

You can pass some flags with valgrind to produce much details and provide more in depth information about possible errors or memory leaks:

```terminal
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./executable exampleParam1
```

The flags are in short:

- `--leak-check=full`: "each individual leak will be shown in detail"

- `--show-leak-kinds=all`: Show all of "definite, indirect, possible, reachable" leak kinds in the "full" report.

- `--track-origins=yes`: Favor useful output over speed. This tracks the origins of uninitialized values, which could be very useful for memory errors. Consider turning off if Valgrind is unacceptably slow.

- `--verbose`: Can tell you about unusual behavior of your program. Repeat for more verbosity.

- `--log-file`: Write to a file. Useful when output exceeds terminal space.

Finally, you would like to see a Valgrind report that looks like this:

```terminal
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: 636 allocs, 636 frees, 25,393 bytes allocated

All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

As you see this command is pretty long, so you can do this instead:

- create a .bashrc file: `.bashrc`.

- Write an alias to the command in it:

    ```bash
    echo "Init bashrc "
    alias check='valgrind --leak-check=full \
            --show-leak-kinds=all \
            --track-origins=yes \
            --verbose \
            --log-file=valgrind-out.txt'
    ```

- Go back to terminal and initialize the .bashrc by using this command:

    ```terminal
    user@userx:/$ source .bashrc
    ```

- Now run the alias along with the excutable:

    ```terminal
    user@userx:/$ check ./executable
    ```

You can combine gdb with valgrind to help valgrind specify the line numbers of where issues happen.

Add these flags when compiling:

```terminal
user@userx:/$ gcc -o executable -std=c11 -Wall -ggdb3 main.c
```

<br/>

## General Techniques for Debugging Memory Leaks & Errors ##

- Make use of [www.cplusplus.com](http://www.cplusplus.com/) It has great documentation on C/C++ functions.

- **General advice for memory leaks**:
    Make sure your dynamically allocated memory does in fact get freed.
    Don't allocate memory and forget to assign the pointer.
    Don't overwrite a pointer with a new one unless the old memory is freed.

- **General advice for memory errors**:
    Access and write to addresses and indices you're sure belong to you. Memory errors are different from leaks; they're often just `IndexOutOfBoundsException` type problems.
    *Don't access or write to memory after freeing it.*

- Sometimes your leaks/errors can be linked to one another, much like an IDE discovering that you haven't typed a closing bracket yet. Resolving one issue can resolve others, so look for one that looks a good culprit and apply some of these ideas:

  - List out the functions in your code that depend on/are dependent on the "offending" code that has the memory error. Follow the program's execution (maybe even in gdb perhaps), and look for precondition/postcondition errors. The idea is to trace your program's execution while focusing on the lifetime of allocated memory.
  - Try commenting out the "offending" block of code (within reason, so your code still compiles). If the Valgrind error goes away, you've found where it is.

- If all else fails, try looking it up. Valgrind has [documentation](http://valgrind.org/docs/manual/manual.html) too!


### Examples of Memory Errors ##

Your task is to create an input function that accepts input from user and store it in a string pointer, so we are expecting this behavior:

```C
// inside main()
char *ip;
    
input(ip, 1000); // user will input on keyboard

printf("input inside main says %s\n", ip); // display the stored input
```

Here is the function that we created: 

```C
int input(char* input, size_t size)
{
    char buffer[size];

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Buffer says: %s\n", buffer);

        input = buffer;

        printf("input inside function says: %s\n", input);

        return 0;
    }  

    return -1;
}
```

When we run this code:

```terminal
user@userx:/$ gcc main.c -o Tutorial
user@userx:/$ ./Tutorial
Hi

Buffer says: Hi
input inside function says: Hi
input inside main says (null)
```

`input` in `main` is of course `NULL` since the local variable `buffer` is destroyed after the function `input()` hands off control to `main()`, so we attempt to fix this by doing this:

```C
int input(char* input, size_t size)
{
    char buffer[size];

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Buffer says: %s\n", buffer);

        strncpy(input, buffer, sizeof(buffer))

        printf("input inside function says: %s\n", input);

        return 0;
    }  

    return -1;
}
```

Let's compile and run to see what happens:

```terminal
user@userx:/$ gcc main.c -o Tutorial
user@userx:/$ ./Tutorial
Hi

Buffer says: Hi
Segmentation fault (core dumped)
```

Now it is even worse, our program crashed!

Let's launch valgrind to see what happened:

```terminal
user@userx:/$ check ./Tutorial  #using .bashrc
Hi

Buffer says: Hi
Segmentation fault (core dumped)
```

Let's open the log file that valgrind generated for us:

Upon examining the summary at the end of the file, we find this:

```terminal
HEAP SUMMARY:
==173631==     in use at exit: 0 bytes in 0 blocks
==173631==   total heap usage: 2 allocs, 2 frees, 2,048 bytes allocated
==173631== 
==173631== All heap blocks were freed -- no leaks are possible
==173631== 
==173631== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
==173631== 
==173631== 1 errors in context 1 of 2:
==173631== Invalid write of size 1
==173631==    at 0x483F260: strncpy (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==173631==    by 0x10933D: input (in /home/Tutorial)
==173631==    by 0x1091EC: main (in /home/Tutorial)
==173631==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
==173631== 
==173631== 
==173631== 1 errors in context 2 of 2:
==173631== Use of uninitialised value of size 8
==173631==    at 0x483F260: strncpy (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_memcheck-amd64-linux.so)
==173631==    by 0x10933D: input (in /home/Tutorial)
==173631==    by 0x1091EC: main (in /home/Tutorial)
==173631==  Uninitialised value was created by a stack allocation
==173631==    at 0x1091C9: main (in /home/Tutorial)
==173631== 
==173631== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
```

First error found is here:

```terminal
==173631== Invalid write of size 1
==173631==    by 0x10933D: input (in /home/Tutorial)
==173631==    by 0x1091EC: main (in /home/Tutorial)
==173631==  Address 0x0 is not stack'd, malloc'd or (recently) free'd
```

What does that mean?

Note that `input` variable is a `NULL` when it is declared, it doesn't point to anything, and what we are doing is that we are copying data to this pointer that points to nothing!

We can fix this by allocating memory, which in turn, make `input` points to some legal location to store the data that we are copying.

Fixing our `input()`:

```C
int input(char* input, size_t size)
{
    char buffer[size];

    input = (char*)malloc(sizeof(char) * sizeof(buffer));

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Buffer says: %s\n", buffer);

        strncpy(input, buffer, sizeof(buffer));

        printf("input inside function says: %s\n", input);
    }  
}
```

After we compile and run, we get no errors, our program compiles normally, but we are back to square one:

```terminal
user@userx:/$ gcc main.c -o Tutorial
Hi

Buffer says: Hi
input inside function says: Hi
input inside main says (null)
```

`input` variable in `main` reads `NULL`! why?

We have an issue with our references.
The problem is that the line:

```C
input = (char*)malloc(sizeof(char) * sizeof(buffer));
```

will only modify the pointer variable `input` in the function `input`, which contains a copy of the value of the variable `ip` in the function `main`. It will not set the value of the original variable `ip` in the function `main`.

Therefore, we need a double pointer!

```C
int input(char** input, size_t size)
{
    char buffer[size];

    *input = (char*)malloc(sizeof(char) * sizeof(buffer));

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Buffer says: %s\n", buffer);

        strncpy(*input, buffer, sizeof(buffer));

        printf("input inside function says: %s\n", *input);
    }  
}
```

We need also to modify our function call in `main`:

```C
char* str; 
input(&str, 1000);
printf("str in main is: %s\n", str);
```

When we compile and run:

```terminal
user@xuser:/$ check ./Tutorial
Hi
Buffer says: Hi
input inside function says: Hi
str in main is: Hi
```

We solved the problem, now we can read input correctly.

But wait, there is still more.

This implementaion will force users of our function to clean up after themselves and call `free()` after they are done to avoid memory leaks.

Therefore, when someone uses our library, they have to call `free`:

```C
char* str; 
input(&str, 1000);
printf("str in main is: %s\n", str);

// ... 
free(str);
return 0;
```

Which is not really good from my point of view, so we need to improve this.

Also this is not the only bad thing with our code so far, our code is pretty horrible at this point even though, it meets our task requirement.

Consider the 1000 byte `buffer` that we are allocating in the stack, is really useless, since we can perform all our operations on the pointer directly!

So let's ditch the buffer first:

```C
int input(char** str, size_t size)
{
    *str = (char*)malloc(sizeof(char)*size);

    if (fgets(*str, size, stdin) != NULL)
    {

        int index = strcspn(*str, "\n") ;

        (*str)[index] = '\0'; // notice we had to add *str between paranthesis
        
        printf("str inside function says: %s\n", *str);

        return 1;
    }  

    return 0;
}
```

When we compile and run code, it still works great, we also saved some memory in the stack.

Now, we want our function to be `malloc` free since we don't want to bug the callee of the functions with having to call `free` because of our implementaion, therefore, we will be forcing them that they create their own buffer according to their needs while keeping our function as generic as possible.

Here is our final `input` function:

```C
int input(char* str, size_t size)
{
    if (fgets(str, size, stdin) != NULL)
    {
        int index = strcspn(str, "\n") ;

        str[index] = '\0';
        
        printf("str inside function says: %s\n", str);

        return 1;
    }  

        return 0;
}
```

When someone uses our function:

```C
char ip[1000];

input3(ip, 1000);
printf("ip inside main says %s\n", ip)
```

Now the user will create their own buffer acoording to their needs. 

You may ask why did we have to this in `main`: `char ip[1000]` instead of this `char* ip`?

If we did that, we will be back to the same problem of referencing a copy of the data instead of the original data that we had before **scroll above!**.
