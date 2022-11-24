#ifndef CONTROL_H_INCLUDED
#define CONTROL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "econio.h"
#include "pieces.h"
#include "tableDisplay.h"
#include "chessRule.h"
#include "menu.h"

typedef struct StepLogList{
    int fromX;
    int fromY;
    int toX;
    int toY;
    struct StepLogList *next;
}StepLogList;

StepLogList *getStepLogList();

/**Szöveget olvas be a bementrõl, visszatérési értéke egy char pointer.*/
char *readAString();

/**Beolvassa hogy melyik bábut szeretné mozgatni és hova.
Egyenlõre csak számokat tud használni a helyzetek meghatározására.
*/
void stepOne(PiecesList *selectedPiece, int x, int y);

/**A játék menetét vezérli. Miután betöltõdött a pálya ez a függvény hívja meg a játék során szükséges függvényeket.*/
void gamePlay();

int lengthLogList();

#endif // CONTROL_H_INCLUDED
