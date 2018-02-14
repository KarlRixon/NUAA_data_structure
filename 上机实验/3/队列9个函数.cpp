#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#define QUEUE_INIT_SIZE 100
#define QUEUE_INCREMENT 10
using namespace std;

typedef struct QNode{
	int data;
	QNode *next;
}QNode;
typedef struct{
	QNode *front;		//队首指针 
	QNode *rear;		//队尾指针 
}LinkQueue;

class Queue{
private:
	LinkQueue Q;
public:
	int InitQueue(){
		Q.front=(QNode*)malloc(sizeof(QNode));
		Q.front->data=0;
		Q.front->next=NULL;
		Q.rear=Q.front;
		cout<<"队列初始化成功"<<endl;
		return 1;
	}
	int DestroyQueue(){
		QNode *q=NULL,*p=NULL;
		q=Q.front;
		for(;q;p=q,q=q->next,free(p));
		Q.front=Q.rear=NULL;
		cout<<"队列销毁成功"<<endl;
		return 1;
	}
	int ClearQueue(){
		DestroyQueue();
		InitQueue();
		cout<<"队列清空成功"<<endl;
		return 1;
	}
	int QueueEmpty(){
		if(Q.front&&Q.front==Q.rear){
			cout<<"队列为空"<<endl;
		}
		else if(Q.front==NULL){
			cout<<"队列不存在"<<endl;
		}
		else{
			cout<<"队列不空"<<endl;
		}
		return 1;
	}
	int QueueLength(){
		QNode *q;
		int n=0;
		for(q=Q.front;q!=Q.rear;q=q->next)n++;
		return n;
	}
	int GetHead(){
		if(Q.front!=Q.rear){
			return Q.front->next->data;
		}else{
			cout<<"队列为空"<<endl;
			return 0; 
		}
	}
	int EnQueue(){
		cout<<"输入入队元素：";
		QNode *qn=NULL;
		qn=(QNode*)malloc(sizeof(QNode));
		cin>>qn->data;
		qn->next=NULL;
		Q.rear->next=qn;
		Q.rear=Q.rear->next;
		return 1;
	}
	int DeQueue(){
		if(Q.front->next==NULL)Q.rear=Q.front;
		else{
			QNode *q=NULL;
			int t=0;
			q=Q.front->next;
			t=q->data;
			Q.front->next=Q.front->next->next;
			free(q);
			return t;
		}
	}
	int QueueTraverse(int(*visit)(int)){
		QNode *q=Q.front->next;
		for(;q!=NULL;q=q->next){
			visit(q->data);
		}
		cout<<endl;
	}
};
int visit(int e){
	cout<<e<<"\t";
}
int main(){
	Queue Q;int n=0;
	while(1){
		cout<<"请选择功能："<<endl;
		cout<<"----1.初始化队列"<<endl;
		cout<<"----2.销毁队列"<<endl;
		cout<<"----3.清空队列"<<endl;
		cout<<"----4.判断是否为空队列"<<endl; 
		cout<<"----5.求队列的长度"<<endl;
		cout<<"----6.查看队首元素"<<endl;
		cout<<"----7.从队首插入元素"<<endl;
		cout<<"----8.弹出队尾元素"<<endl;
		cout<<"----9.从队首到队尾遍历元素"<<endl;
		cout<<"----10.清屏"<<endl;
		cin>>n;
		switch(n){
			case 1:Q.InitQueue();break;
			case 2:Q.DestroyQueue();break;
			case 3:Q.ClearQueue();break;
			case 4:Q.QueueEmpty();break;
			case 5:cout<<Q.QueueLength()<<"个元素"<<endl;break;
			case 6:cout<<Q.GetHead()<<endl;break;
			case 7:Q.EnQueue();break;
			case 8:cout<<Q.DeQueue()<<"元素弹出"<<endl;break;
			case 9:Q.QueueTraverse(visit);break;
			case 10:system("cls");break;
		}
	}
}
