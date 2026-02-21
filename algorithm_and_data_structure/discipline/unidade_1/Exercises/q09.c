#include <stdio.h>
#include <stdlib.h>

#include "../../data_structures/include/binary_search_tree.h"

int main()
{
    int list1[] = {10, 5, 3, 7, 15, 12, 18};

    Node *tree = createTree(list1, 7, ITER);

    traverse(tree, PRE, printNode);
    printf("\n");
    traverse(tree, IN, printNode);
    printf("\n");
    traverse(tree, POS, printNode);
    printf("\n");

    freeTree(tree);

    return 0;
}
