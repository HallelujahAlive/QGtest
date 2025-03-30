#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��ӡ����
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

// ��������
int partition(int arr[], int low, int high) {
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
    arr[low] = pivto;
    return low;
}

// ����������
void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int position = partition(arr, low, high);
        QuickSort(arr, low, position - 1);
        QuickSort(arr, position + 1, high);
    }
}

// �����������
void generateRandomArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

// ���Կ��������ʱ��
double testQuickSort(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    if (arr == NULL) {
        printf("�ڴ����ʧ��\n");
        return -1;
    }

    generateRandomArray(arr, n);

    clock_t start = clock();
    QuickSort(arr, 0, n - 1);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    free(arr);
    return time_taken;
}

int main() {
    int sizes[] = {10000, 50000, 200000};
    int num_sizes = sizeof(sizes) / sizeof(sizes[0]);
    int i;

    srand(time(NULL));

    for (i = 0; i < num_sizes; i++) {
        double time = testQuickSort(sizes[i]);
        if (time >= 0) {
            printf("������Ϊ %d ʱ������������ʱ: %f ��\n", sizes[i], time);
        }
    }

    return 0;
}
