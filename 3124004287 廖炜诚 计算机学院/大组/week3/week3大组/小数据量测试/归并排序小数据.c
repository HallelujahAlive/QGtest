#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//打印数组
void printArr(int arr[], int n) {
    int i = 0;
    for (; i < n; i++) {
        printf("%d ", arr[i]);
    }
    //打印完之后换行
    putchar('\n');
}

//合并数组
void merge(int arr[], int tempArr[], int left, int mid, int right) {
    //左子数组的起始索引
    int l_left = left;
    //右子数组的起始元素, 即mid+1
    int l_right = mid + 1;
    //临时数组元素的索引
    int t_left = left;
    // 开始合并
    while (l_left <= mid && l_right <= right) {
        if (arr[l_left] < arr[l_right]) {  //如果左子数组的第一个元素更小，那么该元素先放入临时数组
            tempArr[t_left++] = arr[l_left++];
        } else {
            tempArr[t_left++] = arr[l_right++];
        }
    }
    //左子数组有剩余元素时，将剩余元素全部放入临时数组
    while (l_left <= mid) {
        tempArr[t_left++] = arr[l_left++];
    }
    //右子数组有剩余元素时，将剩余元素全部放入临时数组
    while (l_right <= right) {
        tempArr[t_left++] = arr[l_right++];
    }
    //将临时数组复制回原数组
    while (left <= right) {
        arr[left] = tempArr[left];
        left++;
    }
}

//拆分和递归排序主要是将原始数组通过递归拆分成一个个小的数组
void msort(int arr[], int tempArr[], int left, int right) {
    if (left < right) {
        //计算中间位置，将中间以及中间之前的元素构成的子数组称为左子数组，mid+1之后的元素构成的子数组称为右子数组
        int mid = (left + right) / 2;
        //开始递归拆分左子数组
        msort(arr, tempArr, left, mid);
        //递归拆分右子数组, 注意，右子数组的起始索引是从mid+1开始的，mid索引对应的元素属于左子数组
        msort(arr, tempArr, mid + 1, right);
        //拆分之后，必然要进行合并，此时需要用到merge函数
        merge(arr, tempArr, left, mid, right);
    }
}

//归并排序主函数，主要是分配内存以及调用拆分和递归排序
void msort_merge(int arr[], int n) {
    int* tempArr = (int*)malloc(n * sizeof(int));
    if (tempArr) {
        //分配内存成功，那么调用拆分和递归排序msort
        msort(arr, tempArr, 0, n - 1);
        //排序完成之后需要释放空间，释放内存
        free(tempArr);
    } else {
        printf("分配内存失败!排序失败!");
    }
}

int main() {
    const int dataSize = 100;  // 数据量
    const int testTimes = 100000;  // 测试次数

    int arr[dataSize];
    clock_t start, end;
    double cpu_time_used;

    //初始化随机数种子
    srand(time(NULL));

    start = clock();  //记录开始时间
    int i;
    for (i = 0; i < testTimes; i++) {
        //生成随机数据
        int j;
        for (j = 0; j < dataSize; j++) {
            arr[j] = rand();
        }
        //进行归并排序
        msort_merge(arr, dataSize);
    }

    end = clock();  //记录结束时间
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  // 计算用时

    printf("归并排序%d次，每次%d个数据，总共用时: %f 秒\n", testTimes, dataSize, cpu_time_used);
    system("pause");
    return 0;
}
