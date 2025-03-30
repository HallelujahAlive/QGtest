#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 打印数组
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
    //a[0]需要预留作为哨兵
    for (i = 2; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            //如果 arr[i] < arr[i - 1]，说明 i 是无序区的第一个元素的位置，此时需要将 arr[i] 的值放到 arr[0]
            arr[0] = arr[i];
            /*j索引一开始指向有序部分的最后一个元素，只要a[j]大于哨兵a[0]，那么a[j]就向后移一位(a[j+1]=a[j])，一直到a[j]<a[0]
			时，for循环停止，然后哨兵a[0]插入到a[j]的后面(a[j+1]=a[0]),这时候a[0]又空了出来，继续下一轮排序 
			*/ 
            for (j = i - 1; arr[j] > arr[0]; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = arr[0];
        }
    }
}

//生成随机数组
void generateRandomArray(int arr[], int n) {
    srand(time(NULL));
    int i;
    for (i = 1; i < n; i++) {
        arr[i] = rand();
    }
}

int main() {
    int sizes[] = {10000, 50000, 200000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);

    int i;
    for (i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int *arr = (int *)malloc((n + 1) * sizeof(int));
        if (arr == NULL) {
            printf("内存分配失败\n");
            return 1;
        }

        //生成随机数组
        generateRandomArray(arr, n);
        //记录开始时间
        clock_t start = clock();
        //执行插入排序
        InsertSort(arr, n);
        // 记录结束时间
        clock_t end = clock();
        //计算用时（秒）
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("数据量为 %d 时，插入排序用时: %f 秒\n", n, time_taken);
        //释放内存
        free(arr);
    }
    system("pause");
    return 0;
}
