# Error Handling ##

As such, C programming does not provide direct support for error handling but being a system programming language, it provides you access at lower level in the form of return values.

Most of the C or even Unix function calls return `-1` or `NULL` in case of any error and set an error code `errno`.

It is set as a global variable and indicates an error occurred during any function call. You can find various error codes defined in `<error.h>` header file.

So a C programmer can check the returned values and can take appropriate action depending on the return value. It is a good practice, to set `errno` to 0 at the time of initializing a program. A value of 0 indicates that there is no error in the program.

## `errno`, `perror()`. and `strerror()` ##

The C programming language provides `perror()` and `strerror()` functions which can be used to display the text message associated with `errno`.

- The `perror()` function displays the string you pass to it, followed by a colon, a space, and then the textual representation of the current errno value.

- The `strerror()` function, which returns a pointer to the textual representation of the current errno value.

Example: Opening a file that doesn't exit

```C
#include <stdio.h>
#include <errno.h>
#include <string.h>

extern int errno ;

int main () {

   FILE * pf;
   int errnum;
   pf = fopen ("unexist.txt", "rb");

   if (pf == NULL) {
   
      errnum = errno;
      fprintf(stderr, "Value of errno: %d\n", errno);
      perror("Error printed by perror");
      fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
   } else {
   
      fclose (pf);
   }
   
   return 0;
}
```

Output:

```terminal
Value of errno: 2
Error printed by perror: No such file or directory
Error opening file: No such file or directory
```
