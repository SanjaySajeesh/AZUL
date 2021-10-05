#ifndef A2_Player
#define A2_Player
#include <string>
#include "LinkedList.h"
#include "TileSet.h"

class Player {
public:
    Player(std::string name);
    ~Player();

    int getScore();
    int get_Id();
    

    std::vector<Tile> wallTiling();
    bool factoryOffer(Tile tile, int row);
    std::string printMosaic();
    std::string getName();
    bool checkValid(Tile tile, int row);

    bool firstPlayer;
    
private:
    std::string name;      
    int score;
    int Id;
    int brokenLength;
    TileSet** patternLine;
    Tile wall[WALL_DIM][WALL_DIM];
    Tile brokenTile[MAX_FLOORLINE]; 

    void addScore(int row, int col);
    int calcScoreHorizontal(int row, int col, int colS);
    int calcScoreVertical(int row, int col, int rowS);
    int deductBrokenPoints(std::vector<Tile> &returnTiles);
};

#endif // A2_Player