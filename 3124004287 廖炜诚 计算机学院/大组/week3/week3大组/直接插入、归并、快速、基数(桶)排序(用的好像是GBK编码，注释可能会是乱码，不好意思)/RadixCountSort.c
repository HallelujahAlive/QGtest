#include<stdio.h>
#include<stdlib.h>

/*
基数排序(桶排序):基数排序是不用比较的排序方法，用图来解释的话还挺简单的，但是我觉得代码写起来很麻烦。
简单讲就是一开始想找出数组中的最大数，然后求出这个最大数的位数，这个最大位数就是需要进行的趟数。
计算出最大数的位数之后，就得定义桶，比如说，我们用十进制数，那么就需要定义十个指针数组，每个指针指向一个数组，每个数组
代表一个桶，桶的大小由数组中存储的数的多少(n)来决定 
*/

//打印
void printArr(int arr[],int n){
	int i;
	for(i=0; i < n;i++){
		printf("%d ",arr[i]);
	}
	putchar('\n');
} 

//获取传过来的整数的某个位数
int getDigit(int num,int digit){
	int temp = 1;
	int i;
	for(i = 0;i < digit - 1;i++){
		temp *= 10;
	}
	return (num/temp)%10;
} 


//基数排序函数
void RadixCountSort(int arr[],int n){
	//首先找出数组中最大数
	int maxValue = arr[0];
	int i;
	for (i=0;i < n;i++) {
		if(arr[i]>maxValue){
			maxValue = arr[i];
		}
	} 
	int maxDigit;
	//计算出最大数的位数(digit)是多少，用maxDigit表示最大数的位数
	while(maxValue > 0){
		maxValue /= 10;
		maxDigit++;
	} 
	//定义指针数组,来表示桶 (ducket) 
	int *duckets[10];
	for(i=0;i < 10;i++){
		//分配内存,每个桶都可以存储n个整数 
		duckets[i] = (int*)malloc(n*sizeof(int)); 
	}
	//暂时令桶的大小为零 
	int ducketSize[10] = {0};
	int digit;
	//加入最大位数为3,那么就只需要进行三趟大循环 
	for (digit = 1;digit <= maxDigit; digit++){
		int i;
		for(i = 0;i < n; i++){
			//调用求位数的函数，得到该数第digit位数
			int currentDigit = getDigit(arr[i],digit); 
			//获取当前整数的当前位数之后，就需要根据改位数将整数放到对应的桶之中去了
			duckets[currentDigit][ducketSize[currentDigit]++] = arr[i]; 
		}
		//将数组所有数放到对应的桶之后，就需要按位数从小到大取出放到数组中
		//从位数为0的数组开始取 
		int index = 0;
		for(i = 0;i < 10;i++){
			int j;
			for(j = 0;j < ducketSize[i];j++){
				arr[index++] = duckets[i][j];
			}
			//重新将每个桶的大小置为0
			ducketSize[i] = 0;
		}  
	} 
	//排序完成之后，释放空间，以免占用内存
	for (i = 0;i < 10;i++){
		free(duckets[i]);
	} 
}

int main(){
	int arr[] = {14,50,45,60,101,123,23,89,40,158};
	int n = 10;
	//打印原数组 
	printArr(arr,n);
	//调用基数排序函数
	RadixCountSort(arr,n); 
	//打印排序之后的数组
	printArr(arr,n); 
	system("pause");
	return 0;
}
