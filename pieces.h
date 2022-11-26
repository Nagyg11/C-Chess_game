#ifndef PIECES_H_INCLUDED
#define PIECES_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"



/**Betölt a paraméterben kapott adatokkal egy új elemet a bábukat tartalmazó lista végére*/
void pieceLoad(char name, bool color, int x, int y, DefDatas *data);




PiecesList *findPiece(int posX, int posY, DefDatas *data);

/**Vissza adja a játék bábu adatait tartalmazó lista első elemére mutató pointert*/
//PiecesList *getPcListBegin();

void changePieceXY(PiecesList *selectedPiece, int x, int y);

PiecesList *findColorKing(bool color, DefDatas *data);

void  pieceListFree(DefDatas *data);


#endif // PIECES_H_INCLUDED
