# Scope #

Scope is the area under which the variable is *alive*.

- Example 1:
    - Here we say the scope of the variable ```var``` is only within the ```main()``` function.
    - The variable ```var``` is *local* to ```main()``` function only. Therefore, we call ```var``` a **local variable** to the ```main()``` function.    

```c
#include <stdio.h>

int main(int argc, char const *argv[]) {

    char var = 'N';

    getch();

  return 0;
}
```

- Example 2:
    - Here the variable ```var``` is not visible to the function ```func()``` since it is not a local variable to ```func()```.

```C

int main(int argc, char const *argv[]) {

    char var = 'N';

    getch();

  return 0;
}

void int func() {
    printf("%c\n", var); // produces an error
    return 0;
}
```

- Variable redefinition is not allowed in C. In other words, you're not allowed to declare the same variable twice.

```C
int var = 3;
int var = 4;
//this code produces an error
```

- **Global variable** is a variable that is visible to all functions.

```C
int var = 10;

int main(int argc, char const *argv[]) {
    /* var is visible here */
    return 0;
}

int int func(/* arguments */) {
    /* var is visible here as well */
    return 0;
}
```
