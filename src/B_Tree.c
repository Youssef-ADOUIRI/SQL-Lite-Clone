#include "B_Tree.h"

B_Tree* newBTree(){
    B_Tree* bt = (B_Tree*)malloc(sizeof(B_Tree));
    bt->order = DefaultOrder;
    bt->root = (B_Tree_Node*)malloc(sizeof(B_Tree_Node));
    bt->root->isRoot = true ;
    bt->root->index = 0 ;
    return bt;
}

B_Tree_Node* newNode(int id , B_Tree_Node * parent){
    
}