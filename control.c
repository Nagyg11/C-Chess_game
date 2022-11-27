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

char *colorName(bool color,DefDatas *data){
    int db = 0;
    char *theName = (char*) malloc(sizeof(char) * 1);
    theName[0] = '\0';
    char newC;

    if(!color){
        while(data->names[db]!=';'){
            db++;
        }
        db++;
    }

    while (data->names[db]!= (color?';':'\0')) {
        newC=data->names[db];
        char *helpArray = (char*) malloc(sizeof(char) * (db+1+1));
        for (int i = 0; i < db; ++i){
            helpArray[i] = theName[i];
        }
        free(theName);
        theName = helpArray;
        theName[db] = newC;
        theName[db+1] = '\0';
        ++db;
    }
    return theName;
}


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

void deleteLastLog(DefDatas *data){
    StepLogList *mover=data->stepListBegin;
    while(mover->next->next!=NULL){
        mover=mover->next;
    }
    free(mover->next);
    mover->next=NULL;

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

char *join3String(char *str1, char *str2, char *str3){
    char *joinedStr=(char*) malloc((strlen(str1)+strlen(str2)+strlen(str3)+1)*sizeof(char));
    strcpy(joinedStr,str1);
    strcat(joinedStr, str2);
    strcat(joinedStr, str3);
    return joinedStr;
}


void quitGame(DefDatas *data){
    data->gameEnd=true;
    pieceListFree(data);
    stepLogListFree(data);
}

void win(bool color, DefDatas *data){
    econio_clrscr();
    char *winName=colorName(color, data);
    printf("Gratulálok gyözött %s!", winName);
    char c;
    scanf("%c", &c);
    //putToLeaderboard(winName);
    quitGame(data);
}

void saveGame(DefDatas *data){
    econio_clrscr();
    printf("Adja meg kérem milyen néven szeretné menteni a játékot: ");
    char *saveName=readAString();
    char *trash=saveName;
    saveName=join3String("./savedGames/",saveName,".txt");
    free(trash);
    fileWrite(saveName, data);
    free(saveName);
    quitGame(data);
}

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

/**A táblán való bábú kijelzését megváltoztatja és meghívja a "changePieceXY()" fügvényt, ami a listában is átírja a bábu helyzetét.*/
void stepOne(PiecesList *selectedPiece, int x, int y, DefDatas *data){

    if(colorCheck(selectedPiece, data)){

    if(defaultStepCheck(selectedPiece, x, y, false, data)){
        int fromX=selectedPiece->posX;
        int fromY=selectedPiece->posY;

        stepAddLog(selectedPiece, x, y, data);
        changePieceXY(selectedPiece,x,y);
        if(checkCheck(findColorKing(!(lengthLogList(data)%2==0), data), data)){
            errorPrint("A sakkból ki kell lépnie és nem is léphet sakkba!",0,16);
            changePieceXY(selectedPiece, fromX,fromY);
            deleteLastLog(data);
            return;
        }

        econio_clrscr();
    }else{
        errorPrint("Hibás lépés!",0,16);
    }

    }else{
        errorPrint("Nem Ön jön!", 0,16);
    }

    //stepDrawInTable(selectedPiece,x,y);



}

/**Beolvassa hogy melyik bábut szeretné mozgatni és hova.
Egyenlõre csak számokat tud használni a helyzetek meghatározására.
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
    printf("Kérem adja meg melyik bábuval szeretne lépni: \n");
    printf("Kérem adja hova szeretne lépni: \n");
    printf("A betûk és számkok kombinációjav tudja megadni honnan hová szertene lépni!\n");
    printf("Ha ki szeretne lepni írja be \"menu\" szót valamelyik bementre!");

    econio_gotoxy(45,11);
    from=readAString();
    if(!strcmp(from,"menu")){
        saveGame(data);
        econio_gotoxy(0,15);
        printf("Játék kilépés");
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
            if(findPiece(selPosX, selPosY, data)!=NULL){
            stepOne(findPiece(selPosX, selPosY, data), stepPosX, stepPosY, data);
            }else{
                errorPrint("Nem bábut választott!",0,16);
            }
       }else if(!strcmp(to,"menu")){
        saveGame(data);
        econio_gotoxy(0,15);
        printf("Játék kilépés");
        free(from);
        free(to);
        return;
    }else{
        errorPrint("Hibás bemenet!",0,16);
    }
    free(from);
    free(to);
}

/**A játék menetét vezérli. Miután betöltõdött a pálya ez a függvény hívja meg a játék során szükséges függvényeket.*/
void gamePlay(DefDatas *data){
    econio_clrscr();

    while(!data->gameEnd){
    bool tempColor=lengthLogList(data)%2==0;

    if(checkCheck(findColorKing(findColorKing(tempColor,data), data), data))
    {
        if(checkMate(tempColor, data), data){
            win(!(tempColor),data);
        }else{
        econio_gotoxy(0,17);
        printf("Sakk!");
        }

    }else{
        econio_gotoxy(0,17);
        printf("     ");
    }
    basicTableDraw();
    drawThePieces(data->pcListBegin);

    econio_gotoxy(0,10);
    lengthLogList(data)%2==0?printf("világos"):printf("sötét  ");

    stepGetter(data);
    }
}
