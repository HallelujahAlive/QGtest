#ifndef CALCULATOR_H
#define CALCULATOR_H

#include "stack.h"

// �ж���������ȼ�
int precedence(char op);

// �������
double calculate(double a, double b, char op);

// ����������ʽ
double evaluateExpression(char *expression);

#endif    
