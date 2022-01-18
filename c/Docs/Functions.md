# Functions #

A function is a set of statements that takes some input and do some computations on it and produces an output.

**Syntax**:

```
Output_Type function_name(arguments/inputs)
```

There are 2 important reasons why we use functions:
1. Reusability
2. Abstraction

#### Example: Area of a rectangle ####

```C
#include <stdio.h>

int area(int length, int breadth) {
    int area;
    area = length * breadth;

    return area;
}

int main(int argc, char const *argv[]) {
    int a = 10;
    int b = 5;
    int area = area(a, b);
    printf("%d\n", area);

    return 0;
}
```

<br/>

## Function Prototypes ##

Declaring the properties of a function to the complier.

**Example**:

```C
int foo(int, char);
```

Here you introduced the compiler the properties of a the function that you're going to implement later:
1. Name of the function
2. Return type
3. Number of arguments
4. Type of each argument

> Notice that it is not mandatory to insert the function parameters in the Prototype, as we can only use the types of the arguments instead.

> It is not always necessary to declare the function before using it, but it is preferred.

> You can't use a function before defining it as it will generate an error, unless you define a Prototype to the function and then implemented it later, it won't produce an error.

<br/>

## Calling a function by value and calling by reference ##

Before we go further let's agree on some terminology:
- **Actual Parameters**: The parameters passed to a function.

    ```C
    //x1, x2 are actual parameters
    add(x1, x2)
    ```

- **Formal Parameters**: The parameters received by a function.

    ```C
    //m, n are formal parameters
    int add(int m, int n)
    {
        return (a + b);
    }
    ```

### Call by Value ###

Values of the actual parameters will be copied to the formal parameters and each of them store the values in different locations in memory.

The ```area()``` function is an example of call by value function.

### Call by Reference ###

Both values of the actual and formal parameters are stored in the same memory location. Therefore, any changes made to the formal parameters will reflect on the actual parameters.

We don't pass values to function calls, instead, we pass **addresses**.

```C
int x1 = 10;
int x2 = 20;
int area = 0;

calculate_area(&x1, &x2, &area)
```

- Here the function ```calculate_area()``` accept the addresses of 3 variables as actual parameters.

- Notice how we define the formal parameters:

```C
void calculate_area(int* x, int* y, int* area)
{
    *area = *x * *y;
}
```

We use special variables called **[pointers]()**.

<br/>

## Static Functions in C ##

In C, functions are global by default. This means that if we want to access the function from the file where it is declared, we can do it easily.

If we want to restrict the access to the function, then we can make our function static by simply putting a keyword ```static``` in front of the function.
> For more information about the ```static``` keyword, refer to [```static``` Keyword in C]()
