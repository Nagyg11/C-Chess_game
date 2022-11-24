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

/**Az �j j�t�khoz sz�ks�ges f�ggv�nyeket megh�vja*/
void newGameStart();

/**pieceLoad() f�ggv�ny seg�ts�g�vel a kezdetben sz�ks�ges �sszes b�but bet�lti a j�t�k b�buit tartalmaz� list�ba*/
void newGamePices();

#endif // NEWGAME_H_INCLUDED
