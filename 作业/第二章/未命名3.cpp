#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct list{
	int *nums;
	int size;
}list;

int main(){
	int n=0,num=0,size=0,bgn=0;
	while(1){
		cout<<"输入元素个数：";
		cin>>n;
		if(n>0)break; 
	}
	list *nms=NULL;
	nms=(list*)malloc(sizeof(list));
	nms->size=n;
	nms->nums=(int*)malloc(sizeof(int)*n);
	cout<<"输入元素："<<endl;
	for(int i=0;i<n;i++){
		cin>>num;
		*(nms->nums+i)=num;
	}
	for(int i=0;i<n;i++){
		cout<<*(nms->nums+i)<<"\t";
	}
}
