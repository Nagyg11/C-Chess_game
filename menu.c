#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "control.h"
#include "econio.h"

/**Betölti a menűt és 1-4-ig lehet választani a menüpontokból
A menühöz be kell írni a választani kivánt menüpont számát majd entert kell nyomni.
*/
void menuLoad(){
    econio_clrscr();
    econio_set_title("Sakk - Menü");

    int menuChoose=0;
    printf("Kérem válasszon menüpontot! \n");
    printf("[1] Új játek kezdés\n");
    printf("[2] Játek állás betöltés fájlból\n");
    printf("[3] Dicsõseg lista\n");
    printf("[4] Kilépés\n");
    do{
    fflush(stdin);
    scanf("%d", &menuChoose);
    switch(menuChoose){
    case 1: newGameStart();
        break;
    case 2:
        break;
    case 3:
        break;
    case 4:
        break;
    default: printf("Kérem adjon meg egy olyan számot, amely szerepel a menüben!");
            //econio_gotoxy(0,2);
        break;
    }
    }
    while(menuChoose<1 || menuChoose>4);

}
