#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../build/Configs.h"

void commandx(int argc, const char* argv[])
{
    for (size_t i = 0; i < argc; i++)
    {

        if (strcmp("--run-hello", argv[i]) == 0)
        {
            printf("Hello world!\n");
        }

        if (strcmp("--version", argv[i]) == 0)
        {
            printf("Version %d.%d\n", Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR);
        }
        
    }

}