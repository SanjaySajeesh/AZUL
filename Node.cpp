#include "Node.h"

   Node::Node(Tile data, Node* next){
       this->data = data;
       this->next = next;
   }

   Node::Node(Node& other){
       data = other.data;
       next = new Node(*other.next);
   }
   
   Node::~Node(){
   }
