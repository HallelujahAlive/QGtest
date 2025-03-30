#include<stdio.h>

/*
直接插入排序：先定义一个数组，该数组需要在0索引处空出一个位置，作为哨兵位置，然后通过for循环划分出有序部分和无序部分，
这时i索引处于无序部分的第一个元素，这时将a[i]暂时放置在哨兵位置(即a[0]=a[i])，然后又通过一个for循环在有序部分从末到尾判断
哨兵元素需要插入的位置 
*/ 

printArr(int arr[],int n){
	int i;
	for(i=1; i < n;i++){
		printf("%d ",arr[i]);
	}
	putchar('\n');
}

//直接插入函数 
void InsertSort(int arr[],int n){
	int i,j;
	//a[0]需要空出来作为哨兵 
	for (i = 2; i < n ;i++){
		if(arr[i] < arr[i-1]){
			//如果a[i]<a[i-1]，说明i来到了无序部分的第一个元素的位置，这时需要将a[i]的值赋给a[0] 
			arr[0] = arr[i];
			/*j索引一开始指向有序部分的最后一个元素，只要a[j]大于哨兵a[0]，那么a[j]就向后移一位(a[j+1]=a[j])，一直到a[j]<a[0]
			时，for循环停止，然后哨兵a[0]插入到a[j]的后面(a[j+1]=a[0]),这时候a[0]又空了出来，继续下一轮排序 
			*/ 
			for(j = i-1; arr[j]> arr[0]; j--){
				arr[j+1] = arr[j];
			}
			arr[j+1]=arr[0];
		}
	}
} 

int main(){
	//数组的第一个需要空出来,所以遍历数组都要从i=1开始 
	int arr[] = {0,9,20,14,27,34,15,9,10,8};
	int n = 10;
	printf("原数组:\n");
	printArr(arr,n);
	InsertSort(arr,n);
	printf("直接插入排序之后数组:\n");
	printArr(arr,n);
	system("pause");
	return 0;
}
