#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

// ��ӡ����
void printArr(int arr[], int n) {
    int i;
    for (i = 1; i < n; i++) {
        printf("%d ", arr[i]);
    }
    putchar('\n');
}

// ֱ�Ӳ���������
void InsertSort(int arr[], int n) {
    int i, j;
    // a[0] ��ҪԤ��������Ϊ������
    for (i = 2; i < n; i++) {
        if (arr[i] < arr[i - 1]) {
            // ��� arr[i] < arr[i - 1]��˵�� i ���������ĵ�һ��Ԫ�ص�λ�ã���ʱҪ�� arr[i] ��ֵ�ŵ� arr[0]
            arr[0] = arr[i];
            /* j һ��ʼָ�������������һ��Ԫ�أ�ֻҪ arr[j] ���ڼ����� arr[0]����ô arr[j] ��������һλ (arr[j + 1] = arr[j])��
               һֱ�� arr[j] < arr[0] ʱ��for ѭ��ֹͣ��Ȼ�󽫼����� arr[0] �ŵ� arr[j] �ĺ��� (arr[j + 1] = arr[0])��
               ��ʱ��arr[0] �ճ����ˣ�һ�β����������
            */
            for (j = i - 1; arr[j] > arr[0]; j--) {
                arr[j + 1] = arr[j];
            }
            arr[j + 1] = arr[0];
        }
    }
}

int main() {
    FILE *file;
    int arr[MAX_SIZE];
    int n = 0;

    // �Զ�ȡģʽ���ļ�
    file = fopen("test_data.txt", "r");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return 1;
    }

    // ��ȡ�ļ��е����ݵ�����
    while (fscanf(file, "%d", &arr[n]) != EOF && n < MAX_SIZE) {
        n++;
    }

    // �ر��ļ�
    fclose(file);

    printf("ԭʼ����:\n");
    printArr(arr, n);

    // ���в�������
    InsertSort(arr, n);

    printf("ֱ�Ӳ�������֮�������:\n");
    printArr(arr, n);
    system("pause");
    return 0;
}
