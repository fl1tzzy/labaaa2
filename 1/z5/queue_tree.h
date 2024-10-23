#ifndef QUEUE_TREE_H
#define QUEUE_TREE_H

#include "tree.h"

typedef struct TreeNodeQueue {
    TreeNode* node;
    struct TreeNodeQueue* next;
} TreeNodeQueue;

typedef struct {
    TreeNodeQueue* front;
    TreeNodeQueue* rear;
} TreeQueue;

void init_tree_queue(TreeQueue* q);
void push_tree_queue(TreeQueue* q, TreeNode* node);
TreeNode* pop_tree_queue(TreeQueue* q);
int isEmptyTreeQueue(TreeQueue* q);

#endif