#include <stdio.h>
#include "RBTree.h"

int main() {
    RBTreeRoot *T = RB_Tree_Create();

    int low, high;
    int count = 0;
    printf("Please Input low and high\n");
    while (scanf("%d%d", &low, &high) == 2){
        RBTree n = CreateNode(low, high);
        if (RBTree_Check(T, n))
        {
            RB_Insert(T, n);
            printf("Successful insert! The tree is:\n");
            RBTree_Print(T, T->root, 0);
            count++;
            printf("\n\n");
        }
        else
        {
            printf("There has an interval overleap! Try again!\n\n");
        }
        printf("Please Input low and high\n");
    }
    getchar();
    int i;
    printf("Find key and delete key.\n");
    while (scanf("%d", &i) == 1)
    {
        RBTree x = FindNode(T, i);
        if (x == T->nil)
        {
            printf("Do not have this key\n");
        }
        else
        {
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
            printf("\n");
            RB_Delete(T, x);
            RBTree_Print(T, T->root, 0);
            printf("\n");
            count--;
        }
        printf("\nFind key and delete key.\n");
    }

    for (int i = 0; i<count; ++i)
    {
        RBTree_Print(T, T->root, 0);
        RB_Delete(T,T->root);
        printf("\n");
    }
    return 0;
}