#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <stdlib.h>

void circle(wchar_t *string, int *pos, int count);

void square(wchar_t *string, int *pos, int count);

void err_disp(int err_code, const int *pos) {
    if (err_code == 0) {
        wprintf(L"Строчка корректна.\n");
    } else if (err_code == 1) {
        wprintf(L"Недопустимое начало строки.\n");
    } else if (err_code == 2) {
        wprintf(L"На позиции %d ожидались '-' или '('\n", *pos);
    } else if (err_code == 3) {
        wprintf(L"На позиции %d ожидалось закрытие скобки.\n", *pos);
    } else if (err_code == 4) {
        wprintf(L"На позиции %d ожидались '+' или '['\n", *pos);
    } else if (err_code == 5) {
        wprintf(L"Лишние символы в строчке.\n");
    }
    exit(0);
}

void square(wchar_t *string, int *pos, int count) {
    if (count < 2 && *(string + *pos) == '(') {
        (*pos)++;
        circle(string, pos, 0);
    } else if (count < 2 && *(string + *pos) == '-') {
        (*pos)++;
    } else if (count == 2 && *(string + *pos) == ']') {
        (*pos)++;
        return;
    } else if (count < 2) {
        (*pos)++;
        err_disp(2, pos);
    } else if (count == 2 && *(string + *pos) != ']') {
        (*pos)++;
        err_disp(3, pos);
    }
    if (count < 2) {
        count++;
        square(string, pos, count);
    }
}

void circle(wchar_t *string, int *pos, int count) {
    if (count < 2 && *(string + *pos) == '[') {
        (*pos)++;
        square(string, pos, 0);
    } else if (count < 2 && *(string + *pos) == '+') {
        (*pos)++;
    } else if (count == 2 && *(string + *pos) == ')') {
        (*pos)++;
        return;
    } else if (count < 2) {
        (*pos)++;
        err_disp(4, pos);
    } else if (count == 2 && *(string + *pos) != ')') {
        (*pos)++;
        err_disp(3, pos);
    }
    if (count < 2) {
        count++;
        circle(string, pos, count);
    }
}

int main() {
    setlocale(LC_ALL, "");
    int i = 0;
    wchar_t string[1000];
    fgetws(string, 1000, stdin);
    if (wcslen(string) == 2 && (string[0] == '+' || string[0] == '-')) {
        err_disp(0, 0);
    } else if (string[0] == '[') {
        i++;
        square(string, &i, 0);
    } else if (string[0] == '(') {
        i++;
        circle(string, &i, 0);
    } else {
        err_disp(1, &i);
    }
    wprintf(L"%d %lc\n", i, string[i]);
    if (string[i] == '\n') {
        err_disp(0, 0);
    } else {
        err_disp(5, &i);
    }
    return 0;
}