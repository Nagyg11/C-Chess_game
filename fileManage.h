#ifndef FILEMANAGE_H_INCLUDED
#define FILEMANAGE_H_INCLUDED

#include "newGame.h"
#include "leaderBoard.h"

void fileWrite(char *saveName, DefDatas *data);

char *readNameFile(char *savedGame);

void readStepsFile(char *savedName,DefDatas *data);

LeaderboardArray *readFileLeaderboard(int *length);


#endif // FILEMANAGE_H_INCLUDED
