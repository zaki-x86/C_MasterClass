#include "myio.h"

char* input(size_t size)
{
    char buffer[size];

    char* str = (char*)malloc(sizeof(char) * sizeof(buffer));

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Buffer says: %s\n", buffer);

        strncpy(str, buffer, sizeof(buffer));

        str[sizeof(buffer) - 1] = '\0';
        
        printf("str inside function says: %s\n", str);

        return str;
    }  

    return NULL;
}

int input2(char** str, size_t size)
{
    *str = (char*)malloc(sizeof(char)*size);

    if (fgets(*str, size, stdin) != NULL)
    {
        int index = strcspn(*str, "\n") ;

        (*str)[index] = '\0';
        
        printf("str inside function says: %s\n", *str);

        return 1;
    }  

    return 0;
}

int input3(char* str, size_t size)
{
    if (fgets(str, size, stdin) != NULL)
    {
        int index = strcspn(str, "\n") ;

        str[index] = '\0';
        
        printf("str inside function says: %s\n", str);

        return 1;
    }  

        return 0;
}

int test(char** input, size_t size)
{
    char buffer[size];

    *input = (char*)malloc(sizeof(char) * sizeof(buffer));

    if (fgets(buffer, size, stdin) != NULL)
    {
        buffer[strcspn(buffer, "\n")] = '\0';

        printf("Buffer says: %s\n", buffer);

        strncpy(*input, buffer, sizeof(buffer));

        printf("input inside function says: %s\n", *input);
    }  
}