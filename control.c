#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "newGame.h"
#include "econio.h"
#include "pieces.h"
#include "tableDisplay.h"
#include "chessRule.h"
#include "fileManage.h"
#include "debugmalloc.h"


void stepAddLog(PiecesList *piece, int toX, int toY, DefDatas *data){
    StepLogList *newStep=(StepLogList*) malloc(sizeof(StepLogList));
        newStep->fromX=piece->posX;
        newStep->fromY=piece->posY;
        newStep->toX=toX;
        newStep->toY=toY;
        newStep->next=NULL;
        if(data->stepListBegin==NULL){
            data->stepListBegin=newStep;
        }
    else{
        StepLogList *helper=data->stepListBegin;
        while(helper->next!=NULL){
            helper=helper->next;
        }
        helper->next=newStep;
        }
}

/*StepLogList *getStepLogList(){
    return stepListBegin;
}*/

int lengthLogList(DefDatas *data){
    StepLogList *helper=data->stepListBegin;
    int i;
    for( i=0; helper!=NULL; i++){
        helper=helper->next;
    }
    return i;
}

void stepLogListFree(DefDatas *data){
    StepLogList *mover = data->stepListBegin;
    while (mover != NULL) {
        StepLogList *next = mover->next;
        free(mover);
        mover = next;
    }

}


void quitGame(DefDatas *data){

    econio_clrscr();
    printf("Adja meg k�rem milyen n�ven szeretn� menteni a j�t�kot: ");
    char *saveName=readAString();
//    char *names="auto;palyam ja";
    fileWrite(saveName, data);

    data->gameEnd=true;
    free(saveName);
    pieceListFree(data);
    stepLogListFree(data);
    //menuLoad();
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

/*void kiir(){
    StepLogList *helper=stepListBegin;
        while(helper!=NULL){
            printf("%d ,%d = %d, %d \n", helper->fromX, helper->fromY, helper->toX, helper->toY);
            helper=helper->next;
        }
        return NULL;
}*/

/**A t�bl�n val� b�b� kijelz�s�t megv�ltoztatja �s megh�vja a "changePieceXY()" f�gv�nyt, ami a list�ban is �t�rja a b�bu helyzet�t.*/
void stepOne(PiecesList *selectedPiece, int x, int y, DefDatas *data){

    if(colorCheck(selectedPiece, data)){

    if(defaultStepCheck(findPiece(selectedPiece->posX, selectedPiece->posY, data), x, y, data)){
        econio_gotoxy(10,10);
        printf("    ");
        stepAddLog(selectedPiece, x, y, data);
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

/**Beolvassa hogy melyik b�but szeretn� mozgatni �s hova.
Egyenl�re csak sz�mokat tud haszn�lni a helyzetek meghat�roz�s�ra.
*/
void stepGetter(DefDatas *data){
    econio_textbackground(16);
    econio_textcolor(16);

    int selPosX;
    int selPosY;
    int stepPosX;
    int stepPosY;
    char *from=NULL;
    char *to=NULL;
    econio_gotoxy(0,11);
    printf("K�rem adja meg melyik b�buval szeretne l�pni: \n");
    printf("K�rem adja hova szeretne l�pni: \n");
    printf("A bet�k �s sz�mkok kombin�ci�jav tudja megadni honnan hov� szertene l�pni");

    econio_gotoxy(45,11);
    from=readAString();
    if(!strcmp(from,"menu")){
        quitGame(data);
        econio_gotoxy(0,15);
        printf("J�t�k kil�p�s");
        free(from);
        return;
    }

    econio_gotoxy(31,12);
    to=readAString();

    selPosX=charToNum(from[0]);
    selPosY=numCharToNumber(from[1]);
    stepPosX=charToNum(to[0]);
    stepPosY=numCharToNumber(to[1]);

    if(strlen(to)==2 && strlen(from)==2 &&
       selPosX!=-1 && selPosY!=-1 &&
       stepPosX!=-1 && stepPosY!=-1){
        stepOne(findPiece(selPosX, selPosY, data), stepPosX, stepPosY, data);
       }else if(!strcmp(to,"menu")){
        quitGame(data);
        econio_gotoxy(0,15);
        printf("J�t�k kil�p�s");
        free(from);
        free(to);
        return;
    }else{
        econio_gotoxy(0,16);
        printf("Hibas bemenet");
    }
    free(from);
    free(to);
}

/**A j�t�k menet�t vez�rli. Miut�n bet�lt�d�tt a p�lya ez a f�ggv�ny h�vja meg a j�t�k sor�n sz�ks�ges f�ggv�nyeket.*/
void gamePlay(DefDatas *data){
    while(!data->gameEnd){
    //econio_clrscr();
    if(checkCheck(data))
    {
        econio_gotoxy(0,17);
        printf("Sakk!");
    }
    basicTableDraw();
    drawThePieces(data->pcListBegin);
    stepGetter(data);

    //colorStep=!colorStep;
    }
}
