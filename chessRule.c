#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "newGame.h"
#include "pieces.h"
#include "control.h"
#include "debugmalloc.h"




/*bool stalemate(){

    if( !checkCheck()){

    }

    return true;
}*/


bool pawnStepCheck(PiecesList *piece, int toX, int toY, DefDatas *data){
    int direction= piece->color? -1: 1;
    PiecesList *toPiece=findPiece(toX,toY, data);

    if(((piece->posY) + 1*direction) == toY && piece->posX == toX && toPiece==NULL){
        return true;
    }
    if(((piece->posY) + 2*direction == toY) && piece->posX == toX && (piece->posY==2 || piece->posY==7) && (findPiece(toX,(piece->posY) + 1*direction, data)==NULL)){
        return true;
    }
    //Hit check
    if(((piece->posX+1 == toX) || (piece->posX-1 == toX)) && (piece->posY+1*direction==toY) && toPiece->color!=piece->color){
            //hitPiece(toPiece);
            return true;
    }
    return false;
}

bool bishopStepCheck(PiecesList *piece, int toX, int toY, DefDatas *data){
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
        if(findPiece((i*directionX+piece->posX),(i*directionY+piece->posY), data)!=NULL){
            return false;
        }
    }

    return true;
}

bool rookStepCheck(PiecesList *piece, int toX, int toY, DefDatas *data){

    int directionX=(toX-piece->posX<0)?-1:1;
    int directionY=(toY-piece->posY<0)?-1:1;

    if(piece->posX==toX){
        for(int i=1; ((i*directionY) + piece->posY) != toY; i++){
                if(findPiece(piece->posX,(i*directionY) + piece->posY, data)!=NULL){
                    return false;
                }
        }
    }else if(piece->posY==toY){
        for(int i=1; ((i*directionX) + piece->posX) != toX; i++){
                if(findPiece((i*directionX) + piece->posX, piece->posY, data)!=NULL){
                    return false;
                }
        }
    }else{
        return false;
    }
    return true;
}

bool queenStepCheck(PiecesList *piece, int toX, int toY, DefDatas *data){
    if(rookStepCheck(piece, toX, toY, data) || bishopStepCheck(piece, toX, toY, data)){
        return true;
    }
    return false;
}

bool kingStepCheck(PiecesList *piece, int toX, int toY, DefDatas *data){
    int deltaX=toX-piece->posX;
    int deltaY=toY-piece->posY;
    deltaX=(deltaX<0)?deltaX*(-1):deltaX;
    deltaY=(deltaY<0)?deltaY*(-1):deltaY;

    if((deltaX==1 && deltaY==1) || (deltaX==1 && deltaY==0) || (deltaX==0 && deltaY==1) ){
        return true;
    }
    return false;

}

bool knightStepCheck(PiecesList *piece, int toX, int toY, DefDatas *data){
    int deltaX=toX-piece->posX;
    int deltaY=toY-piece->posY;
    deltaX=(deltaX<0)?deltaX*(-1):deltaX;
    deltaY=(deltaY<0)?deltaY*(-1):deltaY;

    if((deltaX==1 && deltaY==2) || (deltaX==2 && deltaY==1)){
        return true;
    }
    return false;

}


bool defaultStepCheck(PiecesList *piece, int toX, int toY,bool check ,DefDatas *data){

    PiecesList *toPiece=findPiece(toX, toY, data);
    char name=piece->name;

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
    if(!check){
    if(toPiece->name=='k'){
        return false;
    }
    }
    }


    switch(name){
    case 'p':
            return pawnStepCheck(piece, toX, toY, data);
        break;

    case 'b':
            return bishopStepCheck(piece, toX, toY, data);
        break;

    case 'r':
            return rookStepCheck(piece, toX, toY, data);
        break;

    case 'h':
            return knightStepCheck(piece, toX, toY, data);
        break;
    case 'q':
            return queenStepCheck(piece, toX, toY, data);
        break;
    case 'k':
            return kingStepCheck(piece, toX, toY, data);
        break;
    default:
            return false;
        break;

    }

}

bool colorCheck(PiecesList *piece, DefDatas *data){
    return (piece->color == (lengthLogList(data)%2==0));
}

bool checkCheck(PiecesList *king, DefDatas *data){

    PiecesList *helper=data->pcListBegin;
        while(helper!=NULL){
            if(helper->color!=king->color && defaultStepCheck(helper, king->posX, king->posY, true,data)){
                return true;
            }
            helper=helper->next;
        }
    return false;
}

/**Vizsgálja hogy a játékot megnyerte-e valamelyik játékos. Visszatérési értéke bool, ami igaz: ha megnyerte valaki, hamis: ha nem*/
bool checkMate(bool color, DefDatas *data){
    PiecesList *helperPiece=data->pcListBegin;

    while(helperPiece!=NULL){
            int fromX;
            int fromY;
    bool help=helperPiece->color;

            if(helperPiece->color==color){
                fromX=helperPiece->posX;
                fromY=helperPiece->posY;
                for(int x=1; x<=8; x++){
                    for(int y=1; y<=8; y++){
                        if(defaultStepCheck(helperPiece, x, y, false, data)){
                            changePieceXY(helperPiece, x, y);

                            if(!checkCheck(findColorKing(color,data),data)){
                                changePieceXY(helperPiece, fromX, fromY);
                                return false;
                            }
                        }
                        changePieceXY(helperPiece, fromX, fromY);
                    }
                }
            }
            helperPiece=helperPiece->next;
        }


    free(helperPiece);
    return true;
}
