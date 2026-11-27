#ifndef CALC_H //проверка существования отметки
#define CALC_H //создаем эту отметку, чтобы файл не обрабатывался повторно при той же компиляции



int calculate(int left_operand, char operator_char, int right_operand, int* is_valid); //функция мат.выражений
char* build_string(const int* results, int count, int key); //функция, превращающая результат в строку
int parse_int(const char* text, int* value); //функция, превращающая строку в целое число
int validate_operator(const char* text); //функция проверки мат.знака

#endif //закрытие проверки