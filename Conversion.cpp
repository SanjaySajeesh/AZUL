/* Conversion Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The Conversion Class is used to convert enum value to desired characters depending on the need.
 */

//Header Files
#include "Types.h"

Tile charToEnum(char c)
{
    Tile tile = NO_TILE;
    if (c == SYMBOL_YELLOW)
    {
        tile = YELLOW;
    }
    else if (c == SYMBOL_DARKBLUE)
    {
        tile = DARK_BLUE;
    }
    else if (c == SYMBOL_BLACK)
    {
        tile = BLACK;
    }
    else if (c == SYMBOL_LIGHTBLUE)
    {
        tile = LIGHT_BLUE;
    }
    else if (c == SYMBOL_RED)
    {
        tile = RED;
    }
    return tile;
}

char enumToChar(Tile t){
    char tile = ' ';

    if (t == YELLOW)
    {
        tile = SYMBOL_YELLOW;
    }
    else if (t == DARK_BLUE)
    {
        tile = SYMBOL_DARKBLUE;
    }
    else if (t ==BLACK )
    {
        tile = SYMBOL_BLACK ;
    }
    else if (t == LIGHT_BLUE)
    {
        tile = SYMBOL_LIGHTBLUE ;
    }
    else if (t == RED)
    {
        tile = SYMBOL_RED ;
    }
    else if(t==NO_TILE){
        tile = SYMBOL_NOTILE;
    } 
    else if(t == FIRST_PLAYER){
        tile = SYMBOL_FIRST_PLAYER;
    }
    return tile;
}