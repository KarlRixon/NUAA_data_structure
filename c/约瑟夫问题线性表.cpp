#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
	int n=0,s=0,m=0,count=0;
	cout<<"输入总人数：";
	cin>>n;
	cout<<"第几个人开始报数：";
	cin>>s;
	cout<<"报几号的人出列：";
	cin>>m;
	int *p=NULL;
	p=(int *)malloc(sizeof(int)*n);
//	q=p+s-1;
	for(int i=0;i<n;i++){
		*(p+i)=1;
	}
	for(int i=0;count!=n-1;i++){
		if((i+1)%m==0){
			*(p+(i+s)%m)=0;
			count++;
		}
	}
	for(int i=0;i<n;i++){
//		cout<<*(p+i)
		if()
	};
}
