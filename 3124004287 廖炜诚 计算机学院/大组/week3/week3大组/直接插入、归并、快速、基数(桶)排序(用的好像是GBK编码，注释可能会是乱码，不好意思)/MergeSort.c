#include<stdio.h>
#include<stdlib.h> //由于要分配内存，所以需要用到

/*
归并主要就是分成划分和合并部分，划分部分主要用到了递归的思想 ，排序部分我放在了合并函数 
*/

//打印函数
void printArr(int arr[],int n){
	int i=0;
	for(;i<n;i++){
		printf("%d ",arr[i]);
	}
	//打印完之后换行 
	putchar('\n');
} 

//合并函数
void merge(int arr[],int tempArr[],int left,int mid,int right){
	//定义左半区最左边下标
	int l_left = left;
	//定义右半区最左边元素,即mid+1 
	int l_right = mid+1; 
	//临时数组元素的下标
	int t_left = left;
	//开始合并 
	while(l_left <= mid && l_right <=  right){
		if(arr[l_left] < arr[l_right]){  //如果左半区第一个元素更小，那么这个元素先进入临时 
			tempArr[t_left++] = arr[l_left++];
		} else {
			tempArr[t_left++] = arr[l_right++];
		}
	}
	//将左半区剩余元素放入临时数组(前提是有剩余元素)
	while(l_left <= mid){
		tempArr[t_left++]=arr[l_left++];
	}
	//将右半区剩余元素放入临时数组(前提是有剩余元素)
	while(l_right <= right){
		tempArr[t_left++]=arr[l_right++];
	}
	//把临时数组放入原数组
	while(left<=right){
		arr[left] = tempArr[left];
		left++;
	} 
} 

//划分函数，主要作用就是将原始数组通过递归将数组划分成一个个小块 
void msort(int arr[],int tempArr[],int left,int right){
	if (left < right){
		//定义划分界限，包括mid以及mid之前的元素我们称之为左半区，mid+1之后的元素组成的数组我们称之为右半区 
		int mid = (left + right)/2;
		//开始递归划分数组
		//划分左半区 
		msort(arr,tempArr,left,mid);
		//划分右半区,注意，这里右半区的下标是从mid+1开始的，mid下标对应的元素是属于左半区的 
		msort(arr,tempArr,mid+1,right);
		//划分完之后，肯定要排序合并，这时候就要用到merge函数
		merge(arr,tempArr,left,mid,right);
	}
}


//归并排序数组的入口：这个入口的功能主要就是分配内存以及进入划分函数 
void msort_merge(int arr[],int n){
	int* tempArr = (int*)malloc(n*sizeof(int));
	if (tempArr){
		//如果分配内存成功，那么进入划分函数msort 
		msort(arr,tempArr,0,n-1);
		//最后不要忘了释放空间，避免占用内存 
		free(tempArr);
	} else {
		printf("分配内存失败!排序失败!");
	}
} 

int main(){
	//暂时定义一个比较小的数组 
	int arr[] = {1,6,4,2,9,7,20,5,14,8};
	int n=10;
	printf("原数组:\n");
	printArr(arr,n);
	//调用入口函数 
	msort_merge(arr,n);
	//排序完成之后再次打印函数，检查是否排序成功
	printf("归并排序之后数组:\n");
	printArr(arr,n);
	system("pause");
	return 0; 
} 
