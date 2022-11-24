#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/**Betölt a paraméterben kapott adatokkal egy új elemet a bábukat tartalmazó lista végére*/
void pieceLoad(char name, bool color, int x, int y);


/**A figurák helye és adatai listákban tárolva. Ha leütnek egy figurát törlésre kerül a listából a bábú*/
typedef struct PiecesList{
    char name;
    bool color;
    int posX;
    int posY;
    struct PiecesList *next;
}PiecesList;

PiecesList *findPiece(int posX, int posY);

/**Vissza adja a játék bábu adatait tartalmazó lista első elemére mutató pointert*/
PiecesList *getPcListBegin();

void changePieceXY(PiecesList *selectedPiece, int x, int y);

PiecesList *findColorKing(bool color);


#endif // PIECES_H_INCLUDED
