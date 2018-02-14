#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

typedef struct list{
	int a;
	list *next;
}list;
int count=0;
void show(list *head){
	list *p=head;
	for(int i=0;i<10;i++){
		p=p->next;
		if(p==NULL)return;
		cout<<p->a<<"\t";
	}
}
list *reverse(list *head){
	list *p=head,*q=head;
	int t=0;
	for(int i=0;i<count/2;i++){
		p=p->next;
		for(int j=0;j<count-i;j++){
			q=q->next;
		}
//		cout<<p->a<<"\t"<<q->a<<endl;
		t=p->a;p->a=q->a;q->a=t; 
		q=head;
	}
	return head;
}
int main(){
	list *head,*p,*pn;
	head=p=pn=NULL;
	p=(list *)malloc(sizeof(list));
	p->a=0;
	p->next=NULL;
	head=p;
	int num=0;
	cout<<"输入数字元素（"<<10<<"个以内，输入0结束）："<<endl;
	for(int i=0;i<10;i++){
		cout<<"输入第"<<i+1<<"个数字元素：";
		cin>>num;
		if(num!=0){
			pn=(list*)malloc(sizeof(list));
			pn->a=num;
			pn->next=NULL;
			p->next=pn;
			p=p->next;
			count++;
		}
		else break;
	}
	cout<<"数字序列为："<<endl;
	show(head);
	cout<<endl;
	head=reverse(head);
	cout<<"逆置后的线性表为："<<endl;
	show(head);
}
