#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "econio.h"
#include "newGame.h"
#include "pieces.h"
#include "control.h"
#include "debugmalloc.h"


/**Pálya alapjának 'kirajzolás': az oldal fülek és a háttérszinezések  */
void basicTableDraw(){

econio_gotoxy(0,0);

/*A pálya kirajzolása*/
    char rowCh='A';
    econio_textcolor(0);

    for(int x=0; x!=10; x++){

        econio_textbackground(9);
        if(x==0 || x==9){
        //számoszlop iratás
            for(int i=8; i!=0; i--){
                econio_gotoxy(x, i);
                printf("%d", i);
            }
        }
        else{
            //betűsor íratás
            econio_gotoxy(x,0);
            printf("%c", rowCh);
            //tábla szinezés
            for(int i=1; i!=9; i++){
                econio_gotoxy(x, i);
                if((i%2+(x+1))%2!=0){
                    econio_textbackground(8);
                }else{
                    econio_textbackground(6);
                }

                printf(" ");
            }

            //betûsor íratás
            econio_textbackground(9);
            econio_gotoxy(x,9);
            printf("%c", rowCh);
            rowCh++;
        }

    }
/*Háttér visszaállítás*/
    econio_gotoxy(10, 10);
    econio_textcolor(16);
    econio_textbackground(16);

}

/**Beállítja a paraméterként kapott x y mezőnek a hátterét, hogy megfeleljen a sakktábla színezésének. */
void setBackground(int x, int y){
    if((x+y)%2==0){
        econio_textbackground(8);
    }
    else{
    econio_textbackground(6);
    }
}

/**Beállítja a paraméterben kapott karakter alapján a karakter színt, ha "color" változó értéke true : akkor világosra, ha false: akkor sötétre */
void setColor(bool color){
    if(color){
        econio_textcolor(15);
    }else{
        econio_textcolor(0);
    }
}


/**A paraméterben kapott listára mutató pointer, segítségével végigmegy a listán a fügvény és kirajzolja a bábukat*/
void drawThePieces(PiecesList *pcListBegin){
    for(PiecesList *i=pcListBegin; i!=NULL; i=i->next){
        econio_gotoxy(i->posX,i->posY);
        setBackground(i->posX,i->posY);
        setColor(i->color);
        printf("%c",i->name);
    }
    econio_gotoxy(11,11);
}

void stepDrawInTable(PiecesList *selectedPiece, int x, int y){
    econio_gotoxy(selectedPiece->posX,selectedPiece->posY);
    setBackground(selectedPiece->posX,selectedPiece->posY);
    printf(" ");

    econio_gotoxy(x,y);
    setBackground(x,y);
    setColor(selectedPiece->color);
    printf("%c",selectedPiece->name);

    econio_textcolor(16);
    econio_textbackground(16);
}

void errorPrint(char *err, int x, int y){
    econio_clrscr();
    econio_gotoxy(x,y);
    printf("%s", err);
    econio_gotoxy(0,0);

}
