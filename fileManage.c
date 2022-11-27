#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "control.h"
#include "tableDisplay.h"
#include "debugmalloc.h"
#include "leaderBoard.h"


void fileWrite(char *saveName, DefDatas *data){

    FILE *fp;

    fp = fopen(saveName, "w");

    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
        return;
    }
    fprintf(fp,"Sakk-Játék\n-1\n");

    fprintf(fp, data->names);
    fprintf(fp,"\n-1\n");

    StepLogList *step=data->stepListBegin;

    while(step!=NULL){
        fprintf(fp, "%d%d=%d%d;", step->fromX, step->fromY, step->toX, step->toY);
        step=step->next;
    }


    fclose(fp);
}

char *readFileRow(FILE *fp){
    int db = 0;
    char *theWord = (char*) malloc(sizeof(char) * 1);
    theWord[0] = '\0';
    char newC;
    while (fscanf(fp,"%c", &newC) == 1 && newC != '\n') {
        char *helpArray = (char*) malloc(sizeof(char) * (db+1+1));
        for (int i = 0; i < db; ++i){
            helpArray[i] = theWord[i];
        }
        free(theWord);
        theWord = helpArray;
        theWord[db] = newC;
        theWord[db+1] = '\0';
        ++db;
    }
    return theWord;
    fclose(fp);
}

char *readNameFile(char *savedGame){
    FILE *fp;

    fp = fopen(savedGame,"r");

    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
        return NULL;
    }

    char trash[20];
    fgets(trash, 12, fp);
    fgets(trash, 4, fp);

    fclose(fp);

    return readFileRow(fp);

}


void readStepsFile(char *savedName,DefDatas *data){
    FILE *fp;

    fp = fopen(savedName, "r");
    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
    }

    char *trash;
    for(int i=1; i<=4; i++){
        trash=readFileRow(fp);
        free(trash);
    }


    char* elements=readFileRow(fp);
    PiecesList *piece=(PiecesList*) malloc(sizeof(PiecesList));

    for(int i=0; i+6<strlen(elements)+1; i+=6){
        piece->posX=elements[i]-'0';
        piece->posY=elements[i+1]-'0';
        stepAddLog(piece, elements[i+3]-'0', elements[i+4]-'0', data);
    }

    free(piece);
    free(elements);
    fclose(fp);
}


LeaderboardArray *readFileLeaderboard(int *lengthBack){
    FILE *fp;
     fp = fopen("./leaderboard/leaderboard.txt","r");

     char *trash;
     trash=readFileRow(fp);
     free(trash);

     char *end="end;end";
     char *row=readFileRow(fp);
     LeaderboardArray *board=(LeaderboardArray*) malloc(sizeof(LeaderboardArray));

     int length=0;

     while(strcmp(row,end)){

        LeaderboardArray *helpBoard=(LeaderboardArray*) malloc(sizeof(LeaderboardArray)*(length));
        for(int i=0; i<length; i++){
            helpBoard[i]=board[i];
        }
        free(board);

        board=(LeaderboardArray*) malloc(sizeof(LeaderboardArray)*(length+1));
        for(int i=0; i<length; i++){
            board[i]=helpBoard[i];
        }
        free(helpBoard);

        board[length].player=row;
        char *number=readFileRow(fp);
        int multiplier=1;


            board[length].winNum=0;
        for(int i=strlen(number)-1; i>=0; i--){
            board[length].winNum+=(number[i]-'0')*multiplier;
            multiplier=multiplier*10;
        }

/*
        int idx;

        //player bemasolas
        board[length].player=(char*) malloc(sizeof(char));
        board[length].player[0]='\0';

        for(idx=0; row[idx]!=';'; idx++){

            char *helpStr=(char*) malloc(sizeof(char)*(idx+1));
            for(int i=0; board[length].player[i]!='\0'; i++){
                helpStr[i]=board[length].player[i];
                helpStr[i+1]='\0';
            }

            free(board[length].player);
            board[length].player=(char*) malloc(sizeof(char)*(idx+1+1));

            for(int i=0; helpStr[i]!='\0'; i++){
                board[length].player[i]=helpStr[i];
                board[length].player[i+1]=row[idx];
                board[length].player[i+2]='\0';
            }
            free(helpStr);
        }

        while(row[idx]!='\0'){
            idx++;
        }

        int multiplier=1;
        for(int i=idx-1; row[i]!=';';i--){
            board[length].winNum+=(row[i]-'0')*multiplier;
            multiplier=multiplier*10;
        }

        free(row);
        row=readFileRow(fp);*/
        free(number);
        length++;
        row=readFileRow(fp);
    }

    *lengthBack=length;
    free(row);
     fclose(fp);
    return board;
}
