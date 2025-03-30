#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 打印数组
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

// 获取整数的某一位数
int getDigit(int num, int digit) {
    int temp = 1;
    int i;
    for (i = 0; i < digit - 1; i++) {
        temp *= 10;
    }
    return (num / temp) % 10;
}

// 基数排序
void RadixCountSort(int arr[], int n) {
    // 首先找到数组中的最大值
    int maxValue = arr[0];
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int maxDigit = 0;
    // 计算最大值的位数
    while (maxValue > 0) {
        maxValue /= 10;
        maxDigit++;
    }
    // 创建指针数组，表示桶
    int *duckets[10];
    for (i = 0; i < 10; i++) {
        // 分配内存，每个桶可以存储 n 个整数
        duckets[i] = (int *)malloc(n * sizeof(int));
    }
    // 临时桶的大小初始为 0
    int ducketSize[10] = {0};
    int digit;
    // 从最低位开始，逐位进行排序
    for (digit = 1; digit <= maxDigit; digit++) {
        for (i = 0; i < n; i++) {
            // 获取当前数字的第 digit 位
            int currentDigit = getDigit(arr[i], digit);
            // 将当前数字放入对应的桶中
            duckets[currentDigit][ducketSize[currentDigit]++] = arr[i];
        }
        // 将桶中的数字按顺序放回原数组
        int index = 0;
        for (i = 0; i < 10; i++) {
            int j;
            for (j = 0; j < ducketSize[i]; j++) {
                arr[index++] = duckets[i][j];
            }
            // 清空每个桶的大小
            ducketSize[i] = 0;
        }
    }
    // 释放分配的内存
    for (i = 0; i < 10; i++) {
        free(duckets[i]);
    }
}

int main() {
    const int dataSize = 100;  // 每个数据集的大小
    const int numTests = 100000;  // 测试次数

    int *arr = (int *)malloc(dataSize * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));  // 初始化随机数种子

    clock_t start, end;
    double cpu_time_used;

    start = clock();  // 记录开始时间
    int test;
    for (test = 0; test < numTests; test++) {
        // 生成随机数据
        int i;
        for (i = 0; i < dataSize; i++) {
            arr[i] = rand() % 1000;  // 生成 0 到 999 之间的随机数
        }

        // 调用基数排序函数
        RadixCountSort(arr, dataSize);
    }

    end = clock();  // 记录结束时间

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("排序%d次每次%d个数据，总共用时: %f 秒\n", numTests, dataSize, cpu_time_used);

    free(arr);  // 释放分配的内存
    system("pause");
    return 0;
}
