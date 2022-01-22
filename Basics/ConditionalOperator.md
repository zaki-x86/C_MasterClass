# Conditional Operator in C #

The only ternary operator in C!

**Syntax**:

```
variable = Expression1 ? Expression2 : Expression3;
```

It is equivalent to:

```C
if (//Expression1)
    //variable = Expression2;
else
    //variable = Expression3;
```

**Example**:

```C
// C program to find largest among two
// numbers using ternary operator

#include <stdio.h>

int main()
{
	int m = 5, n = 4;

	(m > n) ? printf("m is greater than n that is %d > %d",
					m, n)
			: printf("n is greater than m that is %d > %d",
					n, m);

	return 0;
}
```

Output:

```
m is greater than n that is 5 > 4
```
