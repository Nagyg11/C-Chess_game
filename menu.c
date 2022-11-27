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

/**Betölti a menût és 1-4-ig lehet választani a menüpontokból
A menühöz be kell írni a választani kivánt menüpont számát majd entert kell nyomni.
*/
void menuLoad(){
    econio_set_title("Sakk - Menü");

    econio_clrscr();
    int menuChoose=0;
    do{
    econio_gotoxy(0,0);
    printf("Kérem válasszon menüpontot! \n");
    printf("[1] Új játek kezdés\n");
    printf("[2] Játek állás betöltés fájlból\n");
    printf("[3] Dicsõség lista\n");
    printf("[4] Kilépés\n");
    fflush(stdin);
    scanf("%d", &menuChoose);
    switch(menuChoose){
    case 1:
        econio_set_title("Sakk - Játék");
        newGameStart();
        econio_clrscr();
        break;
    case 2:
        econio_set_title("Sakk - Játék");
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
    default: errorPrint("Kérem adjon meg egy olyan számot, amely szerepel a menüben!", 0,6);
        break;
    }
    }
    while( menuChoose!=4 );

}
