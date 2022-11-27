#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "fileManage.h"
#include "econio.h"
#include "debugmalloc.h"
#include "tableDisplay.h"
#include "control.h"
#include "pieces.h"

void loadGameStart(){
    econio_clrscr();
    char *savedGame;

    DefDatas data;
    data.pcListBegin=NULL;
    data.stepListBegin=NULL;
    data.names=NULL;

    do{
    printf("Kérem adja meg annak a mentett játéknak a nevét, amelyet folytatni szeretné: ");
    savedGame=readAString();
    char *trash=savedGame;
    savedGame=join3String("./savedGames/", savedGame, ".txt");
    free(trash);
    readStepsFile(savedGame, &data);
    data.names=readNameFile(savedGame);
    //if(){

    //}
    }
    while(!(data.stepListBegin!=NULL || data.names!=NULL));

    data.gameEnd=false;

    newGamePices(&data);

    StepLogList *helpStep=data.stepListBegin;

    while(helpStep!=NULL){
        changePieceXY(findPiece(helpStep->fromX,helpStep->fromY,&data), helpStep->toX, helpStep->toY);
        //printf("%d%d,%d%d\n", helpPiece->posX, helpPiece->posY, helpStep->toX, helpStep->toY);
        helpStep=helpStep->next;
    }

    gamePlay(&data);

    free(savedGame);
    free(data.names);


}
