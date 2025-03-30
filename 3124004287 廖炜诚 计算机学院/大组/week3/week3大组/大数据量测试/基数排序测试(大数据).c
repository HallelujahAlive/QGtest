#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//打印数组
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

//获取一个数字的某一位
int getDigit(int num, int digit) {
    int temp = 1;
    int i;
    for (i = 0; i < digit - 1; i++) {
        temp *= 10;
    }
    return (num / temp) % 10;
}

//基数计数排序
void RadixCountSort(int arr[], int n) {
    //首先找到数组中的最大值
    int maxValue = arr[0];
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int maxDigit = 0;
    //计算最大值的位数
    while (maxValue > 0) {
        maxValue /= 10;
        maxDigit++;
    }
    //创建指针数组，表示桶
    int *duckets[10];
    for (i = 0; i < 10; i++) {
        //分配内存，每个桶可以存储 n 个数字
        duckets[i] = (int *)malloc(n * sizeof(int));
    }
    //桶的大小初始为 0
    int ducketSize[10] = {0};
    int digit;
    //按照位数进行排序
    for (digit = 1; digit <= maxDigit; digit++) {
        int i;
        for (i = 0; i < n; i++) {
            //获取当前数字的当前位数
            int currentDigit = getDigit(arr[i], digit);
            //将数字放入对应的桶中
            duckets[currentDigit][ducketSize[currentDigit]++] = arr[i];
        }
        //将桶中的数字按顺序放回数组
        int index = 0;
        for (i = 0; i < 10; i++) {
            int j;
            for (j = 0; j < ducketSize[i]; j++) {
                arr[index++] = duckets[i][j];
            }
            //清空每个桶的大小
            ducketSize[i] = 0;
        }
    }
    //释放内存
    for (i = 0; i < 10; i++) {
        free(duckets[i]);
    }
}

//生成随机数组
void generateRandomArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

//测试函数
void testRadixCountSort(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    generateRandomArray(arr, n);

    clock_t start = clock();
    RadixCountSort(arr, n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("排序 %d 个元素用时: %f 秒\n", n, time_taken);

    free(arr);
}

int main() {
    srand(time(NULL));

    // 测试不同数据量
    testRadixCountSort(10000);
    testRadixCountSort(50000);
    testRadixCountSort(200000);
    system("pause");
    return 0;
}
