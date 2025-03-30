#include<stdio.h>

/*
快速排序，假设已知一个数组，主要就是选取一个数作为支点(英文就是pivto)，定义low=0，high=n，low++，high-- 
比基点小的放左边，大的放右边，最后将支点放在low与high重合的位置 ...总之最后可以将数组排序好，而且非常快 
*/
 
//打印
void printArr(int arr[],int n){
	int i;
	for(i=0;i<n;i++){
		printf("%d ",arr[i]);
	}
	putchar('\n'); 
} 
 
// 
int partition(int arr[],int low,int high){
	//不用刻意选取，直接将low索引代表的元素作为基点 
	int pivto = arr[low];
	while(low < high){
		while(low<high && arr[high] >= pivto){
			high--;
		}
		arr[low] = arr[high];
		while(low<high && arr[low] <= pivto){
			low++;
	    }
		arr[high]=arr[low];
	}
	arr[low]=pivto;      //其实写成a[high]=pivto也一样，因为low最后跟high重合了
	 
	//不论是返回low还是high都可以，反正最后low和high会重合 
	return low;
}

//分割函数，返回支点的索引
void QuickSort(int arr[],int low,int high){
	//首先要进行判断 
	if(low < high){
		//调用分割(partition)函数，这个函数的作用就是找出pivto经过一轮排序之后所处的位置，并将其位置返回给pivto(支点)
		//只有得到了position之后才能进行递归排序 
		int position = partition(arr,low,high);
		QuickSort(arr,low,position-1);
		QuickSort(arr,position+1,high);
	}
} 

int main(){
	int arr[] = {1,7,4,9,20,14,30,27,19,24};
	int n = 10;
	printf("原数组:\n");
	printArr(arr,n);
	//调用QuickSort函数,一开始low在数组最左边，right在数组最右边 
	QuickSort(arr,0,n-1);
	printf("快速排序后数组:\n");
	printArr(arr,n);
	system("pause");
	return 0;
}
