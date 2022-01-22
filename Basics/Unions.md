# Unions #

Like Structures, union is a user defined data type. In union, all members share the same memory location.

![Unions](https://www.geeksforgeeks.org/wp-content/uploads/Union-in-C.png)
Source: [Geeks for Geeks | Unions](https://www.geeksforgeeks.org/union-c/)

For example in the following C program, both x and y share the same location. If we change x, we can see the changes being reflected in y:

```C
#include <stdio.h>

// Declaration of union is same as structures
union test {
 int x, y;
};

int main()
{
    // A union variable t
    union test t;    
    t.x = 2; // t.y also gets value 2
    printf("After making x = 2:\n x = %d, y = %d\n\n",
     t.x, t.y); 
    t.y = 10; // t.x is also updated to 10
    printf("After making y = 10:\n x = %d, y = %d\n\n",
     t.x, t.y);
    return 0;
}
```

Size of a union is taken according the size of largest member in union.

```C
#include <stdio.h>

union test1 {
    int x;
    int y;
} Test1;

union test2 {
    int x;
    char y;
} Test2;

union test3 {
    int arr[10];
    char y;
} Test3;

int main()
{
    printf("sizeof(test1) = %lu, sizeof(test2) = %lu, "
    "sizeof(test3) = %lu",
    sizeof(Test1),
    sizeof(Test2), sizeof(Test3));
    return 0;
}
```

Output:

```terminal
sizeof(test1) = 4, sizeof(test2) = 4, sizeof(test3) = 40
```
