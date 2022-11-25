#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"


/**A j�t�kban �ppen aktu�lisan szerepl� b�buk list�j�ra mutat� pointer*/
PiecesList *pcListBegin=NULL;

/**Bet�lt a param�terben kapott adatokkal egy �j elemet a b�bukat tartalmaz� lista v�g�re*/
void pieceLoad(char name, bool color, int x, int y){

        PiecesList *newPc=(PiecesList*) malloc(sizeof(PiecesList));
        newPc->name=name;
        newPc->posX=x;
        newPc->posY=y;
        newPc->color=color;
        newPc->next=NULL;
        if(pcListBegin==NULL){
            pcListBegin=newPc;
        }
    else{
        PiecesList *helper=pcListBegin;
        while(helper->next!=NULL){
            helper=helper->next;
        }
        helper->next=newPc;
        }
        //printf("%c ,%c , %d, %d \n", name, color, x, y);
}

/**Vissza adja a j�t�k b�bu adatait tartalmaz� lista els� elem�re mutat� pointert*/
PiecesList *getPcListBegin(){
    return pcListBegin;
}

PiecesList *findPiece(int posX, int posY){
    PiecesList *helper=pcListBegin;
        while(helper!=NULL){
            if((helper->posX== posX )&& (helper->posY== posY)){
                return helper;
            }
            helper=helper->next;
        }
        return NULL;
}

PiecesList *findColorKing(bool color){
    PiecesList *helper=pcListBegin;
        while(helper!=NULL){
            if((helper->color== color )&& (helper->name== 'k')){
                return helper;
            }
            helper=helper->next;
        }
        return NULL;
}

/*void kiir(){
    PiecesList *helper=pcListBegin;
        while(helper!=NULL){
            printf("%c ,%c , %d, %d \n", helper->name, helper->color, helper->posX, helper->posY);
            helper=helper->next;
        }
        return NULL;
}*/

void changePieceXY(PiecesList *selectedPiece, int x, int y){
    selectedPiece->posX=x;
    selectedPiece->posY=y;
};


void  pieceListFree(){
    PiecesList *mover = pcListBegin;
    while (mover != NULL) {
        PiecesList *next = mover->next;
        free(mover);
        mover = next;
    }
}
