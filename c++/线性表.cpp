#include<iostream>
#include<stdlib.h>
#include<string.h>
using namespace std; 

typedef struct node{
	int num;
	node *next;
	node *prior;
}node;

int main(){
	node *head=NULL;
	head=(node*)malloc(sizeof(node));
	head->next=NULL;
	head->num=0;
	node *pn=NULL,*p=NULL;
	p=head;
	int n=0;
//	cin>>n;
//	for(;n!=0;p=p->next){
//		pn=(node*)malloc(sizeof(node));
//		pn->next=NULL;
//		pn->num=n;
//		p->next=pn;
//		cin>>n;
//	}
//	for(p=head->next;p!=NULL;p=p->next){
//		cout<<p->num<<"\t";
//	}cout<<endl;
//	
//	head->next=NULL;
	
//	p=head;
//	for(cin>>n;n!=0;p=p->next){
//		pn=(node*)malloc(sizeof(node));
//		pn->next=NULL;
//		pn->num=n;
//		p->next=pn;
//		cin>>n;
//	}
//	for(p=head->next;p!=NULL;p=p->next){
//		cout<<p->num<<"\t";
//	}cout<<endl;
//	
//	head->next=NULL;
	
//	p=head;
//	for(cin>>n;n!=0;p=p->next){
//		pn=(node*)malloc(sizeof(node));
//		pn->next=NULL;
//		pn->num=n;
//		p->next=pn;
//		cin>>n;
//	}
//	p->next=head;
//	for(p=head->next;p!=NULL&&p->num!=0;p=p->next){
//		cout<<p->num<<"\t";
//	}cout<<endl;
//	
//	head->next=NULL;
	
	node *pre=NULL,*tail=NULL;
	pre=p=head;
	head->prior=NULL;
	for(cin>>n;n!=0;){
		pn=(node*)malloc(sizeof(node));
		pn->next=NULL;
		pn->num=n;
		p->next=pn;
		pn->prior=p;
		p=p->next;
		tail=p;
		cin>>n;
	}
	for(p=head->next;p!=NULL;p=p->next){
		cout<<p->num<<"\t";
	}cout<<endl;
	for(p=tail;p->prior!=NULL;p=p->prior){
		cout<<p->num<<"\t";
	}cout<<endl;
}
