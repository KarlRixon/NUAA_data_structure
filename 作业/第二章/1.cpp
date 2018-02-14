#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
	int size,t=0;
	cout<<"输入元素个数：";
	cin>>size;
	int nums[size+1];
	for(int i=0;i<size;i++){
		cin>>nums[i];
	}
	cout<<"输入完成"<<endl;
	for(int i=0;i<size/2;i++){
		t=nums[i];
		nums[i]=nums[size-i-1];
		nums[size-i-1]=t;
	}
	cout<<"逆转结果为："<<endl;
	for(int i=0;i<size;i++){
		cout<<nums[i];
	}
}
