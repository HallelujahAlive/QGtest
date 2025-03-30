#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//打印数组函数
void printArr(int arr[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

//直接插入排序函数
void InsertSort(int arr[], int n) {
    int i, j;
    // a[0] 需要空出来作为哨兵
    for (i = 2; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            // 如果 arr[i] < arr[i - 1]，说明 i 是无序区的第一个元素的位置，此时要把 arr[i] 的值放到 arr[0]
            arr[0] = arr[i];
            /* j 一开始指向有序区的最后一个元素，只要 arr[j] 大于哨兵 arr[0]，那么 arr[j] 向后移动一位 (arr[j + 1] = arr[j])，
               一直到 arr[j] < arr[0] 时，for 循环停止，然后将哨兵 arr[0] 放到 arr[j] 的后面 (arr[j + 1] = arr[0])，
               此时 a[0] 空出来，一次插入排序完成 
            */
            for (j = i - 1; arr[j] > arr[0]; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = arr[0];
        }
    }
}

int main() {
    const int dataSize = 100;  //数据量
    const int sortTimes = 100000;  //排序次数

    int arr[dataSize + 1];  //数组，第一个位置作为哨兵
    clock_t start, end;
    double cpu_time_used;

    //初始化随机数种子
    srand(time(NULL));

    //记录开始时间
    start = clock();

    //进行 100k 次排序
    int k;
    for (k = 0; k < sortTimes; k++) {
        //生成 100 个随机数据
        int i;
        for (i = 1; i <= dataSize; i++) {
            arr[i] = rand() % 1000;  //生成 0到999之间的随机数
        }

        //进行插入排序
        InsertSort(arr, dataSize + 1);
    }

    // 记录结束时间
    end = clock();

    // 计算排序用时
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // 输出排序用时
    printf("插入排序%d次每次%d个数据，总共用时: %f秒\n", sortTimes, dataSize, cpu_time_used);
    system("pause");
    return 0;
}
