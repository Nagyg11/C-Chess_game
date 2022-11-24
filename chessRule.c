#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "pieces.h"

/**Vizsg�lja hogy a j�t�kot megnyerte-e valamelyik j�t�kos. Visszat�r�si �rt�ke bool, ami igaz: ha megnyerte valaki, hamis: ha nem*/
bool wonSy(){
    return false;
}

bool pawnStepCheck(PiecesList *piece, int toX, int toY){
    int direction= piece->color? -1: 1;
    PiecesList *toPiece=findPiece(toX,toY);

    if(((piece->posY) + 1*direction) == toY && piece->posX == toX && toPiece==NULL){
        return true;
    }
    /*if((getStepLogList()==NULL || getStepLogList()->next==NULL )&& ((piece->posY) + 2*direction) && piece->posX == toX){
            return true;
    }*/
    //Hit check
    if(((piece->posX+1 == toX) || (piece->posX-1 == toX)) && (piece->posY+1*direction==toY) && toPiece->color!=piece->color){
            //hitPiece(toPiece);
            return true;
    }
    return false;
}

bool bishopStepCheck(PiecesList *piece, int toX, int toY){
    int deltaX=toX-piece->posX;
    int deltaY=toY-piece->posY;

    int directionX=(deltaX<0)?-1:1;
    int directionY=(deltaY<0)?-1:1;

    deltaX=(deltaX<0)?deltaX*(-1):deltaX;
    deltaY=(deltaY<0)?deltaY*(-1):deltaY;

    if(deltaX!=deltaY){
        return false;
    }

    for(int i=1; (i*directionX+piece->posX) != toX; i++){
        if(findPiece((i*directionX+piece->posX),(i*directionY+piece->posY))!=NULL){
            return false;
        }
    }

    return true;
}

bool rookStepCheck(PiecesList *piece, int toX, int toY){

    int directionX=(toX-piece->posX<0)?-1:1;
    int directionY=(toY-piece->posY<0)?-1:1;

    if(piece->posX==toX){
        for(int i=1; ((i*directionY) + piece->posY) != toY; i++){
                if(findPiece(piece->posX,(i*directionY) + piece->posY)!=NULL){
                    return false;
                }
        }
    }else if(piece->posY==toY){
        for(int i=1; ((i*directionX) + piece->posX) != toX; i++){
                if(findPiece((i*directionX) + piece->posX, piece->posY)!=NULL){
                    return false;
                }
        }
    }else{
        return false;
    }
    return true;
}

bool queenStepCheck(PiecesList *piece, int toX, int toY){
    if(rookStepCheck(piece, toX, toY) || bishopStepCheck(piece, toX, toY)){
        return true;
    }
    return false;
}

bool kingStepCheck(PiecesList *piece, int toX, int toY){
    int deltaX=toX-piece->posX;
    int deltaY=toY-piece->posY;
    deltaX=(deltaX<0)?deltaX*(-1):deltaX;
    deltaY=(deltaY<0)?deltaY*(-1):deltaY;

    if(deltaX==1 || deltaY==1){
        return true;
    }
    return false;

}

bool knightStepCheck(PiecesList *piece, int toX, int toY){
    int deltaX=toX-piece->posX;
    int deltaY=toY-piece->posY;
    deltaX=(deltaX<0)?deltaX*(-1):deltaX;
    deltaY=(deltaY<0)?deltaY*(-1):deltaY;

    if((deltaX==1 && deltaY==2) || (deltaX==2 && deltaY==1)){
        return true;
    }
    return false;

}


bool defaultStepCheck(PiecesList *piece, int toX, int toY, bool color){
    PiecesList *toPiece=findPiece(toX, toY);
    char name=piece->name;

    if(piece->color!=color){
        return false;
    }

    if(toX>8 || toX<0 || toY<1 || toY>8 ){
        return false;
    }

    if(piece->posX==toX&&piece->posY==toY){
        return false;
    }
    if(toPiece!=NULL){
    if(toPiece->color==piece->color){
        return false;
    }
    if(toPiece->name=='k'){
        return false;
    }
    }


    switch(name){
    case 'p':
            return pawnStepCheck(piece, toX, toY);
        break;

    case 'b':
            return bishopStepCheck(piece, toX, toY);
        break;

    case 'r':
            return rookStepCheck(piece, toX, toY);
        break;

    case 'h':
            return knightStepCheck(piece, toX, toY);
        break;
    case 'q':
            return queenStepCheck(piece, toX, toY);
        break;
    case 'k':
            return kingStepCheck(piece, toX, toY);
        break;
    default:
            return false;
        break;

    }

}

bool chessCheck(bool color){
    PiecesList *helper=getPcListBegin();
    PiecesList *king=findColorKing(color);
        while(helper!=NULL){
            if(defaultStepCheck(helper->next, king->posX, king->posY, !color)){
                return true;
            }
            helper=helper->next;
        }
    return false;
}