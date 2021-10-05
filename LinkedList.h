#ifndef A2_LinkedList
#define A2_LinkedList

#include "Node.h"

class LinkedList {
public:
   LinkedList();
   ~LinkedList();
   
   int size();
   void clear();
   Tile get(int i);

   void addFront(Tile data);
   void addBack(Tile data);
   
   void deleteFront();
   void deleteBack();

   Node* getHead();

   void remove(Node* node); //?
private:
   Node* head;
   int length;
};

#endif
