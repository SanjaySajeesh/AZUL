/* Player Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The Player class is used to setup a player and to validate
 *scores and possible identify deductions in the score.
 */

#include "Player.h"

Player::Player(std::string name)
{
    this->name = name;
    patternLine = new TileSet * [WALL_DIM];
    for (int i = 0; i < WALL_DIM; ++i)
    {
        patternLine[i] = new TileSet(i + 1);
        for (int j = 0; j < WALL_DIM; ++j)
        {
            wall[i][j] = NO_TILE;
        }
    }
    this->brokenLength = 0;
    this->score = 0;
    this->firstPlayer = false;

}

Player::~Player()
{
    for(int i = 0; i < WALL_DIM; ++i){
        delete this->patternLine[i];
    }
    delete [] this->patternLine;
}

// return the score of the player
int Player::getScore()
{
    return this->score;
}

// add a tile to the pattern line or broken tile when the player collects
// a tile from the Factory
bool Player::factoryOffer(Tile tile, int row)
{
   bool success = true;

   //first player tile goes to the broken line directly
    if(tile == FIRST_PLAYER){
        brokenTile[brokenLength] = tile;
        ++brokenLength;
        firstPlayer = true;
    }else{
        // the player has the option to place the tiles in broken line if they have no possible move
        if (row == 0 )
        {
            if(brokenLength < MAX_FLOORLINE){
                brokenTile[brokenLength] = tile;
                ++brokenLength;
            }else {
                success = false;
            }
        }
        else
        {
            //place the tile on desired patternLine if the patternLine is not full, else goes to the broken line
            TileSet *tiles = this->patternLine[row - 1];
            if (!tiles->isFull())
            {
                tiles->addTile(tile);
            }
            else
            {
                brokenTile[brokenLength] = tile;
                ++brokenLength;
            }
        }
    }
    return success;
}

// Push completed patternLine to the mosaic, calculate the score at the end of each round, return discarded tiles
std::vector<Tile> Player::wallTiling()
{
    std::vector<Tile> discardedTiles;
    for (int i = 0; i < WALL_DIM; ++i)
    {
        TileSet *tiles = this->patternLine[i];
        Tile tile = tiles->getTile();
        
        //if the patternLine is full, push to the mosaic
        if (tiles->isFull())
        {
            for(int i = 0; i < tiles->getCurrentSize() - 1; ++i){
                discardedTiles.push_back(tile);
            }
            int col = tiles->pushTiles(i);
            this->wall[i][col] = tile;
            addScore(i,col);
        }
    }
    //deduct points from tiles in brokenLine
    score -= deductBrokenPoints(discardedTiles);

    // move tiles from the pattern line to the wall
    // add unused tiles to the tilebag
    // calculate score
    return discardedTiles;
}

//return a string containing details of the Player's mosaic
std::string Player::printMosaic()
{
    //TODO
    std::string mosaic = "";
    for (int i = 0; i < WALL_DIM; ++i)
    {
        mosaic = mosaic + std::to_string(i + 1) + ": " + this->patternLine[i]->print() + "|| ";
        for (int j = 0; j < WALL_DIM; ++j)
        {
            mosaic = mosaic + enumToChar(wall[i][j]) + " ";
        }
        mosaic += "\n";
    }
    mosaic += "broken: ";
    for (int i = 0; i < brokenLength; ++i)
    {
        mosaic = mosaic + enumToChar(brokenTile[i]) + " ";
    }
    return mosaic;
}

//return if the move is valid
bool Player::checkValid(Tile tile, int row)
{
    bool valid = false;
    if (row == 0)
    {
        valid = true;
    }
    else
    {
        valid = this->patternLine[row - 1]->checkValid(tile);
    }

    return valid;
}

std::string Player::getName()
{
    return this->name;
}

// this is a recursive function which calculate the score in vertical line
int Player::calcScoreHorizontal(int row, int col, int colS){
    int returnVal = 0;
    // base case
    if(this->wall[row][col] == NO_TILE){
        returnVal = 0;
    }else{
        returnVal ++;
       if(col > 0 && col <= colS ){
            // go left
            returnVal += calcScoreHorizontal(row, col-1, colS);
        }
        if (col < WALL_DIM-1 && col >= colS ){
            // go right
            returnVal +=calcScoreHorizontal(row, col+1,colS);
        }
    }
    return returnVal;
    // recursive case
}

// this is a recursive function which calculate the score in vertical line
int Player::calcScoreVertical(int row, int col, int rowS){
    int returnVal = 0;
    // base case
    if(this->wall[row][col] == NO_TILE){
        returnVal = 0;
    }else{
        returnVal ++;
       if(row > 0  && row <= rowS){
            // go up
            returnVal += calcScoreVertical(row-1, col, rowS);
        }
        if (row < WALL_DIM-1 && row >= rowS){
            // go down
            returnVal +=calcScoreVertical(row+1, col, rowS);
        }
    }
    return returnVal;
    // recursive case
}

void Player::addScore(int row, int col){
    int horizontalPoint = calcScoreHorizontal(row, col, col);
    int verticalPoint = calcScoreVertical(row, col, row);

    // if there is no connected tiles add 1 to score
    if(horizontalPoint == 1 && verticalPoint == 1){
        score += 1;
    }
    // if there is only connected tiles in vertical line
    else if(horizontalPoint == 1){
        score += verticalPoint;
    }
    // if there is only connected tiles in horizontal line
    else if(verticalPoint == 1){
        score += horizontalPoint;
    }
    // if there is connected tiles in both direction
    else{
        score += horizontalPoint + verticalPoint;
    }
}

//return how many points shall the player be deducted
int Player::deductBrokenPoints(std::vector<Tile> & discardedTiles){
    int returnValue = 0;
    for(int i = 0; i< this->brokenLength; ++ i){
        if(i < 3){
            returnValue += 1;
        }else if(i < 6){    
            returnValue += 2;
        }else{
            returnValue += 3;
        }
        if(brokenTile[i] != FIRST_PLAYER){
            discardedTiles.push_back(brokenTile[i]);
        }
        
        brokenTile[i] = NO_TILE;
    }
    brokenLength = 0;
    return returnValue;
}