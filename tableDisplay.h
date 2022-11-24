#ifndef TABLEDISPLAY_H_INCLUDED
#define TABLEDISPLAY_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "econio.h"
#include "control.h"
#include "pieces.h"

/**P�lya alapj�nak 'kirajzol�s': az oldal f�lek �s a h�tt�rszinez�sek  */
void basicTableDraw();

/**Be�ll�tja a param�terk�nt kapott x y mez�nek a h�tter�t, hogy megfeleljen a sakkt�bla sz�nez�s�nek. */
void setBackground(int x, int y);

/**Be�ll�tja a param�terben kapott karakter alapj�n a karakter sz�nt, ha 'l': akkor vil�gosra, ha m�s: akkor s�t�tre */
void setColor(bool color);

/**A param�terben kapott list�ra mutat� pointer, seg�ts�g�vel v�gigmegy a list�n a f�gv�ny �s kirajzolja a b�bukat*/
void drawThePieces(PiecesList *pcListBegin);

void stepDrawInTable();

void errorPrint(char *err, int x, int y);

#endif // TABLEDISPLAY_H_INCLUDED
