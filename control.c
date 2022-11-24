#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "econio.h"
#include "pieces.h"
#include "tableDisplay.h"
#include "chessRule.h"
#include "menu.h"


/**Szöveget olvas be a bementrõl, visszatérési értéke egy char pointer.*/
char *readAString(){
    int db = 0;
    char *theWord = (char*) malloc(sizeof(char) * 1);
    theWord[0] = '\0';
    char newC;
    fflush(stdin); //Forrás: https://www.tutorialspoint.com/clearing-input-buffer-in-c-cplusplus
    while (scanf("%c", &newC) == 1 && newC != '\n') {
        char *helpArray = (char*) malloc(sizeof(char) * (db+1+1));
        for (int i = 0; i < db; ++i){
            helpArray[i] = theWord[i];
        }
        free(theWord);
        theWord = helpArray;
        theWord[db] = newC;
        theWord[db+1] = '\0';
        ++db;
    }
    return theWord;
}

void deleteCharacters(int numCh){
    for(int i=0; i<numCh; i++){
        printf(" ");
    }
}

int characterToNumber(char ch){

    ch=tolower(ch);
    if('0'<=ch && ch<='9'){
        return ch-'0';
    }
    return -1;
}

int *szamOlvasBe(){
    int sz;
    int *szam;
    scanf("%d", &sz);
    szam=&sz;
    return szam;
}

/**Beolvassa hogy melyik bábut szeretné mozgatni és hova.
Egyenlõre csak számokat tud használni a helyzetek meghatározására.
*/
void stepGetter(bool color){
    econio_textbackground(16);
    econio_textcolor(16);

    int selPosX;
    int selPosY;
    int stepPosX;
    int stepPosY;
    char *c;
    econio_gotoxy(0,11);
    printf("Kérem adja meg melyik bábuval szeretne lépni: x:  y:\n");
    printf("Kérem adja hova szeretne lépni: x:  y:  \n");
    printf("Egyenlõre a betûk helyett is számot írjon be.");

    char d='a';//=readAString();
    scanf("%c", &d);
    printf("%c", d);
    econio_gotoxy(48,11);
    scanf("%d", &selPosX);
    econio_gotoxy(52,11);
    scanf("%d", &selPosY);
    econio_gotoxy(34,12);
    scanf("%d", &stepPosX);
     econio_gotoxy(38,12);
    scanf("%d", &stepPosY);

    if(defaultStepCheck(findPiece(selPosX, selPosY), stepPosX, stepPosY, color)){
        stepOne(findPiece(selPosX,selPosY),stepPosX, stepPosY);
        econio_gotoxy(10,10);
        printf("    ");
    }else{
        econio_gotoxy(10,10);
        printf("Hiba");
    }

    if(chessCheck(color)){
        econio_gotoxy(0,15);
        printf("Sakk");
    }else{
        econio_gotoxy(0,15);
        printf("   ");
    }
    //c=readAString()

    //selPc=hosszu_sort_olvas();
    //scanf("%c", &selPc);
    //printf("%c", selPc);
    //free(selPc);
    //econio_gotoxy(32,12);
    //stepPos=readAString();
    //printf("\n %c %c",selPc, selPc);
}

/**A táblán való bábú kijelzését megváltoztatja és meghívja a "changePieceXY()" fügvényt, ami a listában is átírja a bábu helyzetét.*/
void stepOne(PiecesList *selectedPiece, int x, int y){

    //stepDrawInTable(selectedPiece,x,y);
    changePieceXY(selectedPiece,x,y);


}

/**A játék menetét vezérli. Miután betöltõdött a pálya ez a függvény hívja meg a játék során szükséges függvényeket.*/
void gamePlay(bool colorStep){
    while(!wonSy()){
    //econio_clrscr();
    basicTableDraw();
    drawThePieces(getPcListBegin());
    stepGetter(colorStep);


    colorStep=!colorStep;
    }
}
