#ifndef LEADERBOARD_H_INCLUDED
#define LEADERBOARD_H_INCLUDED

typedef struct LeaderboardArray{
    char *player;
    int winNum;
}LeaderboardArray;

void getLeaderboard();

#endif // LEADERBOARD_H_INCLUDED
