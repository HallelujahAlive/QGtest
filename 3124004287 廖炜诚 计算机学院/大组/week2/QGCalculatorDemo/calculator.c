#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "calculator.h"

// 判断运算符优先级
int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

// 计算操作
double calculate(double a, double b, char op) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            if (b == 0) {
                printf("除数不能为零！\n");
                return 0;
            }
            return a / b;
        default:
            return 0;
    }
}

// 计算四则表达式
double evaluateExpression(char *expression) {
    LinkStack numStack, opStack;
    initStack(&numStack);
    initStack(&opStack);

    int i = 0;
    while (expression[i] != '\0') {
        if (isdigit(expression[i])) {
            double num = 0;
            while (isdigit(expression[i])) {
                num = num * 10 + (expression[i] - '0');
                i++;
            }
            push(&numStack, num);
            i--;
        } else if (expression[i] == '+' || expression[i] == '-' || expression[i] == '*' || expression[i] == '/') {
            while (!isEmpty(&opStack) && precedence(getTop(&opStack)) >= precedence(expression[i])) {
                double b = pop(&numStack);
                double a = pop(&numStack);
                char op = pop(&opStack);
                double result = calculate(a, b, op);
                push(&numStack, result);
            }
            push(&opStack, expression[i]);
        }
        i++;
    }

    while (!isEmpty(&opStack)) {
        double b = pop(&numStack);
        double a = pop(&numStack);
        char op = pop(&opStack);
        double result = calculate(a, b, op);
        push(&numStack, result);
    }

    return getTop(&numStack);
}    
