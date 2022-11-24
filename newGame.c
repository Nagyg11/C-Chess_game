#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"
#include "control.h"



/**pieceLoad() függvény segítségével a kezdetben szükséges összes bábut betölti a játék bábuit tartalmazó listába*/
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

    printf("Kérem adja meg a világos játékos nevét: ");
    lightName=readAString();
    printf("Kérem adja meg a sötét játékos nevét: ");
    darkName=readAString();

    //printf("%s %s", lightName, darkName);

    econio_clrscr();
}


/**Az új játékhoz szükséges függvényeket meghívja*/
void newGameStart(){
    /**Név bekérés*/
    //getPlayerName();
    newGamePices();
        econio_clrscr();
    gamePlay(true/*világos kezd ezért true*/);

    free(lightName);
    free(darkName);
}
