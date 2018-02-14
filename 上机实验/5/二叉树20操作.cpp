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
	void Search(BiTNode* &q){			//通过元素值搜索节点，顺便确定双亲
		if(q->data==num){
			p=q;parent=pre;
		}
		if(q->lchild&&parent==NULL){
			pre=q;						//pre指向节点双亲 
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
		cout<<"二叉树初始化成功"<<endl;
		return 0;
	}
	void DestroyBiTree(){
		DBT(bt);cout<<"二叉树销毁成功"<<endl;
	}
	void CreateBiTree(){
		CBT(bt);cout<<"二叉树创建成功"<<endl;
	}
	void ClearBiTree(){
		ClearBT(bt);cout<<"二叉树清空成功"<<endl;
	}
	int BiTreeEmpty(){
		if(bt==NULL){cout<<"二叉树不存在"<<endl;return 1;}
		if(bt!=NULL&&bt->lchild==NULL&&bt->rchild==NULL){cout<<"二叉树为空"<<endl;return 1;}
		else {cout<<"二叉树不空"<<endl;return 0;}
	}
	int BiTreeDepth(){
		if(BiTreeEmpty()){cout<<"二叉树为空或不存在"<<endl;return 0;}
		depth=maxdepth=0;		//清空之前记录 
		BTD(bt);
		return maxdepth;
	}
	BiTNode *Root(){
		if(BiTreeEmpty()){cout<<"二叉树为空或不存在"<<endl;return NULL;}
		return bt;
	}
	int Value(){
		if(BiTreeEmpty()){cout<<"二叉树为空或不存在"<<endl;return -1;}
		return bt->data;
	}
	int Assign(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入待修改的节点值：";
		cin>>num;
		Search(bt);
		cout<<"输入修改值：";
		cin>>num;
		if(p){
			p->data=num;
			cout<<"赋值成功"<<endl;
			return 0;
		}else{
			cout<<"未找到元素"<<endl;return 1;
		}
	}
	BiTNode *Parent(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		Search(bt);
		if(parent){
			return parent;
		}else{
			cout<<"未找到"<<endl;return NULL;
		}
	}
	BiTNode *LeftChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		Search(bt);
		if(p&&p->lchild){
			return p->lchild;
		}else{
			cout<<"未找到"<<endl;return NULL;
		}
	}
	BiTNode *RightChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		Search(bt);
		if(p&&p->rchild){
			return p->rchild;
		}else{
			cout<<"未找到"<<endl;return NULL;
		}
	}
	BiTNode *LeftSibling(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		Search(bt);
		if(parent&&parent->lchild&&parent->lchild!=p){
			return parent->lchild;
		}else{
			cout<<"未找到"<<endl;return NULL;
		}
	}
	BiTNode *RightSibling(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		Search(bt);
		if(parent&&parent->rchild&&parent->rchild!=p){
			return parent->rchild;
		}else{
			cout<<"未找到"<<endl;return NULL;
		}
	}
	int InsertChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		int ch=0;
		cout<<"插入到节点的1.左子树/2.右子树";
		cin>>ch;
		Search(bt);
		if(p){
			if(ch==0){
				c->rchild=p->lchild;
				p->lchild=c;
				cout<<"插入成功"<<endl;
				return 0;
			}
			if(ch==1){
				c->rchild=p->rchild;
				p->rchild=c;
				cout<<"插入成功"<<endl;
				return 0;
			}
		}else{
			cout<<"未找到"<<endl;return 1;
		}
	}
	int DeleteChild(){
		num=0;p=NULL;parent=NULL;pre=NULL;		//初始化搜索变量 
		cout<<"输入节点值：";
		cin>>num;
		int ch=0;
		cout<<"删除节点的1.左子树/2.右子树";
		cin>>ch;
		Search(bt);
		if(p){
			if(ch==0){
				p->lchild=NULL;
				cout<<"删除成功"<<endl;
				return 0;
			}
			if(ch==1){
				p->rchild=NULL;
				cout<<"删除成功"<<endl;
				return 0;
			}
		} else{
			cout<<"未找到"<<endl;return 1;
		}
	}
	int PreOrderTraverse(){
		POT(bt);
		cout<<"遍历完成"<<endl;
		return 0;
	}
	int InOrderTraverse(){
		IOT(bt);
		cout<<"遍历完成"<<endl;
		return 0;
	}
	int PostOrderTraverse(){
		PostOT(bt);
		cout<<"遍历完成"<<endl;
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
	c=(BiTNode*)malloc(sizeof(BiTNode));		//c为待插入的子树 
	c->data=0;c->lchild=c->rchild=NULL;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.初始化二叉树"<<endl;
		cout<<"----2.销毁二叉树"<<endl;		//
		cout<<"----3.创建二叉树"<<endl;
		cout<<"----4.清空二叉树"<<endl;
		cout<<"----5.判断二叉树是否为空"<<endl;
		cout<<"----6.二叉树深度"<<endl;
		cout<<"----7.求二叉树根"<<endl;
		cout<<"----8.获取节点值"<<endl;
		cout<<"----9.给节点赋值"<<endl;		//
		cout<<"----10.求节点双亲"<<endl;
		cout<<"----11.节点左孩子"<<endl;
		cout<<"----12.节点右孩子"<<endl;
		cout<<"----13.节点左兄弟"<<endl;
		cout<<"----14.节点右兄弟"<<endl;
		cout<<"----15.插入右子树为空的子树"<<endl;	//
		cout<<"----16.删除子树"<<endl;
		cout<<"----17.先序遍历"<<endl;
		cout<<"----18.中序遍历"<<endl;
		cout<<"----19.后序遍历"<<endl;
		cout<<"----20.层序遍历"<<endl;
		cin>>n;
		switch(n){
			case 1:BT.InitBiTree();break;
			case 2:BT.DestroyBiTree();break;
			case 3:BT.CreateBiTree();break;
			case 4:BT.ClearBiTree();break;
			case 5:BT.BiTreeEmpty();break;
			case 6:cout<<"二叉树深度为："<<BT.BiTreeDepth()<<endl;break;
			case 7:cout<<"二叉树树根值为："<<BT.Root()->data<<endl;break;
			case 8:cout<<"某节点值为："<<BT.Value()<<endl;break;
			case 9:BT.Assign();break;
			case 10:cout<<"双亲的值为："<<BT.Parent()->data<<endl;break;
			case 11:cout<<"节点左孩子值为："<<BT.LeftChild()->data<<endl;break;
			case 12:cout<<"节点右孩子值为："<<BT.RightChild()->data<<endl;break;
			case 13:cout<<"节点左兄弟值为："<<BT.LeftSibling()->data<<endl;break;
			case 14:cout<<"节点右兄弟值为："<<BT.RightSibling()->data<<endl;break;
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
