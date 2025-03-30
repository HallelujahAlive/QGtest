#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��ӡ����
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

//��������
int partition(int arr[], int low, int high) {
    //ͨ��ѡ���һ��Ԫ����Ϊ��׼
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
    arr[low] = pivto;  //ʵ����д a[high]=pivto Ҳһ������Ϊ low �� high �Ѿ��غ�
    //���ػ�׼������λ��
    return low;
}

//����������
void QuickSort(int arr[], int low, int high) {
    //��Ҫ�����ж�
    if (low < high) {
        //ͨ�����������������Ϊ�����֣����ҵ���׼������λ��
        int position = partition(arr, low, high);
        QuickSort(arr, low, position - 1);
        QuickSort(arr, position + 1, high);
    }
}

//�����������
void generateRandomArray(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

int main() {
    const int dataSize = 100;  //������
    const int iterations = 100000;  //�������
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

    printf("��%d�����ݽ���%d�����������ʱ: %f ��\n", dataSize, iterations, cpu_time_used);
    system("pause");
    return 0;
}
