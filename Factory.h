#ifndef A2_Factory
#define A2_Factory

#include <string>
#include <vector>
#include "LinkedList.h"
#include "Types.h"

class Factory {
public:
    Factory();
    // Factory(int index);

    ~Factory();
    std::string printTiles();
    std::vector<Tile> getTile(int index, Tile tile_type); // return an array of tiles 
    void createFactory(Tile* tiles);
    // bool hasFirstPlayer(); // return if factory owns first player tile
    bool isEmpty();
    bool checkValid(Tile tile, int factoryIndex);
private:
    // int index;
    // LinkedList* factories[FACTORY_NUM];
    std::vector<Tile> centreTable[TILE_LEN];
    std::vector<Tile> factoryPlate[FACTORY_NUM];
    bool firstPlayer; 
};

#endif // A2_Factory