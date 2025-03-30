#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// 打印数组
void printArr(int arr[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

// 直接插入排序函数
void InsertSort(int arr[], int n) {
    int i, j;
    // a[0] 需要预留出来作为监视哨
    for (i = 2; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            // 如果 arr[i] < arr[i - 1]，说明 i 是无序区的第一个元素的位置，此时要把 arr[i] 的值放到 arr[0]
            arr[0] = arr[i];
            /* j 一开始指向有序区的最后一个元素，只要 arr[j] 大于监视哨 arr[0]，那么 arr[j] 就往后移一位 (arr[j + 1] = arr[j])，
               一直到 arr[j] < arr[0] 时，for 循环停止，然后将监视哨 arr[0] 放到 arr[j] 的后面 (arr[j + 1] = arr[0])，
               此时，arr[0] 空出来了，一次插入排序完成
            */
            for (j = i - 1; arr[j] > arr[0]; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = arr[0];
        }
    }
}

int main() {
    FILE *file;
    int arr[MAX_SIZE];
    int n = 0;

    // 以读取模式打开文件
    file = fopen("test_data.txt", "r");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return 1;
    }

    // 读取文件中的数据到数组
    while (fscanf(file, "%d", &arr[n]) != EOF && n < MAX_SIZE) {
        n++;
    }

    // 关闭文件
    fclose(file);

    printf("原始数组:\n");
    printArr(arr, n);

    // 进行插入排序
    InsertSort(arr, n);

    printf("直接插入排序之后的数组:\n");
    printArr(arr, n);
    system("pause");
    return 0;
}
