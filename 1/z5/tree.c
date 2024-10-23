#include "tree.h"
#include "queue_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Функция для создания нового узла
TreeNode* newNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Функция для добавления элемента в полное бинарное дерево
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL)
        return newNode(data);

    if (root->left == NULL) {
        root->left = insert(root->left, data);
    } else if (root->right == NULL) {
        root->right = insert(root->right, data);
    } else {
        root->left = insert(root->left, data);
    }
    return root;
}

// Функция для поиска элемента в дереве
bool search(TreeNode* root, int data) {
    if (root == NULL)
        return false;

    if (root->data == data)
        return true;

    return search(root->left, data) || search(root->right, data);
}

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFullBinaryTree(TreeNode* root) {
    if (root == NULL)
        return true;

    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        return false;

    return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);
}

// Функция для вывода дерева (обход в прямом порядке)
void printTree(TreeNode* root, FILE* file) {
    if (root == NULL)
        return;

    fprintf(file, "%d ", root->data);
    printTree(root->left, file);
    printTree(root->right, file);
}

// Функция для вывода дерева "змейкой"
void printTreeZigZag(TreeNode* root, FILE* file) {
    if (root == NULL) return;

    TreeQueue currentLevel;
    TreeQueue nextLevel;
    bool leftToRight = true;

    init_tree_queue(&currentLevel);
    init_tree_queue(&nextLevel);

    push_tree_queue(&currentLevel, root);

    while (!isEmptyTreeQueue(&currentLevel)) {
        TreeNode* node = pop_tree_queue(&currentLevel);

        fprintf(file, "%d ", node->data);

        if (leftToRight) {
            if (node->left) push_tree_queue(&nextLevel, node->left);
            if (node->right) push_tree_queue(&nextLevel, node->right);
        } else {
            if (node->right) push_tree_queue(&nextLevel, node->right);
            if (node->left) push_tree_queue(&nextLevel, node->left);
        }

        if (isEmptyTreeQueue(&currentLevel)) {
            leftToRight = !leftToRight;
            TreeQueue temp = currentLevel;
            currentLevel = nextLevel;
            nextLevel = temp;
            fprintf(file, "\n");
        }
    }
}

// Функция для создания нового дерева
BinaryTree* createBinaryTree() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));
    tree->root = NULL;
    return tree;
}

// Функция для добавления элемента в дерево
void insertElement(BinaryTree* tree, int data) {
    tree->root = insert(tree->root, data);
}

// Функция для поиска элемента в дереве
bool searchElement(BinaryTree* tree, int data) {
    return search(tree->root, data);
}

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFull(BinaryTree* tree) {
    return isFullBinaryTree(tree->root);
}

// Функция для вывода дерева
void print(BinaryTree* tree, FILE* file) {
    printTree(tree->root, file);
    fprintf(file, "\n");
}