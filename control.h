#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include "newGame.h"

/**Szöveget olvas be a bementrõl, visszatérési értéke egy char pointer.*/
char *readAString();

/**Beolvassa hogy melyik bábut szeretné mozgatni és hova.
Egyenlõre csak számokat tud használni a helyzetek meghatározására.
*/
void stepOne(PiecesList *selectedPiece, int x, int y, DefDatas *data);

/**A játék menetét vezérli. Miután betöltõdött a pálya ez a függvény hívja meg a játék során szükséges függvényeket.*/
void gamePlay(DefDatas *data);

int lengthLogList(DefDatas *data);

#endif // CONTROL_H_INCLUDED
