#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "pieces.h"
#include "control.h"
#include "econio.h"
#include "debugmalloc.h"




/**pieceLoad() f�ggv�ny seg�ts�g�vel a kezdetben sz�ks�ges �sszes b�but bet�lti a j�t�k b�buit tartalmaz� list�ba*/
void newGamePices(DefDatas *data){
    char pieces[6]={'r','h','b','k','q','p'};
    int x=1;
    for(int i=0; i!=16; i++){
        pieceLoad(pieces[5], (i%2==0)? true : false, x, (i%2==0)? 7 : 2, data);
        if(i%2==1){
            x++;
        }
    }
    for(int i=0; i!=5;i++){
        pieceLoad(pieces[i],true,i+1,8,data);
        pieceLoad(pieces[i],false,i+1,1,data);
        if(pieces[i]!='k' && pieces[i]!='q'){
        pieceLoad(pieces[i],true,8-i,8,data);
        pieceLoad(pieces[i],false,8-i,1,data);
        }
    }

}


char *getPlayerName(){
    econio_clrscr();

    printf("K�rem adja meg a vil�gos j�t�kos nev�t: ");
    char *lightName=readAString();
    printf("K�rem adja meg a s�t�t j�t�kos nev�t: ");
    char *darkName=readAString();

    char *names=(char*) malloc((strlen(lightName)+strlen(darkName)+2)*sizeof(char));
    strcpy(names,lightName);
    strcat(names, ";");
    strcat(names, darkName);
    free(lightName);
    free(darkName);
    return names;

    econio_clrscr();
}


/**Az �j j�t�khoz sz�ks�ges f�ggv�nyeket megh�vja*/
void newGameStart(){
    DefDatas data;
    data.pcListBegin=NULL;
    data.stepListBegin=NULL;
    data.gameEnd=false;
    data.names=getPlayerName();

    newGamePices(&data);
        econio_clrscr();
    gamePlay(&data);

    free(data.names);
}
