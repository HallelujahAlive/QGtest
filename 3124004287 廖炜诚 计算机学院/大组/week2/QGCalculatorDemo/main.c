#include <stdio.h>
#include "calculator.h"

int main() {
    char expression[100];
    printf("������������ʽ��");
    scanf("%s", expression);

    double result = evaluateExpression(expression);
    printf("������Ϊ��%.2f\n", result);

    return 0;
}    
