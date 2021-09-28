#ifndef DEF_B_Tree
#define DEF_B_Tree

#include "structures.h"

#define DefaultOrder 3


typedef struct 
{
    size_t order;
    B_Tree_Node* root;
}B_Tree;


B_Tree* newBTree();

B_Tree_Node* newNode(int id , B_Tree_Node * parent);


typedef struct 
{
    bool isRoot;
    int index;
    Page * page; // null par defaut
    
}B_Tree_Node;






#endif