#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct list{
	int num;
	list *next;
}list;

int main(){
	int num=0,temp=0;
	list *head=NULL;
	list *p=NULL,*q=NULL;
	head=(list*)malloc(sizeof(list));
	head->next=NULL;
	head->num=0;
	p=head;
	cout<<"输入非递减线性表的元素（输入0结束）："<<endl;
	while(1){
		cin>>num;
		if(num==0)break;
		if(num<temp){
			cout<<"输入数字小于前一个"<<endl;
			continue;
		}
		if(num!=0){
			temp=num;
			q=(list *)malloc(sizeof(list));
			q->num=num;
			q->next=NULL;
			p->next=q;
			p=p->next;
		}
	}
	//开始删除
	p=head;
	q=p->next;
	while(p->next->next){
		p=p->next;
		q=p->next;
		if(p->num==q->num){
			p->next=q->next;
		}
	}
	//结束删除 
	p=head;
	while(p=p->next){
		cout<<p->num<<"\t"; 
	}
	cout<<endl;
}
