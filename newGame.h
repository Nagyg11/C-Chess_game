#ifndef NEWGAME_H_INCLUDED
#define NEWGAME_H_INCLUDED


typedef struct StepLogList{
    int fromX;
    int fromY;
    int toX;
    int toY;
    struct StepLogList *next;
}StepLogList;

/**A figurák helye és adatai listákban tárolva. Ha leütnek egy figurát törlésre kerül a listából a bábú*/
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

/**Az új játékhoz szükséges függvényeket meghívja*/
void newGameStart();

/**pieceLoad() függvény segítségével a kezdetben szükséges összes bábut betölti a játék bábuit tartalmazó listába*/
void newGamePices(DefDatas *data);

#endif // NEWGAME_H_INCLUDED
