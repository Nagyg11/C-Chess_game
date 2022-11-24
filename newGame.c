#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"
#include "control.h"



/**pieceLoad() f�ggv�ny seg�ts�g�vel a kezdetben sz�ks�ges �sszes b�but bet�lti a j�t�k b�buit tartalmaz� list�ba*/
void newGamePices(){
    char pieces[6]={'r','h','b','k','q','p'};
    int x=1;
    for(int i=0; i!=16; i++){
        pieceLoad(pieces[5], (i%2==0)? true : false, x, (i%2==0)? 7 : 2);
        if(i%2==1){
            x++;
        }
    }
    for(int i=0; i!=5;i++){
        pieceLoad(pieces[i],true,i+1,8);
        pieceLoad(pieces[i],false,i+1,1);
        if(pieces[i]!='k' && pieces[i]!='q'){
        pieceLoad(pieces[i],true,8-i,8);
        pieceLoad(pieces[i],false,8-i,1);
        }
    }

}


void getPlayerName(){
    econio_clrscr();

    printf("K�rem adja meg a vil�gos j�t�kos nev�t: ");
    lightName=readAString();
    printf("K�rem adja meg a s�t�t j�t�kos nev�t: ");
    darkName=readAString();

    //printf("%s %s", lightName, darkName);

    econio_clrscr();
}


/**Az �j j�t�khoz sz�ks�ges f�ggv�nyeket megh�vja*/
void newGameStart(){
    /**N�v bek�r�s*/
    //getPlayerName();
    newGamePices();
        econio_clrscr();
    gamePlay(true/*vil�gos kezd ez�rt true*/);

    free(lightName);
    free(darkName);
}
