#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 打印数组
void printArr(int arr[], int n) {
    int i = 0;
    for (; i < n; i++) {
        printf("%d ", arr[i]);
    }
    // 打印完之后换行
    putchar('\n');
}

// 合并数组
void merge(int arr[], int tempArr[], int left, int mid, int right) {
    // 左子数组的起始索引
    int l_left = left;
    // 右子数组的起始元素，即 mid+1
    int l_right = mid + 1;
    // 临时数组元素的索引
    int t_left = left;
    // 开始合并
    while (l_left <= mid && l_right <= right) {
        if (arr[l_left] < arr[l_right]) { // 如果左子数组的第一个元素更小，那么该元素先放入临时数组
            tempArr[t_left++] = arr[l_left++];
        } else {
            tempArr[t_left++] = arr[l_right++];
        }
    }
    // 如果左子数组还有剩余元素，将其全部放入临时数组
    while (l_left <= mid) {
        tempArr[t_left++] = arr[l_left++];
    }
    // 如果右子数组还有剩余元素，将其全部放入临时数组
    while (l_right <= right) {
        tempArr[t_left++] = arr[l_right++];
    }
    // 将临时数组复制回原数组
    while (left <= right) {
        arr[left] = tempArr[left];
        left++;
    }
}

// 分割和递归调用
void msort(int arr[], int tempArr[], int left, int right) {
    if (left < right) {
        // 分割数组，mid 及其之前的元素组成左子数组，mid+1 及其之后的元素组成右子数组
        int mid = (left + right) / 2;
        // 开始递归分割左子数组
        msort(arr, tempArr, left, mid);
        // 递归分割右子数组，注意，右子数组的起始索引是 mid+1，mid 索引对应的元素属于左子数组
        msort(arr, tempArr, mid + 1, right);
        // 分割完成之后，需要进行合并操作，此时需要用到 merge 函数
        merge(arr, tempArr, left, mid, right);
    }
}

// 归并排序主函数，主要负责分配内存以及调用分割和合并函数
void msort_merge(int arr[], int n) {
    int* tempArr = (int*)malloc(n * sizeof(int));
    if (tempArr) {
        // 内存分配成功，那么调用分割和合并函数 msort
        msort(arr, tempArr, 0, n - 1);
        // 排序完成之后需要释放空间，回收内存
        free(tempArr);
    } else {
        printf("分配内存失败!排序失败!");
    }
}

// 生成随机数组
void generateRandomArray(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

int main() {
    int sizes[] = {10000, 50000, 200000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int i;
    for (i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("内存分配失败，无法测试大小为 %d 的数组。\n", n);
            continue;
        }

        //生成随机数组
        generateRandomArray(arr, n);
        //记录开始时间
        clock_t start = clock();
        //调用归并排序函数
        msort_merge(arr, n);

        //记录结束时间
        clock_t end = clock();

        //计算用时（单位：毫秒）
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        printf("数据量为 %d 时，归并排序用时: %.2f 毫秒\n", n, time_taken);
        //释放数组内存
        free(arr);
    }
    system("pause");
    return 0;
}
