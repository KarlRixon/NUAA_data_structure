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
	QNode *front;		//����ָ�� 
	QNode *rear;		//��βָ�� 
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
		cout<<"���г�ʼ���ɹ�"<<endl;
		return 1;
	}
	int DestroyQueue(){
		QNode *q=NULL,*p=NULL;
		q=Q.front;
		for(;q;p=q,q=q->next,free(p));
		Q.front=Q.rear=NULL;
		cout<<"�������ٳɹ�"<<endl;
		return 1;
	}
	int ClearQueue(){
		DestroyQueue();
		InitQueue();
		cout<<"������ճɹ�"<<endl;
		return 1;
	}
	int QueueEmpty(){
		if(Q.front&&Q.front==Q.rear){
			cout<<"����Ϊ��"<<endl;
		}
		else if(Q.front==NULL){
			cout<<"���в�����"<<endl;
		}
		else{
			cout<<"���в���"<<endl;
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
			cout<<"����Ϊ��"<<endl;
			return 0; 
		}
	}
	int EnQueue(){
		cout<<"�������Ԫ�أ�";
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
		cout<<"��ѡ���ܣ�"<<endl;
		cout<<"----1.��ʼ������"<<endl;
		cout<<"----2.���ٶ���"<<endl;
		cout<<"----3.��ն���"<<endl;
		cout<<"----4.�ж��Ƿ�Ϊ�ն���"<<endl; 
		cout<<"----5.����еĳ���"<<endl;
		cout<<"----6.�鿴����Ԫ��"<<endl;
		cout<<"----7.�Ӷ��ײ���Ԫ��"<<endl;
		cout<<"----8.������βԪ��"<<endl;
		cout<<"----9.�Ӷ��׵���β����Ԫ��"<<endl;
		cout<<"----10.����"<<endl;
		cin>>n;
		switch(n){
			case 1:Q.InitQueue();break;
			case 2:Q.DestroyQueue();break;
			case 3:Q.ClearQueue();break;
			case 4:Q.QueueEmpty();break;
			case 5:cout<<Q.QueueLength()<<"��Ԫ��"<<endl;break;
			case 6:cout<<Q.GetHead()<<endl;break;
			case 7:Q.EnQueue();break;
			case 8:cout<<Q.DeQueue()<<"Ԫ�ص���"<<endl;break;
			case 9:Q.QueueTraverse(visit);break;
			case 10:system("cls");break;
		}
	}
}
