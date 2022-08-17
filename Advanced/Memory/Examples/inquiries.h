#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

void inquire()
{
    struct rlimit limit;

    getrlimit (RLIMIT_STACK, &limit);
    printf ("\nStack Limit = %ld MB and %lud MB max\n", limit.rlim_cur/1000, limit.rlim_max/1000);
    
    getrlimit (RLIMIT_AS, &limit);
    printf("Process virtual memory = %lud MB and %lud MB max\n", limit.rlim_cur/1000, limit.rlim_max/1000);
}