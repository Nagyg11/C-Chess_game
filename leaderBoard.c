#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "leaderBoard.h"
#include "fileManage.h"
#include "econio.h"

void orderByAscending(LeaderboardArray *board, int length){
    for (int i = 0; i < length-1; i++){
        int max=i;
        for(int idx=i+1; idx<length-1-1; i++){
            if(board[i].winNum<board[idx].winNum){
                max=idx;
            }
        }
        if(max!=i){
            LeaderboardArray help;
            help.player=board[i].player;
            help.winNum=board[i].winNum;
            board[i].player=board[max].player;
            board[i].winNum=board[max].winNum;
            board[max].player=help.player;
            board[max].winNum=help.winNum;
        }
    }
}

void freeBoard(LeaderboardArray *board, int length){
    for(int i=0; i<length; i++){
        free(board[i].player);
    }
    free(board);
}

void getLeaderboard(){
    econio_gotoxy(0,0);
    econio_clrscr();
    int *length=(int*) malloc(sizeof(int));

    LeaderboardArray *board= readFileLeaderboard(length);

    if(*length!=0){
    orderByAscending(board, *length);
    printf("  Játékos neve - Gyõzelmek száma");
    for(int i=0; i<*length; i++){
        printf("\n%d. %s - %d", i+1, board[i].player, board[i].winNum);
    }
    }else{
        printf("Nem nyert még senki.");
    }

    //freeBoard(board, *length);
    //free(length);
}
