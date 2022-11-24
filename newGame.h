#ifndef NEWGAME_H_INCLUDED
#define NEWGAME_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"
#include "control.h"

char *lightName;
char *darkName;

/**Az új játékhoz szükséges függvényeket meghívja*/
void newGameStart();

/**pieceLoad() függvény segítségével a kezdetben szükséges összes bábut betölti a játék bábuit tartalmazó listába*/
void newGamePices();

#endif // NEWGAME_H_INCLUDED
