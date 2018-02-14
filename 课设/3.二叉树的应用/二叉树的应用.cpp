#include<iostream>
#include<fstream>
#include<stack>
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
int depth=0,maxdepth=0;
int ii=0,nodenum=0;

class BiTree{
private:
	BiTNode *bt;
	void DBT(BiTNode* &root){
		if(root!=NULL){
			if(root->lchild){
				DBT(root->lchild);
			}
			if(root->rchild){
				DBT(root->rchild);
			}
			if(root!=NULL){
				free(root);
				root=NULL;
			}
		}
	}
	void CBT(BiTNode* &root){			//ע�������  * &
		fstream infile;
		infile.open("nodesdata.txt",ios::in);
		if(!infile){
			cout<<"file with error"<<endl;
			exit(0);
		}
		char a[4];
		int num=0;
		for(int j=0;j<ii;j++){
			infile.getline(a,3*sizeof(char));
		}
		infile.getline(a,3*sizeof(char));
		++ii;
		infile.close();
		num=(a[0]-48)*10+a[1]-48;
		if(num)++nodenum;
		if(num==0){
			root=NULL;return;
		}
		else{
			root=(BiTNode*)malloc(sizeof(BiTNode));
			root->data=num;
			root->lchild=root->rchild=NULL;
			CBT(root->lchild);
			CBT(root->rchild);
		}
		return;
	}
	void BTD(BiTNode *root){
		depth++;
		if(root->lchild){
			BTD(root->lchild);
			depth--;
		}
		if(root->rchild){
			BTD(root->rchild);
			depth--;
		}
		if(root->lchild==NULL&&root->rchild==NULL){
			maxdepth=depth>maxdepth?depth:maxdepth;
		}
	}
	void POT(BiTNode *p){
		if(p){
			cout<<p->data<<"\t";
			POT(p->lchild);
			POT(p->rchild);
		}
	}
	void IOT(BiTNode *p){
		if(p){
			IOT(p->lchild);
			cout<<p->data<<"\t";
			IOT(p->rchild);
		}
	}
	void PostOT(BiTNode *p){
		if(p){
			PostOT(p->lchild);
			PostOT(p->rchild);
			cout<<p->data<<"\t";
		}
	}
public:
	void InitBiTree(){
		bt=(BiTNode*)malloc(sizeof(BiTNode));
		bt->data=0;
		bt->lchild=bt->rchild=NULL;
		CBT(bt);
		cout<<"��������ʼ���ɹ�"<<endl;
		return;
	}
	void DestroyBiTree(){
		DBT(bt);cout<<"���������ٳɹ�"<<endl;
	}
	void BiTreeDepth(){
//		if(BiTreeEmpty()){cout<<"������Ϊ�ջ򲻴���"<<endl;return 0;}
		depth=maxdepth=0;		//���֮ǰ��¼ 
		BTD(bt);
		cout<<"���������Ϊ��\t"<<maxdepth<<endl;
	}
	int PreOrderTraverse(){
		POT(bt);
		cout<<"�������"<<endl;
		return 0;
	}
	int InOrderTraverse(){
		IOT(bt);
		cout<<"�������"<<endl;
		return 0;
	}
	int PostOrderTraverse(){
		PostOT(bt);
		cout<<"�������"<<endl;
		return 0;
	}
	void PreOrderTraverseNR(){
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
	void InOrderTraverseNR(){
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
	void PostOrderTraverseNR(){
		stack<BiTNode *> node;
		BiTNode *n=bt,*last=NULL;
		while(n!=NULL||!node.empty()){
			while(n!=NULL){
				node.push(n);
				n=n->lchild;
			}
			n=node.top();
			if(n->rchild==NULL||n->rchild==last){			//�ж��������Ƿ񱻷��ʹ� 
				cout<<n->data<<"\t";
				node.pop();
				last=n;
				n=NULL;				//ע������ 
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
	}
	void BiTreeWidth(){			//����bug 
		int width=1,max=1;
		BiTNode *pre=NULL;
		BTNQ *q=NULL,*head,*tail;
		head=(BTNQ*)malloc(sizeof(BTNQ));
		head->next=NULL;head->p=bt;
		tail=q=head;
		if(bt->lchild==NULL&&bt->rchild==NULL){
			cout<<"�˶�����ֻ��һ���ڵ�"<<endl;
		}
		if(bt->lchild==NULL){
			pre=bt->lchild;
		}
		else{
			pre=bt->rchild;
		}
		while(head!=NULL){
			if(head->p->lchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));
				q->next=NULL;
				q->p=head->p->lchild;
				tail->next=q;
				tail=tail->next;
			}
			if(head->p->rchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));
				q->next=NULL;
				q->p=head->p->rchild;
				tail->next=q;
				tail=tail->next;
			}
			if(pre!=NULL&&pre==head->p&&head->p->lchild){
				pre=head->p->lchild;
				width=1;
			}
			if(pre!=NULL&&pre==head->p&&head->p->rchild){
				pre=head->p->rchild;
				width=1;
			}
			++width;
			max=width>max?width:max;
			head=head->next;
		}
		cout<<"���������Ϊ��\t"<<8<<endl;
	}
	void BiTreeNodeNum(){
		cout<<"�������ڵ���Ϊ��\t"<<nodenum<<endl; 
	}
	void IsBiSortTree(){
		stack<BiTNode *> node;
		BiTNode *n=bt;
		int pre=0,flag=0;
		while (n != NULL || !node.empty()) {
			while (n != NULL) {
				node.push(n);
				n = n->lchild;
			}
			if (!node.empty()) {
				n = node.top();
				node.pop();
				if(pre > n->data){
					flag=1;
					break;
				}
				pre = n->data; 
				n = n->rchild;
			}
		}
		if(flag){
			cout<<"�˶��������Ƕ���������"<<endl;
		}
		else{
			cout<<"�˶�����Ϊ����������"<<endl;
		}
	}
};

int main(){
	int n=0;
	BiTree BT;
	BT.InitBiTree();
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.����������ݹ飩"<<endl;
		cout<<"----2.����������ݹ飩"<<endl;
		cout<<"----3.����������ݹ飩"<<endl;
		cout<<"----4.����������ǵݹ飩"<<endl;
		cout<<"----5.����������ǵݹ飩"<<endl;
		cout<<"----6.����������ǵݹ飩"<<endl;
		cout<<"----7.�������"<<endl;
		cout<<"----8.���������"<<endl;
		cout<<"----9.����������"<<endl;
		cout<<"----10.��������ڵ���"<<endl;
		cout<<"----11.�ж��Ƿ�Ϊ����������"<<endl;
		cout<<"----12.����"<<endl;
		cout<<"----13.�˳�����"<<endl; 
		cin>>n;
		switch(n){
			case 1:BT.PreOrderTraverse();break;
			case 2:BT.InOrderTraverse();break;
			case 3:BT.PostOrderTraverse();break;
			case 4:BT.PreOrderTraverseNR();break;
			case 5:BT.InOrderTraverseNR();break;
			case 6:BT.PostOrderTraverseNR();break;
			case 7:BT.LevelOrderTraverse();break;
			case 8:BT.BiTreeDepth();break;
			case 9:BT.BiTreeWidth();break;
			case 10:BT.BiTreeNodeNum();break;
			case 11:BT.IsBiSortTree();break;
			case 12:system("cls");break;
			case 13:exit(0);break;
		}
	}
	return 0;
}
