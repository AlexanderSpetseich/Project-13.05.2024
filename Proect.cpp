#include <iostream>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

// Функция для вычисления выражения
double evaluate(const string& expr, size_t& index);

// Функция для выражения в скобках
double getFactor(const string& expr, size_t& index) {
    double result = 0;
    if (expr[index] == '(') {
        index++; // Пропускаем открывающую скобку
        result = evaluate(expr, index);
        index++; // Пропускаем закрывающую скобку
    }
    else {
        while (isdigit(expr[index]) || expr[index] == '.') {
            result = result * 10 + (expr[index] - '0');
            index++;
        }
    }
    return result;
}

// Функция для умножения и деления
double getTerm(const string& expr, size_t& index) {
    double result = getFactor(expr, index);
    while (expr[index] == '*' || expr[index] == '/') {
        char op = expr[index];
        index++;
        double factor = getFactor(expr, index);
        if (op == '*') {
            result *= factor;
        }
        else {
            result /= factor;
        }
    }
    return result;
}

// Функция для сложения и вычитания
double evaluate(const string& expr, size_t& index) {
    double result = getTerm(expr, index);
    while (expr[index] == '+' || expr[index] == '-') {
        char op = expr[index];
        index++;
        double term = getTerm(expr, index);
        if (op == '+') {
            result += term;
        }
        else {
            result -= term;
        }
    }
    return result;
}

int main() {
    setlocale(LC_ALL, "rus");
    cout << "Введите выражение без пробелов: ";
    string expression;
    getline(cin, expression); // Получаем выражение целиком

    size_t index = 0;
    double result = evaluate(expression, index);
    cout << "Результат: " << result << endl;

    return 0;
}