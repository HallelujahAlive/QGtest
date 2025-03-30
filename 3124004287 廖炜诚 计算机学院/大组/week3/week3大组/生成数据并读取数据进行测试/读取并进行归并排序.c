#include <stdio.h>
#include <stdlib.h>

// ��ӡ����
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
    // �����������ʼԪ�أ��� mid+1 ��ʼ
    int l_right = mid + 1;
    //��ʱ����Ԫ�ص�����
    int t_left = left;
    //��ʼ�ϲ�
    while (l_left <= mid && l_right <= right) {
        if (arr[l_left] < arr[l_right]) {  //�����������ĵ�һ��Ԫ�ظ�С����ô��Ԫ���ȷ�����ʱ����
            tempArr[t_left++] = arr[l_left++];
        } else {
            tempArr[t_left++] = arr[l_right++];
        }
    }
    //�������黹��ʣ��Ԫ��ʱ������ȫ��������ʱ����
    while (l_left <= mid) {
        tempArr[t_left++] = arr[l_left++];
    }
    //�������黹��ʣ��Ԫ��ʱ������ȫ��������ʱ����
    while (l_right <= right) {
        tempArr[t_left++] = arr[l_right++];
    }
    //����ʱ�����е�Ԫ�ظ��ƻ�ԭ����
    while (left <= right) {
        arr[left] = tempArr[left];
        left++;
    }
}

// ���κ͵ݹ����Ҫ���̣���ԭʼ����ͨ���ݹ鲻�ϲ�ֳ�һ����С��
void msort(int arr[], int tempArr[], int left, int right) {
    if (left < right) {
        // �����м����������м������Լ��м�����֮ǰ��Ԫ�ع��ɵ��������Ϊ�������飬�м�����+1֮���Ԫ�ع��ɵ��������Ϊ��������
        int mid = (left + right) / 2;
        // ��ʼ�ݹ�����������
        msort(arr, tempArr, left, mid);
        // �ݹ����������飬ע�⣬�����������ʼ�����Ǵ� mid+1 ��ʼ�ģ�mid ������Ӧ��Ԫ��������������
        msort(arr, tempArr, mid + 1, right);
        // ������֮�󣬱�ȻҪ���кϲ�����ʱ��Ҫ�õ� merge ����
        merge(arr, tempArr, left, mid, right);
    }
}

//�鲢�������ں�������Ҫ��������ڴ��Լ����÷��κͺϲ�����
void msort_merge(int arr[], int n) {
    int* tempArr = (int*)malloc(n * sizeof(int));
    if (tempArr) {
        //�ڴ����ɹ�����ô���÷��κͺϲ����� msort
        msort(arr, tempArr, 0, n - 1);
        //�����Ҫ�ͷ���ʱ�ռ䣬�ͷ��ڴ�
        free(tempArr);
    } else {
        printf("�����ڴ�ʧ��!����ʧ��!");
    }
}

//���ļ��ж�ȡ����
int readDataFromFile(const char* filename, int** arr) {
    FILE* file = fopen("test_data.txt", "r");
    if (file == NULL) {
        perror("�޷����ļ�");
        return -1;
    }

    int count = 0;
    int num;
    //�ȼ����ļ��е���������
    while (fscanf(file, "%d", &num) == 1) {
        count++;
    }

    //�����ڴ����洢����
    *arr = (int*)malloc(count * sizeof(int));
    if (*arr == NULL) {
        perror("�ڴ����ʧ��");
        fclose(file);
        return -1;
    }

    // ���ļ�ָ�����õ��ļ���ͷ
    rewind(file);

    // ��ȡ���ݵ�����
    int i;
    for (i = 0; i < count; i++) {
        if (fscanf(file, "%d", &(*arr)[i]) != 1) {
            perror("��ȡ�ļ�����ʧ��");
            free(*arr);
            fclose(file);
            return -1;
        }
    }

    fclose(file);
    return count;
}

int main() {
    int* arr;
    int n = readDataFromFile("test_data.txt", &arr);
    if (n == -1) {
        return 1;
    }

    printf("ԭ����:\n");
    printArr(arr, n);

    // ���ù鲢������
    msort_merge(arr, n);

    // ����֮���ٴδ�ӡ���飬����Ƿ�����ɹ�
    printf("�鲢����֮�������:\n");
    printArr(arr, n);

    // �ͷ������ڴ�
    free(arr);
    system("pause");
    return 0;
}
