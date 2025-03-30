#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��ӡ���麯��
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
    // a[0] ��Ҫ�ճ�����Ϊ�ڱ�
    for (i = 2; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            // ��� arr[i] < arr[i - 1]��˵�� i ���������ĵ�һ��Ԫ�ص�λ�ã���ʱҪ�� arr[i] ��ֵ�ŵ� arr[0]
            arr[0] = arr[i];
            /* j һ��ʼָ�������������һ��Ԫ�أ�ֻҪ arr[j] �����ڱ� arr[0]����ô arr[j] ����ƶ�һλ (arr[j + 1] = arr[j])��
               һֱ�� arr[j] < arr[0] ʱ��for ѭ��ֹͣ��Ȼ���ڱ� arr[0] �ŵ� arr[j] �ĺ��� (arr[j + 1] = arr[0])��
               ��ʱ a[0] �ճ�����һ�β���������� 
            */
            for (j = i - 1; arr[j] > arr[0]; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = arr[0];
        }
    }
}

int main() {
    const int dataSize = 100;  //������
    const int sortTimes = 100000;  //�������

    int arr[dataSize + 1];  //���飬��һ��λ����Ϊ�ڱ�
    clock_t start, end;
    double cpu_time_used;

    //��ʼ�����������
    srand(time(NULL));

    //��¼��ʼʱ��
    start = clock();

    //���� 100k ������
    int k;
    for (k = 0; k < sortTimes; k++) {
        //���� 100 ���������
        int i;
        for (i = 1; i <= dataSize; i++) {
            arr[i] = rand() % 1000;  //���� 0��999֮��������
        }

        //���в�������
        InsertSort(arr, dataSize + 1);
    }

    // ��¼����ʱ��
    end = clock();

    // ����������ʱ
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // ���������ʱ
    printf("��������%d��ÿ��%d�����ݣ��ܹ���ʱ: %f��\n", sortTimes, dataSize, cpu_time_used);
    system("pause");
    return 0;
}
