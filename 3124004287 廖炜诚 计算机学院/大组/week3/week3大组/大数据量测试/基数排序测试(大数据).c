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

//��ȡһ�����ֵ�ĳһλ
int getDigit(int num, int digit) {
    int temp = 1;
    int i;
    for (i = 0; i < digit - 1; i++) {
        temp *= 10;
    }
    return (num / temp) % 10;
}

//������������
void RadixCountSort(int arr[], int n) {
    //�����ҵ������е����ֵ
    int maxValue = arr[0];
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int maxDigit = 0;
    //�������ֵ��λ��
    while (maxValue > 0) {
        maxValue /= 10;
        maxDigit++;
    }
    //����ָ�����飬��ʾͰ
    int *duckets[10];
    for (i = 0; i < 10; i++) {
        //�����ڴ棬ÿ��Ͱ���Դ洢 n ������
        duckets[i] = (int *)malloc(n * sizeof(int));
    }
    //Ͱ�Ĵ�С��ʼΪ 0
    int ducketSize[10] = {0};
    int digit;
    //����λ����������
    for (digit = 1; digit <= maxDigit; digit++) {
        int i;
        for (i = 0; i < n; i++) {
            //��ȡ��ǰ���ֵĵ�ǰλ��
            int currentDigit = getDigit(arr[i], digit);
            //�����ַ����Ӧ��Ͱ��
            duckets[currentDigit][ducketSize[currentDigit]++] = arr[i];
        }
        //��Ͱ�е����ְ�˳��Ż�����
        int index = 0;
        for (i = 0; i < 10; i++) {
            int j;
            for (j = 0; j < ducketSize[i]; j++) {
                arr[index++] = duckets[i][j];
            }
            //���ÿ��Ͱ�Ĵ�С
            ducketSize[i] = 0;
        }
    }
    //�ͷ��ڴ�
    for (i = 0; i < 10; i++) {
        free(duckets[i]);
    }
}

//�����������
void generateRandomArray(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

//���Ժ���
void testRadixCountSort(int n) {
    int *arr = (int *)malloc(n * sizeof(int));
    generateRandomArray(arr, n);

    clock_t start = clock();
    RadixCountSort(arr, n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("���� %d ��Ԫ����ʱ: %f ��\n", n, time_taken);

    free(arr);
}

int main() {
    srand(time(NULL));

    // ���Բ�ͬ������
    testRadixCountSort(10000);
    testRadixCountSort(50000);
    testRadixCountSort(200000);
    system("pause");
    return 0;
}
