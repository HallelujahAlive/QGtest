#include <stdio.h>

/*
题目：现给定如下数组，你需要找到第3小的数
*/

/*
所给思路：思路：使用快排中的划分法使得我们可以在时间复杂度为O(nlogn)的情况下找到特定排位的数
*/

//交换
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//打印
void printArr(int arr[],int n){
	int i;
	for (i = 0;i < n;i++){
		printf("%d ",arr[i]);
	}
	putchar('\n');
} 

//传入数组、数组最左边下标(low)、数组最右边下标(high)
int partition(int arr[], int low, int high) {
	//选则最后一个元素作为支点，其实选择第一个元素也可以 
    int pivot = arr[high];
    //i用于标记小于支点的边界，初始化为起始下标 - 1，即还没找到小于枢轴的元素时的边界
    int i = (low - 1);

    // 遍历从起始下标到倒数第二个下标的元素
    int j;
    for (j = low; j <= high - 1; j++) {
        // 如果当前元素小于支点 
        if (arr[j] < pivot) {
            i++;
            // 交换当前小于支点的元素和边界后的元素
            swap(&arr[i], &arr[j]);
        }
    }
    // 把支点放到正确的位置
    swap(&arr[i + 1], &arr[high]);
    // 返回支点最终所在的下标位置
    return (i + 1);
}

//找到第k小的数的函数
//函数通过递归不断缩小查找范围，直到找到第k小的数
int kSmallest(int arr[], int low, int high, int k) {
    //确保k值大于0且在数组元素个数范围内
    if (k > 0 && k <= high - low + 1) {
        int pivotIndex = partition(arr, low, high);

        //如果支点的位置刚好是第k小的位置（位置从0开始计数，所以要减去起始下标low）
        if (pivotIndex - low == k - 1) {
            //直接返回支点对应的值，即找到了第k小的数
            return arr[pivotIndex];
        } 
        //如果支点位置在第k小的位置右边，说明第k小的数在支点左边的子数组里
        else if (pivotIndex - low > k - 1) {
            //递归在支点左边的子数组里继续找第k小的数
            return kSmallest(arr, low, pivotIndex - 1, k);
        } 
        //如果支点位置在第k小的位置左边，说明第k小的数在支点右边的子数组里
        else {
            //递归在支点右边的子数组里找第k小的数，同时调整k值（因为在右边子数组里找的是相对位置了）
            return kSmallest(arr, pivotIndex + 1, high, k - (pivotIndex - low + 1));
        }
    }
    //如果k值无效，返回 -1 表示错误
    return -1; 
}

int main() {
    int arr[] = {15, 22, 18, 4, 13, 7, 6};
    int n = sizeof(arr) / sizeof(arr[0]);
    //题目要求找到第三小的数 
    int k = 3;
    //先遍历数组，然后再打印第三小的数 
    printArr(arr,n);
    int result = kSmallest(arr, 0, n - 1, k);
    if (result != -1) {
        printf("第 %d 小的数是: %d\n", k, result);
    } else {
        printf("输入无效\n");
    }
    system("pause");
    return 0;
} 
