#include "calc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv) {
    int key_flag_index = -1;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-k") == 0) {
            key_flag_index = i;
            break;
        }
        if (argv[i][0] == '-' && argv[i][1] != '\0' &&
            !(argv[i][1] >= '0' && argv[i][1] <= '9')) {
            fprintf(stderr, "Error: unknown flag '%s'\n", argv[i]); //неизвестный флаг
            return 1;
        }
    }

    if (key_flag_index == -1) {
        fprintf(stderr, "Error: missing -k flag\n"); //отстутствие флага
        return 1;
    }
    if (key_flag_index + 2 != argc) {
        fprintf(stderr, "Error: exactly one key must follow -k\n"); //должен быть только один ключ
        return 1;
    }

    int expression_arg_count = key_flag_index - 1;
    if (expression_arg_count == 0 || expression_arg_count % 3 != 0) {
        fprintf(stderr, "Error: number of expression arguments is not a multiple of 3\n"); //неверное количество аргументов
        return 1;
    }

    int expression_count = expression_arg_count / 3;

    int* results = malloc((size_t)expression_count * sizeof(int));
    if (!results) {
        fprintf(stderr, "Error: memory allocation failed\n"); //ошибка выделения памяти
        return 1;
    }

    for (int i = 0; i < expression_count; i++) {
        const char* left_str = argv[1 + i * 3];
        const char* operator_str = argv[2 + i * 3];
        const char* right_str = argv[3 + i * 3];

        int left_operand, right_operand;
        if (!parse_int(left_str, &left_operand) ||
            !parse_int(right_str, &right_operand)) {
            fprintf(stderr, "Error: operand is not an integer\n"); //операнд не является целым числом
            free(results);
            return 1;
        }
        if (!validate_operator(operator_str)) {
            fprintf(stderr, "Error: invalid operator '%s'\n", operator_str); //неправильный мат.знак
            free(results);
            return 1;
        }

        int is_valid = 0;
        int result = calculate(left_operand, operator_str[0], right_operand, &is_valid);
        if (!is_valid) {
            fprintf(stderr, "Error: division by zero in expression #%d\n", i + 1); //деление на ноль
            free(results);
            return 1;
        }
        results[i] = result;
    }

    int key;
    if (!parse_int(argv[key_flag_index + 1], &key)) {
        fprintf(stderr, "Error: key is not an integer\n"); //ключ не является целым числом
        free(results);
        return 1;
    }

    for (int i = 0; i < expression_count; i++) {
        printf("Answer #%d: %d\n", i + 1, results[i]); //перебор результатов
    }

    char* decoded_string = build_string(results, expression_count, key);
    if (!decoded_string) {
        fprintf(stderr, "Error: memory allocation failed\n"); //не удалось выделить память
        free(results);
        return 1;
    }

    printf("Result string: %s\n", decoded_string);

    free(decoded_string);
    free(results);
    return 0;
}