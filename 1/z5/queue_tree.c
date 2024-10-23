#include "queue_tree.h"
#include <stdlib.h>

// Функция для инициализации очереди
void init_tree_queue(TreeQueue* q) {
    q->front = NULL;
    q->rear = NULL;
}

// Функция для добавления элемента в конец очереди
void push_tree_queue(TreeQueue* q, TreeNode* node) {
    TreeNodeQueue* newNode = (TreeNodeQueue*)malloc(sizeof(TreeNodeQueue));
    newNode->node = node;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
}

// Функция для удаления элемента из начала очереди
TreeNode* pop_tree_queue(TreeQueue* q) {
    if (q->front == NULL) {
        return NULL;
    }

    TreeNodeQueue* temp = q->front;
    TreeNode* node = temp->node;

    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
    return node;
}

// Функция для проверки, является ли очередь пустой
int isEmptyTreeQueue(TreeQueue* q) {
    return (q->front == NULL);
}