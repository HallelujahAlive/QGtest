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

//分区函数
int partition(int arr[], int low, int high) {
    //通常选择第一个元素作为基准
    int pivto = arr[low];
    while (low < high) {
        while (low < high && arr[high] >= pivto) {
            high--;
        }
        arr[low] = arr[high];
        while (low < high && arr[low] <= pivto) {
            low++;
        }
        arr[high] = arr[low];
    }
    arr[low] = pivto;  //实际上写 a[high]=pivto 也一样，因为 low 和 high 已经重合
    //返回基准的最终位置
    return low;
}

//快速排序函数
void QuickSort(int arr[], int low, int high) {
    //需要进行判断
    if (low < high) {
        //通过分区函数将数组分为两部分，并找到基准的最终位置
        int position = partition(arr, low, high);
        QuickSort(arr, low, position - 1);
        QuickSort(arr, position + 1, high);
    }
}

//生成随机数组
void generateRandomArray(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

int main() {
    const int dataSize = 100;  //数据量
    const int iterations = 100000;  //排序次数
    int arr[dataSize];

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    int i;
    for (i = 0; i < iterations; i++) {
        generateRandomArray(arr, dataSize);
        QuickSort(arr, 0, dataSize - 1);
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("对%d个数据进行%d次排序的总用时: %f 秒\n", dataSize, iterations, cpu_time_used);
    system("pause");
    return 0;
}
