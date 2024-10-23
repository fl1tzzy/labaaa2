#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_map.h"

// Функция для преобразования целого числа в римскую цифру
char* int_to_roman(int num) {
    // Создаем хэш-таблицу для хранения соответствий римских цифр и их значений
    Hash_Map *roman_map = hash_map_create(13);

    // Заполняем хэш-таблицу
    hash_map_insert(roman_map, "M", "1000");
    hash_map_insert(roman_map, "CM", "900");
    hash_map_insert(roman_map, "D", "500");
    hash_map_insert(roman_map, "CD", "400");
    hash_map_insert(roman_map, "C", "100");
    hash_map_insert(roman_map, "XC", "90");
    hash_map_insert(roman_map, "L", "50");
    hash_map_insert(roman_map, "XL", "40");
    hash_map_insert(roman_map, "X", "10");
    hash_map_insert(roman_map, "IX", "9");
    hash_map_insert(roman_map, "V", "5");
    hash_map_insert(roman_map, "IV", "4");
    hash_map_insert(roman_map, "I", "1");

    // Массив для хранения ключей (римских цифр)
    const char *keys[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

    // Строка для результата
    char *result = calloc(100, sizeof(char));

    // Проходим по всем ключам и добавляем соответствующие римские цифры к результату
    for (int i = 0; i < 13; i++) {
        int value = atoi(hash_map_at(roman_map, keys[i]));
        while (num >= value) {
            strcat(result, keys[i]);
            num -= value;
        }
    }

    // Освобождаем память, выделенную для хэш-таблицы
    hash_map_free(roman_map);

    return result;
}

int main() {
    int num;
    printf("Введите целое число: ");
    scanf("%d", &num);

    char *roman = int_to_roman(num);
    printf("Римская цифра: %s\n", roman);

    // Освобождаем память, выделенную для результата
    free(roman);

    return 0;
}