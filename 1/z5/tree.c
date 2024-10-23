#include "tree.h"          
#include "queue_tree.h"    
#include <stdio.h>         
#include <stdlib.h>        
#include <stdbool.h>       
// Функция для создания нового узла
TreeNode* newNode(int data) {
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));  // Выделяем память для нового узла
    node->data = data;                                    // Устанавливаем данные узла
    node->left = NULL;                                    // Устанавливаем указатель на левого потомка в NULL
    node->right = NULL;                                   // Устанавливаем указатель на правого потомка в NULL
    return node;                                          // Возвращаем указатель на новый узел
}

// Функция для добавления элемента в полное бинарное дерево
TreeNode* insert(TreeNode* root, int data) {
    if (root == NULL)                                     // Если дерево пустое
        return newNode(data);                             // Создаем новый узел и возвращаем его

    if (root->left == NULL) {                             // Если левое поддерево пустое
        root->left = insert(root->left, data);            // Добавляем элемент в левое поддерево
    } else if (root->right == NULL) {                     // Если правое поддерево пустое
        root->right = insert(root->right, data);          // Добавляем элемент в правое поддерево
    } else {                                              // Если у корня есть оба потомка
        root->left = insert(root->left, data);            // Добавляем элемент в левое поддерево
    }
    return root; // Возвращаем корень дерева
}

// Функция для поиска элемента в дереве
bool search(TreeNode* root, int data) {
    if (root == NULL)                                     // Если дерево пустое
        return false;                                     // Элемент не найден

    if (root->data == data)                               // Если данные узла совпадают с искомым значением
        return true;                                      // Элемент найден

    return search(root->left, data) || search(root->right, data);  // Рекурсивный поиск в левом и правом поддеревьях
}

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFullBinaryTree(TreeNode* root) {
    if (root == NULL)                                     // Если дерево пустое
        return true;                                      // Считаем его полным

    if ((root->left == NULL && root->right != NULL) || (root->left != NULL && root->right == NULL))
        return false;                                     // Если узел имеет только одного потомка, дерево не полное

    return isFullBinaryTree(root->left) && isFullBinaryTree(root->right);  // Рекурсивная проверка левого и правого поддеревьев
}

// Функция для вывода дерева (обход в прямом порядке)
void printTree(TreeNode* root, FILE* file) {
    if (root == NULL)                                     // Если дерево пустое
        return;                                           // Выходим из функции

    fprintf(file, "%d ", root->data);                     // Выводим данные узла
    printTree(root->left, file);                          // Рекурсивный вывод левого поддерева
    printTree(root->right, file);                         // Рекурсивный вывод правого поддерева
}

// Функция для вывода дерева "змейкой"
void printTreeZigZag(TreeNode* root, FILE* file) {
    if (root == NULL) return;                             // Если дерево пустое, выходим из функции

    TreeQueue currentLevel;                               // Очередь для хранения узлов текущего уровня
    TreeQueue nextLevel;                                  // Очередь для хранения узлов следующего уровня
    bool leftToRight = true;                              // Флаг для определения порядка вывода узлов

    init_tree_queue(&currentLevel);                       // Инициализируем очередь текущего уровня
    init_tree_queue(&nextLevel);                          // Инициализируем очередь следующего уровня

    push_tree_queue(&currentLevel, root);                 // Добавляем корень в очередь текущего уровня

    while (!isEmptyTreeQueue(&currentLevel)) {            // Пока очередь текущего уровня не пуста
        TreeNode* node = pop_tree_queue(&currentLevel);   // Извлекаем узел из очереди текущего уровня

        fprintf(file, "%d ", node->data);                 // Выводим данные узла

        if (leftToRight) {                                // Если вывод слева направо
            if (node->left) push_tree_queue(&nextLevel, node->left);    // Добавляем левого потомка в очередь следующего уровня
            if (node->right) push_tree_queue(&nextLevel, node->right);  // Добавляем правого потомка в очередь следующего уровня
        } else {                                          // Если вывод справа налево
            if (node->right) push_tree_queue(&nextLevel, node->right);  // Добавляем правого потомка в очередь следующего уровня
            if (node->left) push_tree_queue(&nextLevel, node->left);    // Добавляем левого потомка в очередь следующего уровня
        }

        if (isEmptyTreeQueue(&currentLevel)) {            // Если текущий уровень закончился
            leftToRight = !leftToRight;                   // Меняем порядок вывода для следующего уровня
            TreeQueue temp = currentLevel;                // Меняем очереди местами
            currentLevel = nextLevel;
            nextLevel = temp;
            fprintf(file, "\n");                          // Выводим пустую строку для разделения уровней
        }
    }
}

// Функция для создания нового дерева
BinaryTree* createBinaryTree() {
    BinaryTree* tree = (BinaryTree*)malloc(sizeof(BinaryTree));  // Выделяем память для нового дерева
    tree->root = NULL;                                       // Устанавливаем корень дерева в NULL
    return tree;                                             // Возвращаем указатель на новое дерево
}

// Функция для добавления элемента в дерево
void insertElement(BinaryTree* tree, int data) {
    tree->root = insert(tree->root, data);                   // Вызов функции добавления элемента с корнем дерева
}

// Функция для поиска элемента в дереве
bool searchElement(BinaryTree* tree, int data) {
    return search(tree->root, data);                         // Вызов функции поиска элемента с корнем дерева
}

// Функция для проверки, является ли дерево полным бинарным деревом
bool isFull(BinaryTree* tree) {
    return isFullBinaryTree(tree->root);                     // Вызов функции проверки с корнем дерева
}

// Функция для вывода дерева
void print(BinaryTree* tree, FILE* file) {
    printTree(tree->root, file);                             // Вызов функции вывода дерева с корнем дерева
    fprintf(file, "\n");                                     // Вывод пустой строки для разделения
}
