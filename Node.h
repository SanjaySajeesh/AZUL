#ifndef A2_Node
#define A2_Node
#include "Types.h"
#include "TileSet.h"

class Node
{
public:
   Node(Tile data, Node *next);
   Node(Node &other);
   ~Node();
   
   Tile data;
   Node *next;

};
#endif