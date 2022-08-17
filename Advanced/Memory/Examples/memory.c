#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "inquiries.h"


int main(int argc, char const *argv[])
{
    inquire();

    getchar();
    return 0;
}
