#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
	int size,t=0;
	cout<<"����Ԫ�ظ�����";
	cin>>size;
	int nums[size+1];
	for(int i=0;i<size;i++){
		cin>>nums[i];
	}
	cout<<"�������"<<endl;
	for(int i=0;i<size/2;i++){
		t=nums[i];
		nums[i]=nums[size-i-1];
		nums[size-i-1]=t;
	}
	cout<<"��ת���Ϊ��"<<endl;
	for(int i=0;i<size;i++){
		cout<<nums[i];
	}
}
