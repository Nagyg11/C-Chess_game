#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
//#include "defaultDatas"
#include "newGame.h"
#include "fileManage.h"
#include "econio.h"
#include "debugmalloc.h"
#include "control.h"

void loadGameStart(){
    econio_clrscr();
    DefDatas data;
    data.pcListBegin=NULL;

    //do{
    printf("Kérem adja meg annak a mentett játéknak a nevét, amelyet folytatni szeretné: ");
    char *savedGame=readAString();
    data.stepListBegin=readStepsFile(savedGame);
    data.names=readNameFile(savedGame);
    //}
    //while(data.stepListBegin==NULL && data.names=' ');
    data.gameEnd=false;


}
