#include <stdio.h>
#include "calculator.h"

int main() {
    char expression[100];
    printf("请输入四则表达式：");
    scanf("%s", expression);

    double result = evaluateExpression(expression);
    printf("计算结果为：%.2f\n", result);

    return 0;
}    
