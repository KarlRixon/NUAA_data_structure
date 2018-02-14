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
	void CBT(BiTNode* &root){			//注意这里的  * & 
		cout<<"输入节点元素（输入0跳过该元素）：";
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
public:
	void CreateBiTree(){
		CBT(bt);cout<<"二叉树创建成功"<<endl;
	}
	void PreOrderTraverse(){
		stack<BiTNode *> node;
		BiTNode *n=bt;
		while(n!=NULL||!node.empty()){
			while(n!=NULL){
				cout<<n->data<<"\t";
				node.push(n);
				n=n->lchild;
			}
			if(!node.empty()){
				n=node.top();
				node.pop();
				n=n->rchild;
			}
		}
		cout<<endl;
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
	void PostOrderTraverse(){
		stack<BiTNode *> node;
		BiTNode *n=bt,*last=NULL;
		while(n!=NULL||!node.empty()){
			while(n!=NULL){
				node.push(n);
				n=n->lchild;
			}
			n=node.top();
			if(n->rchild==NULL||n->rchild==last){			//判断右子树是否被访问过 
				cout<<n->data<<"\t";
				node.pop();
				last=n;
				n=NULL;				//注意这里 
			}
			else n=n->rchild;
		}
		cout<<endl;
	}
	void LevelOrderTraverse(){
		BTNQ *q=NULL,*head,*tail;
		head=(BTNQ*)malloc(sizeof(BTNQ));
		head->next=NULL;head->p=bt;
		tail=q=head;
		while(head!=NULL){
			if(head->p->lchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));q->next=NULL;q->p=head->p->lchild;
				tail->next=q;tail=tail->next;
			}
			if(head->p->rchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));q->next=NULL;q->p=head->p->rchild;
				tail->next=q;tail=tail->next;
			}
			cout<<head->p->data<<"\t";
			head=head->next;
		}
		cout<<endl; 
	}
};

int main(){
	BiTree BT;
	int n=0;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.创建二叉树"<<endl;
		cout<<"----2.先序遍历"<<endl;
		cout<<"----3.中序遍历"<<endl;
		cout<<"----4.后序遍历"<<endl;
		cout<<"----5.层次遍历"<<endl;
		cin>>n;
		switch(n){
			case 1:BT.CreateBiTree();break;
			case 2:BT.PreOrderTraverse();break;
			case 3:BT.InOrderTraverse();break;
			case 4:BT.PostOrderTraverse();break;
			case 5:BT.LevelOrderTraverse();break;
		}
	}
}
