
#ifndef CHESSRULE_H_INCLUDED
#define CHESSRULE_H_INCLUDED

#include <stdbool.h>
#include "newGame.h"

/**Vizsg�lja hogy a j�t�kot megnyerte-e valamelyik j�t�kos. Visszat�r�si �rt�ke bool, ami igaz: ha megnyerte valaki, hamis: ha nem*/
bool checkMate(bool color, DefDatas *data);

bool defaultStepCheck(PiecesList *piece, int toX, int toY,bool check, DefDatas *data);

//bool pawnStepCheck(PiecesList *piece, int toX, int toY);
//bool chessCheck(bool color);

bool colorCheck(PiecesList *piece, DefDatas *data);

bool checkCheck(PiecesList *king, DefDatas *data);

#endif // CHESSRULE_H_INCLUDED
