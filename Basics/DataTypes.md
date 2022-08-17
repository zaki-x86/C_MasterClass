# C Data Types #

## Integer Type ##

- An integer can take 2 bytes of memory space (16-bits) or 4 bytes of memory space (32-bit) which is dependent on your machine.

- To know exactly how many bytes does a data type hold, you can use the ```sizeof()``` operator:

```C
#include "stdio.h"

int int main(int argc, char const *argv[]) {
    printf("%d\n", sizeof(int));
    return 0;
}
```

> ```sizeof()``` is a unary operator and is not a function!

### MAX and MIN value that an int type can hold ###

- For a 32-bit machine in which an integer hold 4 bytes, we can calculate the range values that an ```unsigned int``` type can hold. To calculate the max for an unsigned range, we use this formula: (2^n - 1), therefore, MAX = (2^32 - 1). To calculate the max for a signed range, we use the 2's complement formula: -(2^n - 1) to +(2^n-1 - 1)
> ```unsigned int``` is an integer type that can only hold positive values.

### Using short and long ###

- Note that

```
sizeof(short int) <= sizeof(int) <= sizeof(long int)
```

```C
#include "stdio.h"

int int main(int argc, char const *argv[]) {
    printf("Size of short integer: %d\n", sizeof(short int));
    printf("Size of long  integer: %d\n", sizeof(long int));

    return 0;
}
```

- We can include a c library called `limits.h` which includes 2 symbolic constants that define the limits of ```int``` type as well as any data type in the C language:

```C
#include <stdio.h>
#include <limits.h>
#include <conio.h>

int main(int argc, char const *argv[]) {

    // notice that we hand to change the identifier to %u
    printf("Range of unsigned integers: %u to %u\n", 0, UINT_MAX);

    getch();

  return 0;
}
```

- The ```limits.h``` library also include:

```C
short int v1 = SHRT_MIN;            // %d
short int v2 = SHRT_MAX;            // %d
unsigned short int v3 = USHRT_MAX;  // %u
long int v4 = LONG_MIN;             // %ld
long int v5 = LONG_MAX;             // %ld
unsigned long int v6 = ULONG_MAX;   // %ud
```

### What happens when you exceed the allowed range ###

Check [Exceeding The Valid Range of Data Types](https://youtu.be/nwfoxcXgs8o?list=PLBlnK6fEyqRggZZgYpPMUxdY1CYkZtARR)
<!-- watch: https://youtu.be/nwfoxcXgs8o?list=PLBlnK6fEyqRggZZgYpPMUxdY1CYkZtARR -->

<br/>

## Character Type ##

- Defining and declaring a Character type:

```C
char something = 'N';
char something2 = 65;
printf("%c\n", something2); // prints A
printf("%d\n", something2); // prints 65
```

- Size of ```char``` type is only 1 byte.

- Ranges of ```char``` type:
    - unsigned: 0 to 255
    - signed: -128 to 127

<br />

## Float and Double Types ##

- The size of these types depends on your machine but here is an example:
    - float -> 4 bytes
    - double -> 8 bytes
    - long double -> 12 bytes  

### Floating point representation vs Fixed point representation ###

<!-- Source: https://youtu.be/vNeOx1rQ25E?list=PLBlnK6fEyqRggZZgYpPMUxdY1CYkZtARR -->
