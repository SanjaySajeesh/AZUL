/*Factory Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The Factory Class is resposible for the creation of factories for players to choose from.
 *It also runs multiple checks to determine the validity of the move and manipulates the TileSet class
 *to move the tiles into the Mosaic.
 */

//Header Files
#include "Factory.h"
#include "LinkedList.h"
#include <string>

Factory::Factory() {
    this->firstPlayer = true;
}

Factory::~Factory()
{

}

// this returns a vector of tiles to be "moved" to player's mosaic    
std::vector<Tile> Factory::getTile(int index, Tile tile_type){
    // this is a vector tiles that will contains tiles of same tile colour
    std::vector<Tile> retTiles;
    
    // if tiles are chosen from centre table
    if(index == CENTRETABLE){
        // check if center of table was chosen for very first time in 
        // the round by the player
        if(firstPlayer == true){
            firstPlayer = false;
            retTiles.push_back(FIRST_PLAYER);
        }

        // pick tiles of specified tile colour from center of tables
        std::vector<Tile>* copy = nullptr;
        copy = &centreTable[tile_type];
   
        for (Tile t : (*copy)){
            //std::cout << t << std::endl;
            retTiles.push_back(t);
        }
        (*copy).clear();

    }
    // if tiles are chosen from factory plates
    else {
        for(Tile t : factoryPlate[index-1]){
            if(t == tile_type){
                retTiles.push_back(t);
            }else{
                centreTable[t].push_back(t);
            }
        }
        factoryPlate[index-1].clear();
    }
    return retTiles;
}  

// intialise factory plates
void Factory::createFactory(Tile* tiles){
    int size = FACTORY_NUM*FACTORY_PLATE;
    for(int i =0; i< size; i++){
        factoryPlate[i/FACTORY_PLATE].push_back(tiles[i]);
    }
    firstPlayer = true;
}

// check if the factory is empty
bool Factory::isEmpty(){
    bool empty = true;
    for(int i = 0; i< TILE_LEN; i++){
        if(!centreTable[i].empty()){
            empty = false;
        }
    }
    for(int i = 0; i<FACTORY_NUM; i++){
        if(!factoryPlate[i].empty()){
            empty = false;
        }
    }
    return empty;
}

// string formatted for printing out factory
std::string Factory::printTiles()
{
    std::string result;

    // represents centre of table
    result += "0: ";
    if(firstPlayer){
        result += SYMBOL_FIRST_PLAYER;
        result += " ";
    }
    for(int i = 0; i < TILE_LEN; i++){
        for(Tile tile : centreTable[i]){
            result = result + enumToChar(tile) + " ";
        }
    }
    // represents factory plate
    for(int i = 0; i < FACTORY_NUM; i++){
        // int index = i+1;
        result += "\n" + std::to_string(i+1)+ ": ";

        for(Tile tile : factoryPlate[i]){
            result = result + enumToChar(tile) + " ";

        }
    }
    return result;
}

// this method checks whether the "turn" command parameter is 
// valid or not 
bool Factory::checkValid(Tile tile, int factoryIndex){
    bool valid = false;
    if(tile != NO_TILE && tile != FIRST_PLAYER){
        // checks the validity in the case of centre table
        if(factoryIndex == CENTRETABLE){
            if(this->centreTable[tile].size() > 0){
                valid = true;
            }
        }
        // checks the validity in the case of factory plate
        else{
            for(Tile t: this->factoryPlate[factoryIndex-1]){
                if(t == tile){
                    valid = true;
                }
            }
        }
    }
    return valid;
}