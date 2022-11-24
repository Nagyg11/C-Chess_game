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

StepLogList *stepListBegin=NULL;
StepLogList *stepListBack=NULL;

void stepAddLog(PiecesList *piece, int toX, int toY){
    StepLogList *newStep=(StepLogList*) malloc(sizeof(StepLogList));
        newStep->fromX=piece->posX;
        newStep->fromY=piece->posY;
        newStep->toX=toX;
        newStep->toY=toY;
        newStep->next=NULL;
        if(stepListBegin==NULL){
            stepListBegin=newStep;
        }
    else{
        StepLogList *helper=stepListBegin;
        while(helper->next!=NULL){
            helper=helper->next;
        }
        helper->next=newStep;
        }
}

StepLogList *getStepLogList(){
    return stepListBegin;
}

int lengthLogList(){
    StepLogList *helper=stepListBegin;
    int i;
    for( i=0; helper!=NULL; i++){
        helper=helper->next;
    }
    return i;
}


/**Sz�veget olvas be a bementr�l, visszat�r�si �rt�ke egy char pointer.*/
char *readAString(){
    int db = 0;
    char *theWord = (char*) malloc(sizeof(char) * 1);
    theWord[0] = '\0';
    char newC;
    fflush(stdin); //Forr�s: https://www.tutorialspoint.com/clearing-input-buffer-in-c-cplusplus
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

int numCharToNumber(char ch){

    ch=tolower(ch);
    if('0'<=ch && ch<='9'){
        return ch-'0';
    }
    return -1;
}

int charToNum(char ch){

    ch=tolower(ch);
    if('a'<=ch && ch<='h'){
        return ch-'a'+1;
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

/*void kiir(){
    StepLogList *helper=stepListBegin;
        while(helper!=NULL){
            printf("%d ,%d = %d, %d \n", helper->fromX, helper->fromY, helper->toX, helper->toY);
            helper=helper->next;
        }
        return NULL;
}*/

/**Beolvassa hogy melyik b�but szeretn� mozgatni �s hova.
Egyenl�re csak sz�mokat tud haszn�lni a helyzetek meghat�roz�s�ra.
*/
void stepGetter(){
    econio_textbackground(16);
    econio_textcolor(16);

    int selPosX;
    int selPosY;
    int stepPosX;
    int stepPosY;
    char *from;
    char *to;
    econio_gotoxy(0,11);
    printf("K�rem adja meg melyik b�buval szeretne l�pni: \n");
    printf("K�rem adja hova szeretne l�pni: \n");
    printf("A bet�k �s sz�mkok kombin�ci�jav tudja megadni honnan hov� szertene l�pni");

    econio_gotoxy(45,11);
    from=readAString();

    econio_gotoxy(31,12);
    to=readAString();

    selPosX=charToNum(from[0]);
    selPosY=numCharToNumber(from[1]);
    stepPosX=charToNum(to[0]);
    stepPosY=numCharToNumber(to[1]);

    if(strlen(to)==2 && strlen(from)==2 &&
       selPosX!=-1 && selPosY!=-1 &&
       stepPosX!=-1 && stepPosY!=-1){
        stepOne(findPiece(selPosX, selPosY), stepPosX, stepPosY);
       }else if(strcmp(to,"menu")){
//        quitGame();
        econio_gotoxy(0,15);
        printf("J�t�k kil�p�s");
    }else{
        econio_gotoxy(0,16);
        printf("Hibas bemenet");
    }



    /*
    econio_gotoxy(48,11);
    scanf("%d", &selPosX);
    econio_gotoxy(52,11);
    scanf("%d", &selPosY);
    econio_gotoxy(34,12);
    scanf("%d", &stepPosX);
     econio_gotoxy(38,12);
    scanf("%d", &stepPosY);*/


    /*if(chessCheck(color)){
        econio_gotoxy(0,15);
        printf("Sakk");
    }else{
        econio_gotoxy(0,15);
        printf("   ");
    }*/
    //c=readAString()

    //selPc=hosszu_sort_olvas();
    //scanf("%c", &selPc);
    //printf("%c", selPc);
    //free(selPc);
    //econio_gotoxy(32,12);
    //stepPos=readAString();
    //printf("\n %c %c",selPc, selPc);
}

/**A t�bl�n val� b�b� kijelz�s�t megv�ltoztatja �s megh�vja a "changePieceXY()" f�gv�nyt, ami a list�ban is �t�rja a b�bu helyzet�t.*/
void stepOne(PiecesList *selectedPiece, int x, int y){

    if(colorCheck(selectedPiece)){
    if(defaultStepCheck(findPiece(selectedPiece->posX, selectedPiece->posY), x, y)){
        econio_gotoxy(10,10);
        printf("    ");
        stepAddLog(selectedPiece, x, y);
        changePieceXY(selectedPiece,x,y);
    }else{
        econio_gotoxy(10,10);
        printf("Hiba");
    }
    }else{
        econio_gotoxy(0,16);
        printf("Nem �n j�n!");
    }

    //stepDrawInTable(selectedPiece,x,y);



}

/**A j�t�k menet�t vez�rli. Miut�n bet�lt�d�tt a p�lya ez a f�ggv�ny h�vja meg a j�t�k sor�n sz�ks�ges f�ggv�nyeket.*/
void gamePlay(){
    while(!checkMate()){
    //econio_clrscr();
    basicTableDraw();
    drawThePieces(getPcListBegin());
    stepGetter();


    //colorStep=!colorStep;
    }
}
