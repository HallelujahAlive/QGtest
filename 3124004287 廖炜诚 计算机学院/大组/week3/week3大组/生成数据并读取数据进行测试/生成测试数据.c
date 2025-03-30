#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NUMBER 1000  // 生成的随机数的最大值
#define DATA_COUNT 10    // 生成的数据数量

int main() {
    FILE *file;
    int i;

    // 以写入模式打开文件
    file = fopen("test_data.txt", "w");
    if (file == NULL) {
        printf("无法打开文件！\n");
        return 1;
    }
    // 初始化随机数种子
    srand(time(NULL));
    // 写入一个占位符 0
    fprintf(file, "0 ");
    //生成随机数并写入文件
    for (i = 0; i < DATA_COUNT; i++) {
        int num = rand() % MAX_NUMBER + 1;
        fprintf(file, "%d ", num);
    }

    // 关闭文件
    fclose(file);

    printf("测试数据已生成并保存到 test_data.txt 文件中。\n");
    system("pause");
    return 0;
}
