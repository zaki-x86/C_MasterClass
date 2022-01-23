#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef USE_CUSTOMIO
#include "libs/custom/myio.h"
#endif

int main(int argc, char const *argv[])
{
    char* str = NULL; 

    #ifdef USE_CUSTOMIO
        input2(&str, 1000);
    #endif

    printf("str in main is: %s\n", str);

    return 0;
}
