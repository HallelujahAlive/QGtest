#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h"

// 判断运算符优先级
int precedence(char op);

// 计算操作
double calculate(double a, double b, char op);

// 计算四则表达式
double evaluateExpression(char *expression);

#endif    
