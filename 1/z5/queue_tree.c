#include "queue_tree.h" 
#include <stdlib.h>      

// Функция для инициализации очереди
void init_tree_queue(TreeQueue* q) {
    q->front = NULL;  // Устанавливаем указатель на начало очереди в NULL
    q->rear = NULL;   // Устанавливаем указатель на конец очереди в NULL
}

// Функция для добавления элемента в конец очереди
void push_tree_queue(TreeQueue* q, TreeNode* node) {
    TreeNodeQueue* newNode = (TreeNodeQueue*)malloc(sizeof(TreeNodeQueue));  // Выделяем память для нового узла очереди
    newNode->node = node;  // Присваиваем указатель на узел дерева новому узлу очереди
    newNode->next = NULL;  // Устанавливаем указатель на следующий узел в NULL

    if (q->rear == NULL) {  // Если очередь пуста
        q->front = newNode;  // Новый узел становится началом очереди
        q->rear = newNode;   // Новый узел становится концом очереди
    } else {  // Иначе
        q->rear->next = newNode;  // Устанавливаем указатель на следующий узел для текущего конца очереди
        q->rear = newNode;        // Новый узел становится концом очереди
    }
}

// Функция для удаления элемента из начала очереди
TreeNode* pop_tree_queue(TreeQueue* q) {
    if (q->front == NULL) {  // Если очередь пуста
        return NULL;         // Возвращаем NULL, так как нечего удалять
    }

    TreeNodeQueue* temp = q->front;  // Сохраняем указатель на начало очереди во временную переменную
    TreeNode* node = temp->node;     // Сохраняем указатель на узел дерева, который будем возвращать

    q->front = q->front->next;  // Перемещаем указатель на начало очереди на следующий узел
    if (q->front == NULL) {     // Если очередь стала пустой
        q->rear = NULL;         // Устанавливаем указатель на конец очереди в NULL
    }

    free(temp);  // Освобождаем память, выделенную под узел очереди
    return node; // Возвращаем указатель на узел дерева
}

// Функция для проверки, является ли очередь пустой
int isEmptyTreeQueue(TreeQueue* q) {
    return (q->front == NULL);  // Возвращаем 1, если очередь пуста, иначе 0
}
