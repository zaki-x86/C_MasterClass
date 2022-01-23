#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// prompt user to enter something 
// input is always a string 
// accepts a pointer to void as a parameter
// also accepts buffer size
// functions returns 0 on success, -1 on failure

char* input(size_t);
int input2(char**, size_t);
int input3(char*, size_t);
int test(char**, size_t);