#include<iostream>
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
int depth=0,maxdepth=0,num=0;
BiTNode *p=NULL,*parent=NULL,*pre=NULL,*c=NULL;

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
	void ClearBT(BiTNode* &root){
		root->data=0;
		if(root!=NULL){
			if(root->lchild){
				DBT(root->lchild);
				root->lchild=NULL;
			}
			if(root->rchild){
				DBT(root->rchild);
				root->rchild=NULL;
			}
		}
	}
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
	void Search(BiTNode* &q){			//ͨ��Ԫ��ֵ�����ڵ㣬˳��ȷ��˫��
		if(q->data==num){
			p=q;parent=pre;
		}
		if(q->lchild&&parent==NULL){
			pre=q;						//preָ��ڵ�˫�� 
			Search(q->lchild);
		}
		if(q->rchild&&parent==NULL){
			pre=q;
			Search(q->rchild);
		}
	}
	void POT(BiTNode *p){
		if(p){
			cout<<p->data<<"\t";
			POT(p->lchild);
			POT(p->rchild);
		};
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
			IOT(p->lchild);
			IOT(p->rchild);
			cout<<p->data<<"\t";
		};
	}
public:
	int InitBiTree(){
		bt=(BiTNode*)malloc(sizeof(BiTNode));
		bt->data=0;
		bt->lchild=bt->rchild=NULL;
		cout<<"��������ʼ���ɹ�"<<endl;
		return 0;
	}
	void DestroyBiTree(){
		DBT(bt);cout<<"���������ٳɹ�"<<endl;
	}
	void CreateBiTree(){
		CBT(bt);cout<<"�����������ɹ�"<<endl;
	}
	void ClearBiTree(){
		ClearBT(bt);cout<<"��������ճɹ�"<<endl;
	}
	int BiTreeEmpty(){
		if(bt==NULL){cout<<"������������"<<endl;return 1;}
		if(bt!=NULL&&bt->lchild==NULL&&bt->rchild==NULL){cout<<"������Ϊ��"<<endl;return 1;}
		else {cout<<"����������"<<endl;return 0;}
	}
	int BiTreeDepth(){
		if(BiTreeEmpty()){cout<<"������Ϊ�ջ򲻴���"<<endl;return 0;}
		depth=maxdepth=0;		//���֮ǰ��¼ 
		BTD(bt);
		return maxdepth;
	}
	BiTNode *Root(){
		if(BiTreeEmpty()){cout<<"������Ϊ�ջ򲻴���"<<endl;return NULL;}
		return bt;
	}
	int Value(){
		if(BiTreeEmpty()){cout<<"������Ϊ�ջ򲻴���"<<endl;return -1;}
		return bt->data;
	}
	int Assign(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"������޸ĵĽڵ�ֵ��";
		cin>>num;
		Search(bt);
		cout<<"�����޸�ֵ��";
		cin>>num;
		if(p){
			p->data=num;
			cout<<"��ֵ�ɹ�"<<endl;
			return 0;
		}else{
			cout<<"δ�ҵ�Ԫ��"<<endl;return 1;
		}
	}
	BiTNode *Parent(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		Search(bt);
		if(parent){
			return parent;
		}else{
			cout<<"δ�ҵ�"<<endl;return NULL;
		}
	}
	BiTNode *LeftChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		Search(bt);
		if(p&&p->lchild){
			return p->lchild;
		}else{
			cout<<"δ�ҵ�"<<endl;return NULL;
		}
	}
	BiTNode *RightChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		Search(bt);
		if(p&&p->rchild){
			return p->rchild;
		}else{
			cout<<"δ�ҵ�"<<endl;return NULL;
		}
	}
	BiTNode *LeftSibling(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		Search(bt);
		if(parent&&parent->lchild&&parent->lchild!=p){
			return parent->lchild;
		}else{
			cout<<"δ�ҵ�"<<endl;return NULL;
		}
	}
	BiTNode *RightSibling(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		Search(bt);
		if(parent&&parent->rchild&&parent->rchild!=p){
			return parent->rchild;
		}else{
			cout<<"δ�ҵ�"<<endl;return NULL;
		}
	}
	int InsertChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		int ch=0;
		cout<<"���뵽�ڵ��1.������/2.������";
		cin>>ch;
		Search(bt);
		if(p){
			if(ch==0){
				c->rchild=p->lchild;
				p->lchild=c;
				cout<<"����ɹ�"<<endl;
				return 0;
			}
			if(ch==1){
				c->rchild=p->rchild;
				p->rchild=c;
				cout<<"����ɹ�"<<endl;
				return 0;
			}
		}else{
			cout<<"δ�ҵ�"<<endl;return 1;
		}
	}
	int DeleteChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//��ʼ���������� 
		cout<<"����ڵ�ֵ��";
		cin>>num;
		int ch=0;
		cout<<"ɾ���ڵ��1.������/2.������";
		cin>>ch;
		Search(bt);
		if(p){
			if(ch==0){
				p->lchild=NULL;
				cout<<"ɾ���ɹ�"<<endl;
				return 0;
			}
			if(ch==1){
				p->rchild=NULL;
				cout<<"ɾ���ɹ�"<<endl;
				return 0;
			}
		} else{
			cout<<"δ�ҵ�"<<endl;return 1;
		}
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
};

