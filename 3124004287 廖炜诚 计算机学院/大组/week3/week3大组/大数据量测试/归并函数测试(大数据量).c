#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ��ӡ����
void printArr(int arr[], int n) {
    int i = 0;
    for (; i < n; i++) {
        printf("%d ", arr[i]);
    }
    // ��ӡ��֮����
    putchar('\n');
}

// �ϲ�����
void merge(int arr[], int tempArr[], int left, int mid, int right) {
    // �����������ʼ����
    int l_left = left;
    // �����������ʼԪ�أ��� mid+1
    int l_right = mid + 1;
    // ��ʱ����Ԫ�ص�����
    int t_left = left;
    // ��ʼ�ϲ�
    while (l_left <= mid && l_right <= right) {
        if (arr[l_left] < arr[l_right]) { // �����������ĵ�һ��Ԫ�ظ�С����ô��Ԫ���ȷ�����ʱ����
            tempArr[t_left++] = arr[l_left++];
        } else {
            tempArr[t_left++] = arr[l_right++];
        }
    }
    // ����������黹��ʣ��Ԫ�أ�����ȫ��������ʱ����
    while (l_left <= mid) {
        tempArr[t_left++] = arr[l_left++];
    }
    // ����������黹��ʣ��Ԫ�أ�����ȫ��������ʱ����
    while (l_right <= right) {
        tempArr[t_left++] = arr[l_right++];
    }
    // ����ʱ���鸴�ƻ�ԭ����
    while (left <= right) {
        arr[left] = tempArr[left];
        left++;
    }
}

// �ָ�͵ݹ����
void msort(int arr[], int tempArr[], int left, int right) {
    if (left < right) {
        // �ָ����飬mid ����֮ǰ��Ԫ������������飬mid+1 ����֮���Ԫ�������������
        int mid = (left + right) / 2;
        // ��ʼ�ݹ�ָ���������
        msort(arr, tempArr, left, mid);
        // �ݹ�ָ��������飬ע�⣬�����������ʼ������ mid+1��mid ������Ӧ��Ԫ��������������
        msort(arr, tempArr, mid + 1, right);
        // �ָ����֮����Ҫ���кϲ���������ʱ��Ҫ�õ� merge ����
        merge(arr, tempArr, left, mid, right);
    }
}

// �鲢��������������Ҫ��������ڴ��Լ����÷ָ�ͺϲ�����
void msort_merge(int arr[], int n) {
    int* tempArr = (int*)malloc(n * sizeof(int));
    if (tempArr) {
        // �ڴ����ɹ�����ô���÷ָ�ͺϲ����� msort
        msort(arr, tempArr, 0, n - 1);
        // �������֮����Ҫ�ͷſռ䣬�����ڴ�
        free(tempArr);
    } else {
        printf("�����ڴ�ʧ��!����ʧ��!");
    }
}

// �����������
void generateRandomArray(int arr[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        arr[i] = rand();
    }
}

int main() {
    int sizes[] = {10000, 50000, 200000};
    int numSizes = sizeof(sizes) / sizeof(sizes[0]);
    int i;
    for (i = 0; i < numSizes; i++) {
        int n = sizes[i];
        int* arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("�ڴ����ʧ�ܣ��޷����Դ�СΪ %d �����顣\n", n);
            continue;
        }

        //�����������
        generateRandomArray(arr, n);
        //��¼��ʼʱ��
        clock_t start = clock();
        //���ù鲢������
        msort_merge(arr, n);

        //��¼����ʱ��
        clock_t end = clock();

        //������ʱ����λ�����룩
        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC * 1000;
        printf("������Ϊ %d ʱ���鲢������ʱ: %.2f ����\n", n, time_taken);
        //�ͷ������ڴ�
        free(arr);
    }
    system("pause");
    return 0;
}
