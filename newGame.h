#ifndef NEWGAME_H_INCLUDED
#define NEWGAME_H_INCLUDED


typedef struct StepLogList{
    int fromX;
    int fromY;
    int toX;
    int toY;
    struct StepLogList *next;
}StepLogList;

/**A figur�k helye �s adatai list�kban t�rolva. Ha le�tnek egy figur�t t�rl�sre ker�l a list�b�l a b�b�*/
typedef struct PiecesList{
    char name;
    bool color;
    int posX;
    int posY;
    struct PiecesList *next;
}PiecesList;


typedef struct DefDatas{
    PiecesList *pcListBegin;
    StepLogList *stepListBegin;
    char *names;
    bool gameEnd;
}DefDatas;

/**Az �j j�t�khoz sz�ks�ges f�ggv�nyeket megh�vja*/
void newGameStart();

/**pieceLoad() f�ggv�ny seg�ts�g�vel a kezdetben sz�ks�ges �sszes b�but bet�lti a j�t�k b�buit tartalmaz� list�ba*/
void newGamePices(DefDatas *data);

#endif // NEWGAME_H_INCLUDED
