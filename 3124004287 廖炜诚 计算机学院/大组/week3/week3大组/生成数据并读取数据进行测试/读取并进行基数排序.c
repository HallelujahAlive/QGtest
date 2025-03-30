#include <stdio.h>
#include <stdlib.h>

// ��ӡ����
void printArr(int arr[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

// ��ȡ������ĳһλ����
int getDigit(int num, int digit) {
    int temp = 1;
    int i;
    for (i = 0; i < digit - 1; i++) {
        temp *= 10;
    }
    return (num / temp) % 10;
}

// ������������
void RadixCountSort(int arr[], int n) {
    // ���ҵ������е����ֵ
    int maxValue = arr[0];
    int i;
    for (i = 0; i < n; i++) {
        if (arr[i] > maxValue) {
            maxValue = arr[i];
        }
    }
    int maxDigit = 0;
    // ȷ�����ֵ��λ����digit���Ƕ��٣���maxDigit��ʾ���λ��
    while (maxValue > 0) {
        maxValue /= 10;
        maxDigit++;
    }
    // ����ָ�����飬��ʾͰ (ducket)
    int *duckets[10];
    for (i = 0; i < 10; i++) {
        // �����ڴ棬ÿ��Ͱ���Դ洢n������
        duckets[i] = (int *)malloc(n * sizeof(int));
    }
    // ��ʱͰ�Ĵ�С��ʼΪ0
    int ducketSize[10] = {0};
    int digit;
    // ������λ��Ϊ3����ôֻ��Ҫ����3��ѭ��
    for (digit = 1; digit <= maxDigit; digit++) {
        int i;
        for (i = 0; i < n; i++) {
            // ��ȡ��ǰ���ֵĵ�digitλ
            int currentDigit = getDigit(arr[i], digit);
            // ��ȡ��ǰ���ֵĵ�ǰλ֮����Ҫ���ݸ�λ���ֽ���ŵ���Ӧ��Ͱ֮��ȥ
            duckets[currentDigit][ducketSize[currentDigit]++] = arr[i];
        }
        // ���������ַŵ���Ӧ��Ͱ֮����Ҫ��λ��С����ȡ�����Ż�����
        // ��λΪ0�����ֿ�ʼȡ
        int index = 0;
        for (i = 0; i < 10; i++) {
            int j;
            for (j = 0; j < ducketSize[i]; j++) {
                arr[index++] = duckets[i][j];
            }
            // ����ÿ��Ͱ�Ĵ�СΪ0
            ducketSize[i] = 0;
        }
    }
    // �������֮���ͷſռ䣬��ֹռ���ڴ�
    for (i = 0; i < 10; i++) {
        free(duckets[i]);
    }
}

int main() {
    FILE *file;
    int capacity = 10;
    int *arr = (int *)malloc(capacity * sizeof(int));
    int n = 0;

    // ���ļ�
    file = fopen("test_data.txt", "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        return 1;
    }

    // ��ȡ�ļ��е�����
    int num;
    while (fscanf(file, "%d", &num) == 1) {
        if (n >= capacity) {
            // �������������������������
            capacity *= 2;
            arr = (int *)realloc(arr, capacity * sizeof(int));
            if (arr == NULL) {
                perror("�ڴ����ʧ��");
                fclose(file);
                return 1;
            }
        }
        arr[n++] = num;
    }

    //�ر��ļ�
    fclose(file);
    //��ӡԭʼ����
    printf("ԭ����:");
    printArr(arr, n);
    //ִ�л�������
    RadixCountSort(arr, n);
    //��ӡ����������
    printf("�����:");
    printArr(arr, n);
    //�ͷ������ڴ�
    free(arr);
    system("pause");
    return 0;
}
