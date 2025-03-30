#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��ӡ����
void printArr(int arr[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

//ֱ�Ӳ���������
void InsertSort(int arr[], int n) {
    int i, j;
    //a[0]��ҪԤ����Ϊ�ڱ�
    for (i = 2; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            //��� arr[i] < arr[i - 1]��˵�� i ���������ĵ�һ��Ԫ�ص�λ�ã���ʱ��Ҫ�� arr[i] ��ֵ�ŵ� arr[0]
            arr[0] = arr[i];
            /*j����һ��ʼָ�����򲿷ֵ����һ��Ԫ�أ�ֻҪa[j]�����ڱ�a[0]����ôa[j]�������һλ(a[j+1]=a[j])��һֱ��a[j]<a[0]
			ʱ��forѭ��ֹͣ��Ȼ���ڱ�a[0]���뵽a[j]�ĺ���(a[j+1]=a[0]),��ʱ��a[0]�ֿ��˳�����������һ������ 
			*/ 
            for (j = i - 1; arr[j] > arr[0]; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = arr[0];
        }
    }
}

//�����������
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
            printf("�ڴ����ʧ��\n");
            return 1;
        }

        //�����������
        generateRandomArray(arr, n);
        //��¼��ʼʱ��
        clock_t start = clock();
        //ִ�в�������
        InsertSort(arr, n);
        // ��¼����ʱ��
        clock_t end = clock();
        //������ʱ���룩
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
        printf("������Ϊ %d ʱ������������ʱ: %f ��\n", n, time_taken);
        //�ͷ��ڴ�
        free(arr);
    }
    system("pause");
    return 0;
}
