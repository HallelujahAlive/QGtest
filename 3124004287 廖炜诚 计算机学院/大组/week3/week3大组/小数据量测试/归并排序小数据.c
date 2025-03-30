#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//��ӡ����
void printArr(int arr[], int n) {
    int i = 0;
    for (; i < n; i++) {
        printf("%d ", arr[i]);
    }
    //��ӡ��֮����
    putchar('\n');
}

//�ϲ�����
void merge(int arr[], int tempArr[], int left, int mid, int right) {
    //�����������ʼ����
    int l_left = left;
    //�����������ʼԪ��, ��mid+1
    int l_right = mid + 1;
    //��ʱ����Ԫ�ص�����
    int t_left = left;
    // ��ʼ�ϲ�
    while (l_left <= mid && l_right <= right) {
        if (arr[l_left] < arr[l_right]) {  //�����������ĵ�һ��Ԫ�ظ�С����ô��Ԫ���ȷ�����ʱ����
            tempArr[t_left++] = arr[l_left++];
        } else {
            tempArr[t_left++] = arr[l_right++];
        }
    }
    //����������ʣ��Ԫ��ʱ����ʣ��Ԫ��ȫ��������ʱ����
    while (l_left <= mid) {
        tempArr[t_left++] = arr[l_left++];
    }
    //����������ʣ��Ԫ��ʱ����ʣ��Ԫ��ȫ��������ʱ����
    while (l_right <= right) {
        tempArr[t_left++] = arr[l_right++];
    }
    //����ʱ���鸴�ƻ�ԭ����
    while (left <= right) {
        arr[left] = tempArr[left];
        left++;
    }
}

//��ֺ͵ݹ�������Ҫ�ǽ�ԭʼ����ͨ���ݹ��ֳ�һ����С������
void msort(int arr[], int tempArr[], int left, int right) {
    if (left < right) {
        //�����м�λ�ã����м��Լ��м�֮ǰ��Ԫ�ع��ɵ��������Ϊ�������飬mid+1֮���Ԫ�ع��ɵ��������Ϊ��������
        int mid = (left + right) / 2;
        //��ʼ�ݹ�����������
        msort(arr, tempArr, left, mid);
        //�ݹ�����������, ע�⣬�����������ʼ�����Ǵ�mid+1��ʼ�ģ�mid������Ӧ��Ԫ��������������
        msort(arr, tempArr, mid + 1, right);
        //���֮�󣬱�ȻҪ���кϲ�����ʱ��Ҫ�õ�merge����
        merge(arr, tempArr, left, mid, right);
    }
}

//�鲢��������������Ҫ�Ƿ����ڴ��Լ����ò�ֺ͵ݹ�����
void msort_merge(int arr[], int n) {
    int* tempArr = (int*)malloc(n * sizeof(int));
    if (tempArr) {
        //�����ڴ�ɹ�����ô���ò�ֺ͵ݹ�����msort
        msort(arr, tempArr, 0, n - 1);
        //�������֮����Ҫ�ͷſռ䣬�ͷ��ڴ�
        free(tempArr);
    } else {
        printf("�����ڴ�ʧ��!����ʧ��!");
    }
}

int main() {
    const int dataSize = 100;  // ������
    const int testTimes = 100000;  // ���Դ���

    int arr[dataSize];
    clock_t start, end;
    double cpu_time_used;

    //��ʼ�����������
    srand(time(NULL));

    start = clock();  //��¼��ʼʱ��
    int i;
    for (i = 0; i < testTimes; i++) {
        //�����������
        int j;
        for (j = 0; j < dataSize; j++) {
            arr[j] = rand();
        }
        //���й鲢����
        msort_merge(arr, dataSize);
    }

    end = clock();  //��¼����ʱ��
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;  // ������ʱ

    printf("�鲢����%d�Σ�ÿ��%d�����ݣ��ܹ���ʱ: %f ��\n", testTimes, dataSize, cpu_time_used);
    system("pause");
    return 0;
}
