//
// Created by YxGuo on 2019/11/15.
//

#ifndef LAB2_RBTREE_H
#define LAB2_RBTREE_H

#define RED 0
#define BLACK 1

#include <stdbool.h>
typedef struct {
    int low,high;
}ElementType;


typedef struct RBTreeNode {
    int color;
    ElementType interval;
    int key;
    int size;
    struct RBTreeNode *left, *right, *parent;
}RBTreeNode, *RBTree;

typedef struct{
    RBTree root;
    RBTree nil;
}RBTreeRoot;

// functions declaration
// operate of RBTree
void RB_Right_Rotate (RBTreeRoot *T, RBTree x);
void RB_Left_Rotate (RBTreeRoot *T, RBTree x);
void RB_Insert (RBTreeRoot *T, RBTree z);
void RB_Insert_Fixup (RBTreeRoot *T, RBTree z);
void RB_Transplant (RBTreeRoot *T, RBTree u, RBTree v);
void RB_Delete (RBTreeRoot *T, RBTree z);
void RB_Delete_Fixup (RBTreeRoot *T, RBTree x);

//other functions
RBTreeRoot *RB_Tree_Create(void);
RBTree Tree_Minium (RBTreeRoot *T, RBTree x);

void RBTree_Print(RBTreeRoot *T, RBTree x, int depth);
RBTreeNode *CreateNode(int low, int high);
int max3(int x, int y, int z);
bool RBTree_Check(RBTreeRoot *T, RBTree i);

bool overleap(RBTree a, RBTree b);
RBTree FindNode(RBTreeRoot *T, int key);

#endif //LAB2_RBTREE_H
