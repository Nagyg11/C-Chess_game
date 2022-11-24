
#ifndef CHESSRULE_H_INCLUDED
#define CHESSRULE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"

/**Vizsg�lja hogy a j�t�kot megnyerte-e valamelyik j�t�kos. Visszat�r�si �rt�ke bool, ami igaz: ha megnyerte valaki, hamis: ha nem*/
bool wonSy();

bool defaultStepCheck(PiecesList *piece, int toX, int toY, bool color);

bool pawnStepCheck(PiecesList *piece, int toX, int toY);
bool chessCheck(bool color);

#endif // CHESSRULE_H_INCLUDED
