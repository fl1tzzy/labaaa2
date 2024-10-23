#include "tree.h"
#include <stdio.h>

int main() {
    BinaryTree* tree = createBinaryTree();
    insertElement(tree, 22);
    insertElement(tree, 16);
    insertElement(tree, 51);
    insertElement(tree, 7);
    insertElement(tree, 19);
    insertElement(tree, 43);
    insertElement(tree, 57);

    FILE* file = fopen("output.txt", "w");
    printTreeZigZag(tree->root, file);
    fclose(file);

    return 0;
}