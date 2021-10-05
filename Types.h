/* Types Class Description
 *Author:Sara Imamura Sanjay Sajeesh Krishnan Kee Chew Huang
 *The Types class contains all the macros needed for the game's functioning.
 */

#ifndef TYPES
#define TYPES 

enum Tile {
    DARK_BLUE,
    YELLOW,
    RED,
    BLACK,
    LIGHT_BLUE,
    
    NO_TILE,
    FIRST_PLAYER
};
enum Command{
    NEWGAME,
    LOADGAME,
    TESTGAME
};
#define USERINPUT           "> "
#define ERROR               "Invalid Input"

#define TILEBAG_SIZE        100
#define FACTORY_SIZE        4

#define NUM_OF_FACTORIES    6
#define NUM_OF_TILES        20
#define END_ROUNDS          5

#define WALL_DIM            5
#define MAX_FLOORLINE       7
#define NUM_OF_PLAYERS      2

#define FACTORY_NUM         5 // total factory plate size available
#define FACTORY_PLATE       4 // max capacity for tiles to be store in each factory plate
#define TILE_LEN            5 //total number of tile colour variation
#define CENTRETABLE         0 // index of centre table in factory

// defines for symbols
#define SYMBOL_FIRST_PLAYER        'F'

#define SYMBOL_RED          'R'
#define SYMBOL_YELLOW       'Y'
#define SYMBOL_DARKBLUE     'B'
#define SYMBOL_LIGHTBLUE    'L'
#define SYMBOL_BLACK        'U'
#define SYMBOL_NOTILE       '.'


#define RELATIVE_PATH "SavedFiles/"
//this is a random seed
#define DEFAULT_SEED 99
Tile charToEnum(char c);
char enumToChar(Tile t);
#endif
