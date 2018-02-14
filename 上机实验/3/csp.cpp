#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

typedef struct Window{
	int num;
	int x1,x2,y1,y2;
	Window *next;
	Window *prior;		//用双向链表 
}Window;

int main(){
	int n=0,m=0,x=0,y=0;
	Window *head=(Window*)malloc(sizeof(Window)),*pn=NULL,*p=NULL,*tail=NULL,*temp=NULL;
	head->num=0;head->x1=head->x2=head->y1=head->y2=0;head->prior=NULL;
	cin>>n>>m;
	p=head;
	for(int i=0;i<n;i++){
		pn=(Window*)malloc(sizeof(Window));
		pn->next=NULL;
		pn->num=i+1;
		cin>>pn->x1>>pn->y1>>pn->x2>>pn->y2;
		p->next=pn;pn->prior=p;p=p->next;
	}
//	for(p=head->next;p;p=p->next)cout<<p->num<<"\t"<<p->x1<<"\t"<<p->y1<<"\t"<<p->x2<<"\t"<<p->y2<<endl;
//	现在p指向链表最后一个元素即最顶窗口
	tail=p;
	for(int i=0;i<m;i++){
		cin>>x>>y;
		while(p->num!=0){
			if(x>=p->x1&&x<=p->x2&&y>=p->y1&&y<=p->y2){
				cout<<p->num<<endl;
				if(p!=tail){
					temp=p;
					p=p->prior;
					p->next=p->next->next;
					p->next->prior=p;
					tail->next=temp;
					temp->prior=tail;
					tail=temp;
				}
				p=tail;break;
			}else p=p->prior;
		}
		if(p->num==0){
			p=tail;cout<<"IGNORED"<<endl; 
		}
	}
}
