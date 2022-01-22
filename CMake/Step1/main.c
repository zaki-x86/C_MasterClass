#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "build/TutorialConfig.h"

int main(int argc, char const *argv[])
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

    return 0;
}
