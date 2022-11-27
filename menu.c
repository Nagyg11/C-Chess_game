#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "loadGame.h"
#include "tableDisplay.h"
#include "econio.h"
#include "debugmalloc.h"
#include "leaderBoard.h"

/**Bet�lti a men�t �s 1-4-ig lehet v�lasztani a men�pontokb�l
A men�h�z be kell �rni a v�lasztani kiv�nt men�pont sz�m�t majd entert kell nyomni.
*/
void menuLoad(){
    econio_set_title("Sakk - Men�");

    econio_clrscr();
    int menuChoose=0;
    do{
    econio_gotoxy(0,0);
    printf("K�rem v�lasszon men�pontot! \n");
    printf("[1] �j j�tek kezd�s\n");
    printf("[2] J�tek �ll�s bet�lt�s f�jlb�l\n");
    printf("[3] Dics�s�g lista\n");
    printf("[4] Kil�p�s\n");
    fflush(stdin);
    scanf("%d", &menuChoose);
    switch(menuChoose){
    case 1:
        econio_set_title("Sakk - J�t�k");
        newGameStart();
        econio_clrscr();
        break;
    case 2:
        econio_set_title("Sakk - J�t�k");
        loadGameStart();
        econio_clrscr();
        break;
    case 3:
        econio_set_title("Sakk - Ranglista");
        getLeaderboard();
        econio_clrscr();
        break;
    case 4:
        break;
    default: errorPrint("K�rem adjon meg egy olyan sz�mot, amely szerepel a men�ben!", 0,6);
        break;
    }
    }
    while( menuChoose!=4 );

}
