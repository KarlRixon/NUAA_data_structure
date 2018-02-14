#include<iostream>
#include <stack>
#include <queue>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef struct BiTNode{
	int data;
	BiTNode *lchild,*rchild;
}BiTNode;
typedef struct BTNQ{
	BiTNode *p;
	BTNQ *next;
}BTNQ;
int num=0; 

class BiTree{
private:
	BiTNode *bt;
	void CBT(BiTNode* &root){			//ע�������  * & 
		cout<<"����ڵ�Ԫ�أ�����0������Ԫ�أ���";
		cin>>num;
		if(num==0){
			root=NULL;return;
		}
		else{
			root=(BiTNode*)malloc(sizeof(BiTNode));
			root->data=num;root->lchild=root->rchild=NULL;
			CBT(root->lchild);
			CBT(root->rchild);
		}
	}
	void Destroy(BiTNode* &T){
		if(T){
			if(T->lchild){Destroy(T->lchild);}
			if(T->rchild){Destroy(T->rchild);}
			free(T);T=NULL;
		}
	}
public:
	void CreateBiTree(){
		CBT(bt);cout<<"�����������ɹ�"<<endl;
	}
	void InOrderTraverse(){
		stack<BiTNode *> node;
		BiTNode *n=bt;
		while (n != NULL || !node.empty()) {
			while (n != NULL) {
				node.push(n);
				n = n->lchild;
			}
			if (!node.empty()) {
				n = node.top();
				node.pop();
	            cout<<n->data<<"\t";
				n = n->rchild;
			}
		}
		cout<<endl;
	}
	void IsCompBiTree(){
		int flag=0,j=0;
		BTNQ *q=NULL,*head,*tail;
		head=(BTNQ*)malloc(sizeof(BTNQ));
		head->next=NULL;head->p=bt;
		tail=q=head;
		while(head!=NULL){
			if(head->p->lchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));q->next=NULL;q->p=head->p->lchild;
				tail->next=q;tail=tail->next;
				if(j==1){flag=1;break;}
			}
			if(head->p->rchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));q->next=NULL;q->p=head->p->rchild;
				tail->next=q;tail=tail->next;
				if(j==1){flag=1;break;}
			}
			if(!head->p->lchild||!head->p->rchild)j=1;
			head=head->next;
		}
		if(flag)cout<<"������ȫ������"<<endl;
		else cout<<"����ȫ������"<<endl;
	}
};

int main(){
	BiTree BT;
	int n=0;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.����������"<<endl;
		cout<<"----2.�ж��Ƿ�Ϊ��ȫ������"<<endl;
		cout<<"----3.�������"<<endl;
		cin>>n;
		switch(n){
			case 1:BT.CreateBiTree();break;
			case 2:BT.IsCompBiTree();break;
			case 3:BT.InOrderTraverse();break; 
		}
	}
}
