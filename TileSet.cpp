/* TileSet Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The TileSet makes use of the tile enum found in the Types class
 *to form the tiles needed for the mosaic and for the factories.
 *It contains functions that are necessary for the manipulation of the tile.
 */

//Header Files
#include "TileSet.h"

TileSet::TileSet(int size){
    this->tile= NO_TILE;
    this->size = size;

}

TileSet::~TileSet(){
    
}

// add a tile to the array
void TileSet::addTile(Tile tile){
    if(current_size == 0){
        this->tile = tile;
    }
    ++current_size;

}

// return true if the array(tileset) is full
bool TileSet::isFull(){
    return this->current_size == this->size;
}

//return if the move is valid
bool TileSet::checkValid(Tile tile){
    return !isFull() && (current_size == 0 || this->tile == tile) && !isPushed(tile);
}

//check if the Color of the tile is already in the mosaic
bool TileSet::isPushed(Tile tile){
    bool pushed = false;
    for(Tile t:this->pushedTiles){
        if (t == tile){
            pushed = true;
        }
    }
    return pushed;
}

//return a string containing information of a TileSet
std::string TileSet::print(){
    std::string print;

    for(int i = 0; i < WALL_DIM; ++i){
        if(i < WALL_DIM - size){
            print += " ";
        }else if(i >= WALL_DIM - current_size){
            print += enumToChar(tile);
        }else {
            print += SYMBOL_NOTILE;
        }
        print += " ";
    }

    return print;
}

// return the tile type
Tile TileSet::getTile(){
    
    return tile;
}

// return the current size of the TileSet
int TileSet::getCurrentSize(){
    
    return current_size;
}

// return the index of the tile whr the Tile shall be pushed to
int TileSet::pushTiles(int row){
    int returnValue = (this->tile + row) % WALL_DIM;

    //register the tile as pushed
    this->pushedTiles.push_back(this->tile);

    //clear the patternLine
    this->clear();
    return returnValue;
 
}

void TileSet::clear(){
    this->current_size = 0;
    this->tile = NO_TILE;
}
