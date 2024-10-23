#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>

// Определяем структуру для хранения множества подмножеств
typedef struct Set {
    int **subsets;          // Массив для хранения подмножеств
    size_t capacity;        // Вместимость
    size_t size;            // Текущий размер
} Set;

// Функция для создания нового множества
Set *create_set(size_t capacity) {
    Set *set = malloc(sizeof(Set));  // Выделяем память для структуры Set
    set->subsets = malloc(capacity * sizeof(int *));  // Выделяем память для массива подмножеств
    set->size = 0;  // Инициализируем текущий размер нулем
    set->capacity = capacity;  // Устанавливаем вместимость
    return set;  // Возвращаем указатель на созданное множество
}

// Функция для сравнения двух подмножеств
bool subsets_equal(int *subset1, size_t size1, int *subset2, size_t size2) {
    if (size1 != size2) return false;  // Если размеры подмножеств не равны, возвращаем false
    for (size_t i = 0; i < size1; i++) {
        if (subset1[i] != subset2[i]) return false;  // Если элементы подмножеств не равны, возвращаем false
    }
    return true;  // Если все элементы равны, возвращаем true
}

// Функция для проверки наличия подмножества в множестве
bool contains(Set *set, int *subset, size_t subset_size) {
    for (size_t i = 0; i < set->size; i++) {
        if (subsets_equal(set->subsets[i] + 1, set->subsets[i][0], subset, subset_size)) {
            return true;  // Если подмножество найдено, возвращаем true
        }
    }
    return false;  // Если подмножество не найдено, возвращаем false
}

// Функция для добавления подмножества в множество
void add_subset(Set *set, int *subset, size_t subset_size) {
    if (contains(set, subset, subset_size)) {
        return;  // Если подмножество уже существует, выходим из функции
    }
    
    if (set->size == set->capacity) {  // Если достигнута вместимость
        set->capacity *= 2;  // Увеличиваем вместимость в два раза
        set->subsets = realloc(set->subsets, set->capacity * sizeof(int *));  // Перераспределяем память
    }

    // Создаем копию подмножества
    int *new_subset = malloc((subset_size + 1) * sizeof(int));
    new_subset[0] = subset_size;  // Храним размер подмножества
    for (size_t i = 0; i < subset_size; i++) {
        new_subset[i + 1] = subset[i];
    }

    set->subsets[set->size] = new_subset;  // Добавляем подмножество в множество
    set->size++;  // Увеличиваем текущий размер
}

// Функция для освобождения памяти, выделенной под множество
void free_set(Set *set) {
    for (size_t i = 0; i < set->size; i++) {
        free(set->subsets[i]);  // Освобождаем память, выделенную под каждое подмножество
    }
    free(set->subsets);  // Освобождаем память, выделенную под массив подмножеств
    free(set);  // Освобождаем память, выделенную под структуру Set
}

// Рекурсивная функция для поиска подмножеств с заданной суммой
void find_subsets(int *set, int n, int subset_sum, int *subset, int subset_size, int current_sum, Set *result_set) {
    if (current_sum == subset_sum) {  // Если текущая сумма равна целевой сумме
        add_subset(result_set, subset, subset_size);  // Добавляем подмножество в результирующее множество
        return;
    }

    for (int i = 0; i < n; i++) {  // Перебираем элементы множества
        if (current_sum + set[i] <= subset_sum) {  // Если текущая сумма плюс текущий элемент не превышает целевую сумму
            subset[subset_size] = set[i];  // Добавляем элемент в текущее подмножество
            find_subsets(set + i + 1, n - i - 1, subset_sum, subset, subset_size + 1, current_sum + set[i], result_set);  // Рекурсивный вызов
        }
    }
}

// Функция для разделения множества на подмножества с заданной суммой
void partition_set(int *set, int n, int target_sum) {
    int total_sum = 0;
    for (int i = 0; i < n; i++) {
        total_sum += set[i];  // Вычисляем общую сумму элементов множества
    }

    if (total_sum % target_sum != 0) {  // Если общая сумма не делится на целевую сумму без остатка
        printf("Ошибка: множество не может быть разделено на подмножества с равными суммами.\n");
        return;
    }

    int num_subsets = total_sum / target_sum;  // Вычисляем количество подмножеств
    Set *result_set = create_set(10);  // Создаем множество для хранения результатов с начальной вместимостью 10
    int *subset = (int *)malloc(n * sizeof(int));  // Выделяем память для текущего подмножества

    printf("Подмножества с суммой %d:\n", target_sum);
    for (int i = 0; i < num_subsets; i++) {
        find_subsets(set, n, target_sum, subset, 0, 0, result_set);  // Ищем подмножества с заданной суммой
    }

    if (result_set->size == 0) {  // Если не найдено ни одного подмножества
        printf("Ошибка: не найдено подходящее подмножество.\n");
    } else {
        for (size_t i = 0; i < result_set->size; i++) {
            printf("Найдено подмножество: { ");
            for (size_t j = 1; j <= result_set->subsets[i][0]; j++) {
                printf("%d ", result_set->subsets[i][j]);  // Выводим элементы подмножества
            }
            printf("}\n");
        }
    }

    free_set(result_set);  // Освобождаем память, выделенную под результирующее множество
    free(subset);  // Освобождаем память, выделенную под текущее подмножество
}

int main() {
    int set[] = {4, 10, 5, 1, 3, 7};  // Исходное множество
    int n = sizeof(set) / sizeof(set[0]);  // Вычисляем количество элементов в множестве
    int target_sum;

    printf("Введите целевую сумму для подмножеств: ");
    scanf("%d", &target_sum);  // Считываем целевую сумму с клавиатуры

    partition_set(set, n, target_sum);  // Вызываем функцию для разделения множества

    return 0;
}