int main(){
	int n=0;
	BiTree BT;
	c=(BiTNode*)malloc(sizeof(BiTNode));		//cΪ����������� 
	c->data=0;c->lchild=c->rchild=NULL;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.��ʼ��������"<<endl;
		cout<<"----2.���ٶ�����"<<endl;		//
		cout<<"----3.����������"<<endl;
		cout<<"----4.��ն�����"<<endl;
		cout<<"----5.�ж϶������Ƿ�Ϊ��"<<endl;
		cout<<"----6.���������"<<endl;
		cout<<"----7.���������"<<endl;
		cout<<"----8.��ȡ�ڵ�ֵ"<<endl;
		cout<<"----9.���ڵ㸳ֵ"<<endl;		//
		cout<<"----10.��ڵ�˫��"<<endl;
		cout<<"----11.�ڵ�����"<<endl;
		cout<<"----12.�ڵ��Һ���"<<endl;
		cout<<"----13.�ڵ����ֵ�"<<endl;
		cout<<"----14.�ڵ����ֵ�"<<endl;
		cout<<"----15.����������Ϊ�յ�����"<<endl;	//
		cout<<"----16.ɾ������"<<endl;
		cout<<"----17.�������"<<endl;
		cout<<"----18.�������"<<endl;
		cout<<"----19.�������"<<endl;
		cout<<"----20.�������"<<endl;
		cin>>n;
		switch(n){
			case 1:BT.InitBiTree();break;
			case 2:BT.DestroyBiTree();break;
			case 3:BT.CreateBiTree();break;
			case 4:BT.ClearBiTree();break;
			case 5:BT.BiTreeEmpty();break;
			case 6:cout<<"���������Ϊ��"<<BT.BiTreeDepth()<<endl;break;
			case 7:cout<<"����������ֵΪ��"<<BT.Root()->data<<endl;break;
			case 8:cout<<"ĳ�ڵ�ֵΪ��"<<BT.Value()<<endl;break;
			case 9:BT.Assign();break;
			case 10:cout<<"˫�׵�ֵΪ��"<<BT.Parent()->data<<endl;break;
			case 11:cout<<"�ڵ�����ֵΪ��"<<BT.LeftChild()->data<<endl;break;
			case 12:cout<<"�ڵ��Һ���ֵΪ��"<<BT.RightChild()->data<<endl;break;
			case 13:cout<<"�ڵ����ֵ�ֵΪ��"<<BT.LeftSibling()->data<<endl;break;
			case 14:cout<<"�ڵ����ֵ�ֵΪ��"<<BT.RightSibling()->data<<endl;break;
			case 15:BT.InsertChild();break;
			case 16:BT.DeleteChild();break;
			case 17:BT.PreOrderTraverse();break;
			case 18:BT.InOrderTraverse();break;
			case 19:BT.PostOrderTraverse();break;
			case 20:BT.LevelOrderTraverse();break;
		}
	}
	return 0;
}
