# Arrays in C #

An array is a collection of items of the same type stored at contiguous memory locations and elements can be accessed randomly using indices of an array.

<!-- image description of an array here -->
![image description of an array of how an array is stored in memory](https://media.geeksforgeeks.org/wp-content/cdn-uploads/gq/2015/05/Arrays.png)

## Array Declaration ##

```C
int a[3];
// a = {garbage values}

int a[3] = { 1, 2, 3 };
// a = {1, 2, 3}

int a[3] = {};
// a = {0, 0, 0}

int a[3] = { 1 };
//a = {1, 0, 0}

int a[3] = { 0 };
// a = {0, 0, 0}

int a[] = { 10, 20, 30, 40 }
// a = {10, 20, 30, 40}

int* pa = a;
// pa = {10, 20, 30, 40}
// To be discussed later
```

## Accessing Array Elements ##

Array elements are accessed by using an integer index. Array index starts with 0 and goes till size of array minus 1.

Name of the array is also a pointer to the first element of array.

In C, it is not a compiler error to initialize an array with more elements than the specified size. For example, the below program compiles fine and shows just Warning.

```C
#include <stdio.h>

int main()
{

	// Array declaration by initializing it
	// with more elements than specified size.
	int arr[2] = { 10, 20, 30, 40, 50 };

	return 0;
}
```

There is no index out of bounds checking in C/C++, for example, the following program compiles fine but may produce unexpected output when run.  

```C
// This C program compiles fine
// as index out of bound
// is not checked in C.

#include <stdio.h>

int main()
{
	int arr[2];

	printf("%d ", arr[3]);
	printf("%d ", arr[-2]);

	return 0;
}
```

Output:

```
-449684907 4195777
```

Here is a code snippet that shows that an array elements are stored in at contiguous memory locations

```C
// C program to demonstrate that
// array elements are stored
// contiguous locations

#include <stdio.h>
int main()
{
	// an array of 10 integers.
	// If arr[0] is stored at
	// address x, then arr[1] is
	// stored at x + sizeof(int)
	// arr[2] is stored at x +
	// sizeof(int) + sizeof(int)
	// and so on.
	int arr[5], i;

	printf("Size of integer in this compiler is %lu\n",
		sizeof(int));

	for (i = 0; i < 5; i++)
		// The use of '&' before a variable name, yields
		// address of variable.
		printf("Address arr[%d] is %p\n", i, &arr[i]);

	return 0;
}

```

### Designated initialization ###

Say you have a sparse array and you wanna only fill few number of elements. Consider for example, you want your array to look like this:

```C
int A[10] = {0, 0, 0, 0, 0, 0, 99, 0, 0, 88};
```

In these scenarios, designated initializers become really handy:

```C
int A[10] = { [6] = 99, [9] = 88 };
```

This syntax instructs the compiler to store 99 in index 6 and 88 in index 9. The remaining unfilled entries will be zeros.

> Order doesn't matter as well!

**What happens when you don't specify the length of the array?**

The compiler will deduce the length of the array from the largest designator in the list.

<br/>

## Counting Array Elements ##

We use ```sizeof()```

For an array ```A``` of type ```T``` where the size of each element ```e``` of type ```T``` is ```B``` Bytes:

```
Array_length = sizeof(A) / sizeof(e)
```

Note that ```sizeof(A) = Array_length * sizeof(e)```

<br/>

## Multidimensional Arrays in C ##

In C/C++, we can define multidimensional arrays in simple words as an array of arrays. Data in multidimensional arrays are stored in tabular form (in row-major order).

**Syntax:**

```
Type array_name[size1][size2] ... [sizen]
```

**Example:**

```C
// this is equivalent to a 3 by 3 matrix
int arr[2][2];
```

![2D array](https://media.geeksforgeeks.org/wp-content/uploads/two-d.png)

### Size of multidimensional arrays ###

The total number of elements that can be stored in a multidimensional array can be calculated by multiplying the size of all the dimensions.

For example:
- The array ```int x[10][20]``` can store total (10 * 20) = 200 elements.
- Similarly array ```int x[5][10][20]``` can store total (5 * 10 * 20) = 1000 elements.

### 2-D Arrays ###

**Syntax:**

```
Type array_name[#rows][#columns];
```

#### initializing a 2-D array ####

1. The array has 3 rows and 4 columns. The elements in the braces from left to right are stored in the table also from left to right. The elements will be filled in the array in order, the first 4 elements from the left in the first row, the next 4 elements in the second row, and so on.

    ```C
    int x[3][4] = {0, 1 ,2 ,3 ,4 , 5 , 6 , 7 , 8 , 9 , 10 , 11};
    ```

2. This type of initialization makes use of nested braces. Each set of inner braces represents one row. In the above example, there is a total of three rows so there are three sets of inner braces.

    ```c
    int x[3][4] = {{0,1,2,3}, {4,5,6,7}, {8,9,10,11}};
    ```

#### Accessing array elements ####

To output all the elements of a Two-Dimensional array we can use nested for loops. We will require two for loops. One to traverse the rows and another to traverse columns.

### 3-D Arrays ###

An array of 2-D arrays.

**Syntax:**

```
Type array_name[#arrays][#rows][#columns];
```

![3-D Array](https://media.geeksforgeeks.org/wp-content/uploads/3D-array.jpg)

3-D arrays can be visualized as [tensors](https://www.youtube.com/watch?v=f5liqUk0ZTw).

#### Initialization ####

1.  
```C
int x[2][3][4] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
                 11, 12, 13, 14, 15, 16, 17, 18, 19,
                 20, 21, 22, 23};
```

2.  
```C
int x[2][3][4] =
 {
   { {0,1,2,3}, {4,5,6,7}, {8,9,10,11} },
   { {12,13,14,15}, {16,17,18,19}, {20,21,22,23} }
 };
```

#### Accessing array elements ####

Accessing elements in Three-Dimensional Arrays is also similar to that of Two-Dimensional Arrays. The difference is we have to use three loops instead of two loops for one additional dimension in Three-dimensional Arrays.

<br/>

## Case Study: Implementing Matrix Multiplication ##

Revise how matrices are multiplied:
[Matrix Multiplication](https://www.mathsisfun.com/algebra/matrix-multiplying.html)

#### Important takeaways about matrix multiplication: ####
- In order to multiply 2 matrices, #of columns of 1st matrix must be equal to the #of rows of second matrix.
- The size of the resultant matrix has the #of rows of first matrix and #of columns of the second matrix.

#### How we are expecting the program to look like ####

```
>> Enter the number of rows and columns of matrix A:
3 3

>> Enter the elements of matrix A:
1 2 3
1 2 1
3 1 2

>> Enter number of the rows and columns of matrix B:
3 3

>> Enter the elements of matrix B:
1 2 3
1 2 1
3 1 2
```

output:

```
resultant matrix:
12 9 11
6 7 7
10 10 4
```

#### We will divide the program into 3 parts: ####
1. Asking user for the size of the matrices and storing it.
2. Asking user for the elements of each matrix and storing them.
3. The multiplication algorithm and outputting the resultant matrix.

#### Asking user for the size of the matrices and storing it ####

```C
int a[MAX][MAX];
int arows, acolumns;

printf("%s\n", ">> Enter the number of rows and columns of matrix A:");
scanf("%d %d\n", &arows, &acolumns);
```

#### Asking user for the elements of each matrix and storing them ####

```C
printf("%s\n", ">> Enter the elements of matrix A:");

for (size_t i = 0; i < arows; i++)
    for (size_t j = 0; j < acolumns; j++)
        scanf("%d", &a[i][j]);
```

#### The multiplication algorithm and outputting the resultant matrix ####

```C
int product[MAX][MAX];
int sum = 0;

for (size_t i = 0; i < arows; i++)
{
    for (size_t j = 0; j < bcolumns; j++)
    {
        for (size_t k = 0; k < brows; k++)
        {
            sum += a[i][k] * b[k][j];
        }

        product[i][j] = sum;
        sum = 0;
    }
}

printf("%s\n", "Resultant matrix: ");

for (size_t i = 0; i < arows; i++)
{
    for (size_t j = 0; j < acolumns; j++)
    {
        printf("%d ", product[i][j]);
    }
    printf("\n");
}
```
