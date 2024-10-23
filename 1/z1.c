#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//Вариант 3 задание 1
// Структура для стека
typedef struct _stack {
    char *data;
    struct _stack* next;
} stack;

// Функция для добавления элемента в стек
stack* push(stack* top, const char* value) {
    stack* ptr = (stack*)malloc(sizeof(stack));
    ptr->data = strdup(value);
    ptr->next = top;
    return ptr;
}

// Функция для удаления элемента из стека
stack* pop(stack* top) {
    if (top == NULL) return NULL;
    stack* ptr = top->next;
    free(top->data);
    free(top);
    return ptr;
}

// Функция для реверсирования стека
stack* reverse_stack(stack* top) {
    stack* new_top = NULL;
    while (top != NULL) {
        new_top = push(new_top, top->data);
        top = pop(top);
    }
    return new_top;
}

// Функция для определения приоритета оператора
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// Функция для преобразования инфиксной нотации в постфиксную
void infix_to_postfix(const char* infix) {
    stack* operators = NULL;
    stack* postfix = NULL;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            // Если символ - операнд, добавляем его в выходную строку
            char operand[2] = {infix[i], '\0'};
            postfix = push(postfix, operand);
        } else if (infix[i] == '(') {
            // Если символ - открывающая скобка, помещаем её в стек операторов
            char op[2] = {infix[i], '\0'};
            operators = push(operators, op);
        } else if (infix[i] == ')') {
            // Если символ - закрывающая скобка, выталкиваем операторы из стека
            // до открывающей скобки в выходную строку
            while (operators != NULL && strcmp(operators->data, "(") != 0) {
                postfix = push(postfix, operators->data);
                operators = pop(operators);
            }
            if (operators != NULL && strcmp(operators->data, "(") == 0) {
                operators = pop(operators);
            }
        } else {
            // Если символ - оператор, выталкиваем операторы с большим или равным
            // приоритетом из стека в выходную строку
            while (operators != NULL && precedence(operators->data[0]) >= precedence(infix[i])) {
                postfix = push(postfix, operators->data);
                operators = pop(operators);
            }
            char op[2] = {infix[i], '\0'};
            operators = push(operators, op);
        }
    }

    // Выталкиваем оставшиеся операторы из стека в выходную строку
    while (operators != NULL) {
        postfix = push(postfix, operators->data);
        operators = pop(operators);
    }

    // Реверсируем стек постфиксной нотации для правильного вывода
    postfix = reverse_stack(postfix);

    // Выводим постфиксную нотацию
    while (postfix != NULL) {
        printf("%s ", postfix->data);
        postfix = pop(postfix);
    }
    printf("\n");

    // Освобождаем память
    while (operators != NULL) {
        operators = pop(operators);
    }
}

int main() {
    const char* infix = "A+B*C";
    printf("Infix: %s\n", infix);
    printf("Postfix: ");
    infix_to_postfix(infix);
    return 0;
}
