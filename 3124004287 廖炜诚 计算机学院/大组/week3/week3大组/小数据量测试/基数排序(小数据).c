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

// ��ȡ������ĳһλ��
int getDigit(int num, int digit) {
    int temp = 1;
    int i;
    for (i = 0; i < digit - 1; i++) {
        temp *= 10;
    }
    return (num / temp) % 10;
}

// ��������
void RadixCountSort(int arr[], int n) {
    // �����ҵ������е����ֵ
    int maxValue = arr[0];
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int maxDigit = 0;
    // �������ֵ��λ��
    while (maxValue > 0) {
        maxValue /= 10;
        maxDigit++;
    }
    // ����ָ�����飬��ʾͰ
    int *duckets[10];
    for (i = 0; i < 10; i++) {
        // �����ڴ棬ÿ��Ͱ���Դ洢 n ������
        duckets[i] = (int *)malloc(n * sizeof(int));
    }
    // ��ʱͰ�Ĵ�С��ʼΪ 0
    int ducketSize[10] = {0};
    int digit;
    // �����λ��ʼ����λ��������
    for (digit = 1; digit <= maxDigit; digit++) {
        for (i = 0; i < n; i++) {
            // ��ȡ��ǰ���ֵĵ� digit λ
            int currentDigit = getDigit(arr[i], digit);
            // ����ǰ���ַ����Ӧ��Ͱ��
            duckets[currentDigit][ducketSize[currentDigit]++] = arr[i];
        }
        // ��Ͱ�е����ְ�˳��Ż�ԭ����
        int index = 0;
        for (i = 0; i < 10; i++) {
            int j;
            for (j = 0; j < ducketSize[i]; j++) {
                arr[index++] = duckets[i][j];
            }
            // ���ÿ��Ͱ�Ĵ�С
            ducketSize[i] = 0;
        }
    }
    // �ͷŷ�����ڴ�
    for (i = 0; i < 10; i++) {
        free(duckets[i]);
    }
}

int main() {
    const int dataSize = 100;  // ÿ�����ݼ��Ĵ�С
    const int numTests = 100000;  // ���Դ���

    int *arr = (int *)malloc(dataSize * sizeof(int));
    if (arr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    srand(time(NULL));  // ��ʼ�����������

    clock_t start, end;
    double cpu_time_used;

    start = clock();  // ��¼��ʼʱ��
    int test;
    for (test = 0; test < numTests; test++) {
        // �����������
        int i;
        for (i = 0; i < dataSize; i++) {
            arr[i] = rand() % 1000;  // ���� 0 �� 999 ֮��������
        }

        // ���û���������
        RadixCountSort(arr, dataSize);
    }

    end = clock();  // ��¼����ʱ��

    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("����%d��ÿ��%d�����ݣ��ܹ���ʱ: %f ��\n", numTests, dataSize, cpu_time_used);

    free(arr);  // �ͷŷ�����ڴ�
    system("pause");
    return 0;
}
