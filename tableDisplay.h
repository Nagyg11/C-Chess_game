#ifndef TABLEDISPLAY_H_INCLUDED
#define TABLEDISPLAY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "econio.h"
#include "control.h"
#include "pieces.h"

/**Pálya alapjának 'kirajzolás': az oldal fülek és a háttérszinezések  */
void basicTableDraw();

/**Beállítja a paraméterként kapott x y mezõnek a hátterét, hogy megfeleljen a sakktábla színezésének. */
void setBackground(int x, int y);

/**Beállítja a paraméterben kapott karakter alapján a karakter színt, ha 'l': akkor világosra, ha más: akkor sötétre */
void setColor(bool color);

/**A paraméterben kapott listára mutató pointer, segítségével végigmegy a listán a fügvény és kirajzolja a bábukat*/
void drawThePieces(PiecesList *pcListBegin);

void stepDrawInTable();

void errorPrint(char *err, int x, int y);

#endif // TABLEDISPLAY_H_INCLUDED
