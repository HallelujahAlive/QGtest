#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 1000  // ���ɵ�����������ֵ
#define DATA_COUNT 10    // ���ɵ���������

int main() {
    FILE *file;
    int i;

    // ��д��ģʽ���ļ�
    file = fopen("test_data.txt", "w");
    if (file == NULL) {
        printf("�޷����ļ���\n");
        return 1;
    }
    // ��ʼ�����������
    srand(time(NULL));
    // д��һ��ռλ�� 0
    fprintf(file, "0 ");
    //�����������д���ļ�
    for (i = 0; i < DATA_COUNT; i++) {
        int num = rand() % MAX_NUMBER + 1;
        fprintf(file, "%d ", num);
    }

    // �ر��ļ�
    fclose(file);

    printf("�������������ɲ����浽 test_data.txt �ļ��С�\n");
    system("pause");
    return 0;
}
