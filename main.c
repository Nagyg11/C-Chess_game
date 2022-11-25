#include <stdio.h>
#ifdef _WIN32
    #include <windows.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "fileManage.h"

#include "menu.h"


int main()
{
    #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif

    menuLoad();
    //free(getPcListBegin());

    return 0;
}
