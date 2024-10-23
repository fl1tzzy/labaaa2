#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Вариант 1 задание 4
typedef struct StringArray {
    char **data;
    size_t capacity;
    size_t size;
} StringArray;

// Функция для создания массива строк с заданной начальной емкостью
StringArray* create_string_array(size_t capacity) {
    StringArray* arr = (StringArray*)malloc(sizeof(StringArray));
    arr->data = (char**)malloc(capacity * sizeof(char*));
    arr->size = 0;
    arr->capacity = capacity;
    return arr;
}

// Функция для добавления строки в конец массива
void append_string(StringArray* arr, const char* str) {
    if (arr->size == arr->capacity) {
        arr->capacity *= 2;
        arr->data = (char**)realloc(arr->data, arr->capacity * sizeof(char*));
    }
    arr->data[arr->size++] = strdup(str);
}

// Функция для удаления строки из массива по указанному индексу
void deleteStringAt(StringArray* arr, int index) {
    if (index < 0 || index >= arr->size) {
        printf("Invalid index\n");
        return;
    }
    free(arr->data[index]);
    for (int i = index; i < arr->size - 1; i++) {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;
}

// Функция для вывода всех строк в массиве
void printStringArray(StringArray* arr) {
    if (arr->size == 0) {
        printf("Array is empty\n");
        return;
    }
    printf("Array elements: ");
    for (int i = 0; i < arr->size; i++) {
        printf("'%s' ", arr->data[i]);
    }
    printf("\n");
}

// Функция для освобождения памяти, выделенной под массив строк
void freeStringArray(StringArray* arr) {
    for (int i = 0; i < arr->size; i++) {
        free(arr->data[i]);
    }
    free(arr->data);
    free(arr);
}

// Рекурсивная функция для генерации подмассивов
void generateSubsets(StringArray* arr, int n, int index, StringArray* currentSubset, StringArray* result) {
    if (index == n) {
        char subsetStr[1024] = "{";
        for (int i = 0; i < currentSubset->size; i++) {
            strcat(subsetStr, currentSubset->data[i]);
            if (i < currentSubset->size - 1) {
                strcat(subsetStr, ", ");
            }
        }
        strcat(subsetStr, "}");
        append_string(result, subsetStr);
        return;
    }

    generateSubsets(arr, n, index + 1, currentSubset, result);

    append_string(currentSubset, arr->data[index]);
    generateSubsets(arr, n, index + 1, currentSubset, result);

    deleteStringAt(currentSubset, currentSubset->size - 1);
}

// Функция для генерации всех подмассивов
StringArray* getAllSubsets(StringArray* arr) {
    int n = arr->size;
    StringArray* result = create_string_array(1 << n); // 2^n подмассивов
    StringArray* currentSubset = create_string_array(n);

    generateSubsets(arr, n, 0, currentSubset, result);

    freeStringArray(currentSubset);

    return result;
}

int main() {
    // Создаем массив строк с начальной емкостью 3
    StringArray* arr = create_string_array(3);

    // Добавляем нужные значения в массив
    append_string(arr, "x");
    append_string(arr, "y");
    append_string(arr, "z");

    // Получаем все подмассивы
    StringArray* subsets = getAllSubsets(arr);

    // Выводим все подмассивы
    printStringArray(subsets);

    // Освобождаем память, выделенную под массивы
    freeStringArray(subsets);
    freeStringArray(arr);

    return 0;
}
