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
		cout<<"����Ԫ�ظ�����";
		cin>>n;
		if(n>0)break; 
	}
	list *nms=NULL;
	nms=(list*)malloc(sizeof(list));
	nms->size=n;
	nms->nums=(int*)malloc(sizeof(int)*n);
	cout<<"����Ԫ�أ�"<<endl;
	for(int i=0;i<n;i++){
		cin>>num;
		*(nms->nums+i)=num;
	}
	while(1){
		cout<<"ɾ��Ԫ�ص���ʼ�±꣺";
		cin>>bgn;
		if(bgn>0&&bgn<=n)break;
	}
	while(1){
		cout<<"ɾ���ַ����Ĵ�С��";
		cin>>size;
		if(size>=0)break;
	}
	//��ʼɾ������
	int *p=(nms->nums+bgn-1);
	int *q=(nms->nums+n-1);
	int i=0;
	if((p+size)>=q){
		n=nms->size=bgn;
	}else{
		for(;(p+size)<=q;p++){
			*p=*(p+size);
			i++;
		}
	}
	n=nms->size=n-size;
	//����ɾ������ 
	for(int i=0;i<n;i++){
		cout<<*(nms->nums+i)<<"\t";
	}
}
