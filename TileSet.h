#ifndef TILESET
#define TILESET
#include <string> 
#include <vector>
#include "Types.h"


class TileBag{};

#define MAX_TILESET_SIZE    5

class TileSet {
public:
   TileSet(int size);
   ~TileSet();

   void addTile(Tile tile);
   bool isFull();
  
   Tile getTile();
   int getCurrentSize();
   void clear();
   std::string print();
   bool checkValid(Tile tile);
   int pushTiles(int row);

   std::vector<Tile> pushedTiles;
private:
   int current_size;
   Tile tile;
   int size;


   bool isPushed(Tile tile);
   
};

#endif // TILESET
