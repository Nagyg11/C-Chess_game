
#ifndef CHESSRULE_H_INCLUDED
#define CHESSRULE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"

/**Vizsg�lja hogy a j�t�kot megnyerte-e valamelyik j�t�kos. Visszat�r�si �rt�ke bool, ami igaz: ha megnyerte valaki, hamis: ha nem*/
bool checkMate();

bool defaultStepCheck(PiecesList *piece, int toX, int toY);

bool pawnStepCheck(PiecesList *piece, int toX, int toY);
//bool chessCheck(bool color);

bool colorCheck(PiecesList *piece);

bool checkCheck();

#endif // CHESSRULE_H_INCLUDED
