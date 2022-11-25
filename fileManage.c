#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"
#include "control.h"

void fileWrite(char *saveName, char *names){

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

    for(int i=0; i<strlen(names); i++){
        if(names[i]==';'){
            fprintf(fp,"\n");
        }else{
        fprintf(fp,"%c", names[i]);
        }
    }
    fprintf(fp,"\n-1\n");

    StepLogList *step=getStepLogList();

    while(step!=NULL){
        fprintf(fp, "%d%d=%d%d;", step->fromX, step->fromY, step->toX, step->toY);
        step=step->next;
    }


    fclose(fp);
    free(saveTo);
}
