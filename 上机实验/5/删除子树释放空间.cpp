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
	void DeleteChildTree(){
		int data=0,flag=0;
		cout<<"�����������ڵ�ֵ��";
		cin>>data;
		stack<BiTNode *> node;
		BiTNode *n=bt,*t=NULL;
		while (n != NULL || !node.empty()) {
			while (n != NULL) {
				node.push(n);
				n = n->lchild;
			}
			if (!node.empty()) {
				n = node.top();
				node.pop();
				if(n->lchild&&n->lchild->data==data){Destroy(n->lchild);n->lchild=NULL;flag=1;}
				if(n->rchild&&n->rchild->data==data){Destroy(n->rchild);n->rchild=NULL;flag=1;}
				else n = n->rchild;
			}
		}
		if(flag)cout<<"ɾ���ɹ�"<<endl;
	} 
};

int main(){
	BiTree BT;
	int n=0;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.����������"<<endl;
		cout<<"----2.ɾ������"<<endl;
		cout<<"----3.�������"<<endl;
		cin>>n;
		switch(n){
			case 1:BT.CreateBiTree();break;
			case 2:BT.DeleteChildTree();break;
			case 3:BT.InOrderTraverse();break; 
		}
	}
}
