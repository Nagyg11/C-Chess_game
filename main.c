#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "menu.h"
#include "debugmalloc.h"


int main()
{
    #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif

    int f=5;
    char r[f];
    menuLoad();
    //free(getPcListBegin());

    return 0;
}
