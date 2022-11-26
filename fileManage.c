#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "control.h"
#include "tableDisplay.h"
#include "debugmalloc.h"


void fileWrite(char *saveName, DefDatas *data){

    char *saveTo=(char*) malloc((strlen(saveName)+12)*sizeof(char));
    strcpy(saveTo,"./game/");
    strcat(saveTo, saveName);
    strcat(saveTo, ".txt");

    FILE *fp;

    fp = fopen(saveTo, "w");

    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
        return;
    }
    fprintf(fp,"Sakk-Játék\n-1\n");

/*
    for(int i=0; i<strlen(data->names); i++){
        if(data->names[i]==';'){
            fprintf(fp,"\n");
        }else{
        fprintf(fp,"%c", data->names[i]);
        }
    }
*/
    fprintf(fp, data->names);
    fprintf(fp,"\n-1\n");

    StepLogList *step=data->stepListBegin;

    while(step!=NULL){
        fprintf(fp, "%d%d=%d%d;", step->fromX, step->fromY, step->toX, step->toY);
        step=step->next;
    }


    fclose(fp);
    free(saveTo);
}
/*
char *readAString(){
    int db = 0;
    char *theWord = (char*) malloc(sizeof(char) * 1);
    theWord[0] = '\0';
    char newC;
    fflush(stdin); //Forrás: https://www.tutorialspoint.com/clearing-input-buffer-in-c-cplusplus
    while (scanf("%c", &newC) == 1 && newC != '\n') {
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
}
*/
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
}

char *readNameFile(char *savedGame){
    FILE *fp;

    fp = fopen("./game/gyerekek.txt", "r");

    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
        return NULL;
    }

    char trash[20];
    fgets(trash, 12, fp);
    fgets(trash, 4, fp);


    return readFileRow(fp);

}


StepLogList *readStepsFile(char *savedName,DefDatas *data){
    FILE *fp;

    fp = fopen("./game/gyerekek.txt", "r");
    if (fp == NULL) {
        perror("Fájl megnyitása sikertelen");
        return NULL;
    }

    char *trash;
    trash=readFileRow(fp);
    free(trash);
    trash=readFileRow(fp);
    free(trash);
trash=readFileRow(fp);
    free(trash);
trash=readFileRow(fp);
    free(trash);


    char* elements=readFileRow(fp);


    return NULL;
}
