#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../libs/add/add.h"
#include "../libs/subtract/subtract.h"
#include "../build/Configs.h"

void commandx(int argc, const char* argv[]);

int main(int argc, char const *argv[])
{
    if (argc > 1)
    {
        commandx(argc, argv);
        return 0;
    }
    

    #ifdef USE_ARITH_KIT
    
        int diff = 0, sum = 0, x = 5, y = 5;
        
        sum = add(x, y);
        diff = subtract(x, y);
        printf("sum = %d + %d = %d\n", x, y, sum);
        printf("difference = %d - %d = %d\n", x, y, diff);
    
    #else

        printf("Looks like you disabled the use of our arithmetic library\n");
        printf("go to your native build system and run cmake /path/to/source -DUSE_ARITH_KIT=on to enable it\n");

    #endif
    
    return 0;
}
