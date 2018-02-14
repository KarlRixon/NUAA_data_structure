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
	cout<<"�����������Ԫ�ظ�����";
	cin>>n;
	int arr[n+1];
	for(int i=0;i<n;i++){
		arr[i]=rand();
	}
	cout<<"�������������Ϊ���±�->ֵ����"<<endl;
	display(arr);
	cout<<endl;
	cout<<"ѡ������ʽ��1.��С���� 2.�Ӵ�С����";
	int w=0;
	cin>>w;
	if(w==1){
		cout<<"���������飺"<<endl;
		display(sortsb(arr));
	}else if(w==2){
		cout<<"���������飺"<<endl;
		display(sortbs(arr));
	}
}
