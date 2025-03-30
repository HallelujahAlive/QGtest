#include <stdio.h>
#include <stdlib.h>

// 打印数组
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

// 获取整数的某一位数字
int getDigit(int num, int digit) {
    int temp = 1;
    int i;
    for (i = 0; i < digit - 1; i++) {
        temp *= 10;
    }
    return (num / temp) % 10;
}

// 基数计数排序
void RadixCountSort(int arr[], int n) {
    // 先找到数组中的最大值
    int maxValue = arr[0];
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int maxDigit = 0;
    // 确定最大值的位数（digit）是多少，用maxDigit表示最大位数
    while (maxValue > 0) {
        maxValue /= 10;
        maxDigit++;
    }
    // 创建指针数组，表示桶 (ducket)
    int *duckets[10];
    for (i = 0; i < 10; i++) {
        // 分配内存，每个桶可以存储n个整数
        duckets[i] = (int *)malloc(n * sizeof(int));
    }
    // 临时桶的大小初始为0
    int ducketSize[10] = {0};
    int digit;
    // 如果最大位数为3，那么只需要进行3次循环
    for (digit = 1; digit <= maxDigit; digit++) {
        int i;
        for (i = 0; i < n; i++) {
            // 获取当前数字的第digit位
            int currentDigit = getDigit(arr[i], digit);
            // 获取当前数字的当前位之后，需要根据该位数字将其放到对应的桶之中去
            duckets[currentDigit][ducketSize[currentDigit]++] = arr[i];
        }
        // 将所有数字放到对应的桶之后，需要按位从小到大取出并放回数组
        // 从位为0的数字开始取
        int index = 0;
        for (i = 0; i < 10; i++) {
            int j;
            for (j = 0; j < ducketSize[i]; j++) {
                arr[index++] = duckets[i][j];
            }
            // 重置每个桶的大小为0
            ducketSize[i] = 0;
        }
    }
    // 排序完成之后释放空间，防止占用内存
    for (i = 0; i < 10; i++) {
        free(duckets[i]);
    }
}

int main() {
    FILE *file;
    int capacity = 10;
    int *arr = (int *)malloc(capacity * sizeof(int));
    int n = 0;

    // 打开文件
    file = fopen("test_data.txt", "r");
    if (file == NULL) {
        perror("无法打开文件");
        return 1;
    }

    // 读取文件中的整数
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        if (n >= capacity) {
            // 如果数组已满，扩大数组容量
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
            if (arr == NULL) {
                perror("内存分配失败");
                fclose(file);
                return 1;
            }
        }
        arr[n++] = num;
    }

    //关闭文件
    fclose(file);
    //打印原始数组
    printf("原数组:");
    printArr(arr, n);
    //执行基数排序
    RadixCountSort(arr, n);
    //打印排序后的数组
    printf("排序后:");
    printArr(arr, n);
    //释放数组内存
    free(arr);
    system("pause");
    return 0;
}
