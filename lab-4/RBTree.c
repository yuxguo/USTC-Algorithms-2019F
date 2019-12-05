//
// Created by YxGuo on 2019/11/15.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "RBTree.h"

void RB_Right_Rotate (RBTreeRoot *T, RBTree x)
{
    RBTree y = x->left;
    x->left = y->right;
    if (y->right != T->nil)
    {
        y->right->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->right = x;
    x->parent = y;
    /////////////////////////
    x->size = max3(x->interval.high, x->left->size, x->right->size);
    y->size = max3(y->interval.high, y->left->size, y->right->size);

}


void RB_Left_Rotate (RBTreeRoot *T, RBTree x)
{
    RBTree y = x->right;
    x->right = y->left;
    if (y->left != T->nil)
    {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == T->nil)
    {
        T->root = y;
    }
    else if (x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;

    /////////////////////////
    x->size = max3(x->interval.high, x->left->size, x->right->size);
    y->size = max3(y->interval.high, y->left->size, y->right->size);
}


void RB_Insert (RBTreeRoot *T, RBTree z)
{
    RBTree y = T->nil;
    RBTree x = T->root;
    while (x != T->nil)
    {
        y = x;
        if (y->size < z->interval.high)
        {
            y->size = z->interval.high;
        }
        if (z->key < x->key)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    z->parent = y;
    if (y == T->nil)
    {
        T->root = z;
    }
    else if (z->key < y->key)
    {
        y->left = z;
    }
    else
    {
        y->right = z;
    }
    z->left = T->nil;
    z->right = T->nil;
    z->color = RED;

    /////////////////////////
    z->size = z->interval.high;
    RBTree tmp = z->parent;
    while (tmp != T->nil)
    {
        tmp->size = max3(tmp->interval.high, tmp->left->size, tmp->right->size);
        tmp = tmp->parent;
    }
    ////////////////////////
    RB_Insert_Fixup(T, z);

}


void RB_Insert_Fixup (RBTreeRoot *T, RBTree z)
{
    while (z->parent->color == RED)
    {
        if (z->parent == z->parent->parent->left)
        {
            RBTree y = z->parent->parent->right;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->right)
                {
                    z = z->parent;
                    RB_Left_Rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RB_Right_Rotate(T, z->parent->parent);
            }
        }
        else
        {
            RBTree y = z->parent->parent->left;
            if (y->color == RED)
            {
                z->parent->color = BLACK;
                y->color = BLACK;
                z->parent->parent->color = RED;
                z = z->parent->parent;
            }
            else
            {
                if (z == z->parent->left)
                {
                    z = z->parent;
                    RB_Right_Rotate(T, z);
                }
                z->parent->color = BLACK;
                z->parent->parent->color = RED;
                RB_Left_Rotate(T, z->parent->parent);
            }
        }
    }
    T->root->color = BLACK;
}


void RB_Transplant (RBTreeRoot *T, RBTree u, RBTree v)
{
    if (u->parent == T->nil)
    {
        T->root = v;
    }
    else if (u == u->parent->left)
    {
        u->parent->left = v;
    }
    else
    {
        u->parent->right = v;
    }
    v->parent = u->parent;
}


void RB_Delete (RBTreeRoot *T, RBTree z)
{
    //////////////////////////////
    z->size = 0;
    RBTree tmp = z;
    while (tmp != T->nil)
    {
        tmp->size = max3(tmp->interval.high, tmp->left->size, tmp->right->size);
        tmp = tmp->parent;
    }
    //////////////////////////////
    RBTree y = z;
    int y_orig_color = y->color;
    RBTree x;
    if (z->left == T->nil)
    {
        x = z->right;
        RB_Transplant(T, z, z->right);
    }
    else if (z->right == T->nil)
    {
        x = z->left;
        RB_Transplant(T, z, z->left);
    }
    else
    {
        y = Tree_Minium(T, z->right);
        y_orig_color = y->color;
        x = y->right;
        if (y->parent == z)
        {
            x->parent = y;
        }
        else
        {
            RB_Transplant(T, y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(T, z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    if (y_orig_color == BLACK)
    {
        RB_Delete_Fixup(T, x);
    }
    free(z);

}


void RB_Delete_Fixup (RBTreeRoot *T, RBTree x)
{
    while ((x != T->root) && (x->color == BLACK))
    {
        if (x == x->parent->left)
        {
            RBTree w = x->parent->right;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RB_Left_Rotate(T, x->parent);
                w = x->parent->right;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->right->color == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    RB_Right_Rotate(T, w);
                    w = x->parent->right;
                }
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                RB_Left_Rotate(T, x->parent);
                x = T->root;
            }
        }
        else
        {
            RBTree w = x->parent->left;
            if (w->color == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                RB_Right_Rotate(T, x->parent);
                w = x->parent->left;
            }
            if ((w->left->color == BLACK) && (w->right->color == BLACK))
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (w->left->color == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    RB_Left_Rotate(T, w);
                    w = x->parent->left;
                }
                w->color = w->parent->color;
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RB_Right_Rotate(T, x->parent);
                x = T->root;
            }
        }
    }
    x->color = BLACK;
}

RBTreeRoot *RB_Tree_Create(void)
{
    RBTreeRoot *T = (RBTreeRoot *)malloc(sizeof(RBTreeRoot));
    T->nil = (RBTreeNode *)malloc(sizeof(RBTreeNode));
    T->nil->left = T->nil;
    T->nil->right = T->nil;
    T->nil->parent = T->nil;
    T->nil->color = BLACK;
    T->nil->key = -1;
    T->nil->size = 0;
    T->root = T->nil;
    return T;
}

RBTree Tree_Minium (RBTreeRoot *T, RBTree x)
{
    RBTree y = x;
    while (y->left != T->nil)
    {
        y = y->left;
    }
    return y;
}

int max3(int x, int y, int z)
{
    int result;
    int t;
    t = x>y ? x:y;
    result = t>z ? t:z;
    return result;
}

void RBTree_Print(RBTreeRoot *T, RBTree x, int depth)
{
    if (x == T->nil)
    {
        return;
    }
    for (int i = 0; i<depth;++i)
    {
        printf("    ");
    }
    if (x->color == RED)
    {
        printf("\e[01;31m key: %d, color: %s, size: %d, [%d, %d] \e[0m\n",
               x->key, "RED", x->size, x->interval.low, x->interval.high);
    }
    else
    {
        printf("\e[01;34m key: %d, color: %s, size: %d, [%d, %d] \e[0m\n",
               x->key, "BLACK", x->size, x->interval.low, x->interval.high);
    }
    for (int i = 0; i<depth;++i)
    {
        printf("    ");
    }
    printf("left: {\n");
    RBTree_Print(T, x->left, depth+1);
    for (int i = 0; i<depth;++i)
    {
        printf("    ");
    }
    printf("}\n");
    for (int i = 0; i<depth;++i)
    {
        printf("    ");
    }
    printf("right: {\n");
    RBTree_Print(T, x->right, depth+1);
    for (int i = 0; i<depth;++i)
    {
        printf("    ");
    }
    printf("}\n");
}
RBTreeNode *CreateNode(int low, int high)
{
    RBTreeNode *n = (RBTreeNode *)malloc(sizeof(RBTreeNode));
    n->interval.high = high;
    n->interval.low = low;
    n->size = high;
    n->key = low;
}
bool RBTree_Check(RBTreeRoot *T, RBTree i)
{
    RBTree x = T->root;
    while (x != T->nil && !overleap(i, x))
    {
        if (x->left != T->nil && x->left->size >= i->interval.low)
        {
            x = x->left;
        }
        else
        {
            x = x->right;
        }
    }
    if (x == T->nil)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool overleap(RBTree a, RBTree b)
{
    if (a->interval.low > b->interval.high || a->interval.high < b->interval.low)
    {
        return false;
    }
    else
    {
        return true;
    }
}
RBTree FindNode(RBTreeRoot *T, int key)
{
    RBTree x = T->root;

    while (x != T->nil)
    {
        if (x->key < key)
        {
            x = x->right;
        }
        else if (x->key == key)
        {
            break;
        }
        else
        {
            x = x->left;
        }
    }
    return x;
}