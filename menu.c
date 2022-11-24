#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "control.h"
#include "econio.h"

/**Bet�lti a men�t �s 1-4-ig lehet v�lasztani a men�pontokb�l
A men�h�z be kell �rni a v�lasztani kiv�nt men�pont sz�m�t majd entert kell nyomni.
*/
void menuLoad(){
    econio_clrscr();
    econio_set_title("Sakk - Men�");

    int menuChoose=0;
    printf("K�rem v�lasszon men�pontot! \n");
    printf("[1] �j j�tek kezd�s\n");
    printf("[2] J�tek �ll�s bet�lt�s f�jlb�l\n");
    printf("[3] Dics�s�g lista\n");
    printf("[4] Kil�p�s\n");
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
    default: printf("K�rem adjon meg egy olyan sz�mot, amely szerepel a men�ben!");
            //econio_gotoxy(0,2);
        break;
    }
    }
    while(menuChoose<1 || menuChoose>4);

}
