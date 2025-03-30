#include <stdio.h>
#include <stdlib.h>

// 打印数组
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
    // 右子数组的起始元素，从 mid+1 开始
    int l_right = mid + 1;
    //临时数组元素的索引
    int t_left = left;
    //开始合并
    while (l_left <= mid && l_right <= right) {
        if (arr[l_left] < arr[l_right]) {  //如果左子数组的第一个元素更小，那么该元素先放入临时数组
            tempArr[t_left++] = arr[l_left++];
        } else {
            tempArr[t_left++] = arr[l_right++];
        }
    }
    //左子数组还有剩余元素时，将其全部放入临时数组
    while (l_left <= mid) {
        tempArr[t_left++] = arr[l_left++];
    }
    //右子数组还有剩余元素时，将其全部放入临时数组
    while (l_right <= right) {
        tempArr[t_left++] = arr[l_right++];
    }
    //将临时数组中的元素复制回原数组
    while (left <= right) {
        arr[left] = tempArr[left];
        left++;
    }
}

// 分治和递归的主要过程，将原始数组通过递归不断拆分成一个个小的
void msort(int arr[], int tempArr[], int left, int right) {
    if (left < right) {
        // 计算中间索引，将中间索引以及中间索引之前的元素构成的子数组称为左子数组，中间索引+1之后的元素构成的子数组称为右子数组
        int mid = (left + right) / 2;
        // 开始递归拆分左子数组
        msort(arr, tempArr, left, mid);
        // 递归拆分右子数组，注意，右子数组的起始索引是从 mid+1 开始的，mid 索引对应的元素属于左子数组
        msort(arr, tempArr, mid + 1, right);
        // 拆分完毕之后，必然要进行合并，此时需要用到 merge 函数
        merge(arr, tempArr, left, mid, right);
    }
}

//归并排序的入口函数，主要负责分配内存以及调用分治和合并函数
void msort_merge(int arr[], int n) {
    int* tempArr = (int*)malloc(n * sizeof(int));
    if (tempArr) {
        //内存分配成功，那么调用分治和合并函数 msort
        msort(arr, tempArr, 0, n - 1);
        //最后需要释放临时空间，释放内存
        free(tempArr);
    } else {
        printf("分配内存失败!排序失败!");
    }
}

//从文件中读取数据
int readDataFromFile(const char* filename, int** arr) {
    FILE* file = fopen("test_data.txt", "r");
    if (file == NULL) {
        perror("无法打开文件");
        return -1;
    }

    int count = 0;
    int num;
    //先计算文件中的数据数量
    while (fscanf(file, "%d", &num) == 1) {
        count++;
    }

    //分配内存来存储数据
    *arr = (int*)malloc(count * sizeof(int));
    if (*arr == NULL) {
        perror("内存分配失败");
        fclose(file);
        return -1;
    }

    // 将文件指针重置到文件开头
    rewind(file);

    // 读取数据到数组
    int i;
    for (i = 0; i < count; i++) {
        if (fscanf(file, "%d", &(*arr)[i]) != 1) {
            perror("读取文件数据失败");
            free(*arr);
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return count;
}

int main() {
    int* arr;
    int n = readDataFromFile("test_data.txt", &arr);
    if (n == -1) {
        return 1;
    }

    printf("原数组:\n");
    printArr(arr, n);

    // 调用归并排序函数
    msort_merge(arr, n);

    // 排序之后再次打印数组，检查是否排序成功
    printf("归并排序之后的数组:\n");
    printArr(arr, n);

    // 释放数组内存
    free(arr);
    system("pause");
    return 0;
}
