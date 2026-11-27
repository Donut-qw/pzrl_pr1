#include "calc.h"

#include <errno.h>
#include <limits.h>
#include <stdlib.h>

int calculate(int left_operand, char operator_char, int right_operand, int* is_valid) {
    *is_valid = 1;
    switch (operator_char) {
    case '+': return left_operand + right_operand;
    case '-': return left_operand - right_operand;
    case '*': return left_operand * right_operand;
    case '%':
        if (right_operand == 0) {
            *is_valid = 0;
            return 0;
        }
        return left_operand % right_operand;
    default:
        *is_valid = 0;
        return 0;
    }
}

char* build_string(const int* results, int count, int key) {
    char* buffer = malloc((size_t)count + 1);
    if (!buffer) {
        return NULL;
    }
    for (int i = 0; i < count; i++) {
        buffer[i] = (char)(results[i] - key);
    }
    buffer[count] = '\0';
    return buffer;
}

int parse_int(const char* text, int* value) {
    if (!text || !*text) {
        return 0;
    }
    errno = 0;
    char* end = NULL;
    long parsed = strtol(text, &end, 10);
    if (errno != 0 || end == text || *end != '\0') {
        return 0;
    }
    if (parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }
    *value = (int)parsed;
    return 1;
}

int validate_operator(const char* text) {
    if (!text || text[0] == '\0' || text[1] != '\0') {
        return 0;
    }
    return text[0] == '+' || text[0] == '-' || text[0] == '*' || text[0] == '%';
}