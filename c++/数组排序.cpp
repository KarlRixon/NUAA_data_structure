#include<iostream>
using namespace std;
#include<stdlib.h>
#include<iomanip>
#include<time.h>
 
int n;

int* sortsb(int arr[]){
	int t;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i]>arr[j]){
				t=arr[i];arr[i]=arr[j];arr[j]=t;
			}
		}
	}
	return arr;
}
int* sortbs(int arr[]){
	int t;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(arr[i]<arr[j]){
				t=arr[i];arr[i]=arr[j];arr[j]=t;
			}
		}
	}
	return arr;
}
void display(int *arr){
	for(int i=0;i<n;i++){
		if((i+5)%5==0){
			cout<<endl;
		}
		cout<<left<<setw(7)<<i;
		cout<<"->"<<left<<setw(10)<<arr[i];
	}
}

int main(){
	srand((unsigned)time(NULL));
	cout<<"输入随机数组元素个数：";
	cin>>n;
	int arr[n+1];
	for(int i=0;i<n;i++){
		arr[i]=rand();
	}
	cout<<"产生的随机数组为（下标->值）："<<endl;
	display(arr);
	cout<<endl;
	cout<<"选择排序方式（1.从小到大 2.从大到小）：";
	int w=0;
	cin>>w;
	if(w==1){
		cout<<"排序后的数组："<<endl;
		display(sortsb(arr));
	}else if(w==2){
		cout<<"排序后的数组："<<endl;
		display(sortbs(arr));
	}
}
