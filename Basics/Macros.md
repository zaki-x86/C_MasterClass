# Macros in C #

- A **macro** is a piece of code in a program that is replaced by the value of the macro. Macro is defined by #define directive. Whenever a macro name is encountered by the compiler, it replaces the name with the definition of the macro. Macro definitions need not be terminated by semi-colon(;).

    - Examples:
    1.  

    ```C
    // C program to illustrate macros
    #include <stdio.h>

    // Macro definition
    #define LIMIT 5

    // Driver Code
    int main()
    {
    	// Print the value of macro defined
    	printf("The value of LIMIT"
    		" is %d",
    		LIMIT);

    	return 0;
    }
    ```

    2.

    ```C
    // C program to illustrate macros
    #include <stdio.h>

    // Macro definition
    #define AREA(l, b) (l * b)

    // Driver Code
    int main()
    {
    	// Given lengths l1 and l2
    	int l1 = 10, l2 = 5, area;

    	// Find the area using macros
    	area = AREA(l1, l2);

    	// Print the area
    	printf("Area of rectangle"
    		" is: %d",
    		area);

    	return 0;
    }
    ```

- **Chain Macros**: Macros inside macros are termed as chain macros. In chain macros first of all parent macro is expand then child macro is expanded.
Below is the illustration of a Chain Macro:

```C
// C program to illustrate macros
#include <stdio.h>

// Macro definition
#define INSTAGRAM FOLLOWERS
#define FOLLOWERS 138

// Driver Code
int main()
{
	// Print the message
	printf("Geeks for Geeks have %dK"
		" followers on Instagram",
		INSTAGRAM);

	return 0;
}
```

- **Multi-line Macros**: An object-like macro could have a multi-line. So to create a multi-line macro you have to use backslash-newline.
Below is the illustration of multiline macros:

```C
// C program to illustrate macros
#include <stdio.h>

// Multi-line Macro definition
#define ELE 1, \
			2, \
			3

// Driver Code
int main()
{

	// Array arr[] with elements
	// defined in macros
	int arr[] = { ELE };

	// Print elements
	printf("Elements of Array are:\n");

	for (int i = 0; i < 3; i++) {
		printf("%d ", arr[i]);
	}
	return 0;
}
```

- **Function-like Macro**: These macros are the same as a function call. It replaces the entire code instead of a function name. Pair of parentheses immediately after the macro name is necessary. *If we put a space between the macro name and the parentheses in the macro definition then the macro will not work*.
A function-like macro is only lengthened if anD only if its name appears with a pair of parentheses after it. If we don’t do this, the function pointer will get the address of the real function and lead to a syntax error.

```C
// C program to illustrate macros
#include <stdio.h>

// Function-like Macro definition
#define min(a, b) (((a) < (b)) ? (a) : (b))

// Driver Code
int main()
{

	// Given two number a and b
	int a = 18;
	int b = 76;

	printf("Minimum value between"
		" %d and %d is %d\n",
		a, b, min(a, b));

	return 0;
}
```

- ```<stdio.h>``` has a built-in date and time macros:

```C
#include <stdio.h>

int main(int argc, char const *argv[]) {
    printf("Date: %s\n", __DATE__);
    printf("Time: %s\n", __TIME__);
    return 0;
}
```
