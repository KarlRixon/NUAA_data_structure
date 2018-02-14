#include<iostream>
#include<stdlib.h>
#include<queue>
using namespace std;

struct TNode;
typedef struct Sons{
	TNode *node;
	Sons *next;
}Sons;
typedef struct TNode{
	int data;
	Sons *sons;				//孩子链表 
	TNode *lsibling;
	TNode *rsibling;
}TNode;
TNode *root; 

void create(TNode* &root){
	queue<TNode*> tnodeq;
	Sons *s=NULL;TNode *q=NULL,*lsibling=NULL;int n=0;
	root=(TNode*)malloc(sizeof(TNode));
	cout<<"输入根节点数据：";
	cin>>root->data;
	root->lsibling=root->rsibling=NULL;root->sons=NULL;
	tnodeq.push(root);
	while(!tnodeq.empty()){
		q=tnodeq.front();tnodeq.pop();
		while(1){
			cout<<"输入 "<<q->data<<" 的孩子节点数据（输入0结束）：";
			cin>>n;
			if(n>0){
				if(q->sons==NULL){
					q->sons=(Sons*)malloc(sizeof(Sons));
					s=q->sons;q->lsibling=q->rsibling=NULL;
				}else{
					while(s->next){s=s->next;}
					s->next=(Sons*)malloc(sizeof(Sons));s=s->next;
				}
				s->next=NULL;s->node=(TNode*)malloc(sizeof(TNode));
				s->node->data=n;s->node->sons=NULL;
				s->node->lsibling=lsibling;s->node->rsibling=NULL;
				if(lsibling){lsibling->rsibling=s->node;}
				lsibling=s->node;
				tnodeq.push(s->node);
				
			}else if(n<0){cout<<"重新输入"<<endl;continue;}
			else{if(lsibling){lsibling->rsibling=NULL;s=q->sons;break;}}
		}
	}
}
void show(TNode *root){
	TNode *p;Sons *s=NULL;
	queue<TNode*> tnodeq;
	tnodeq.push(root);
	while(!tnodeq.empty()){
		p=tnodeq.front();tnodeq.pop();
		cout<<p->data<<"\t";
		s=p->sons;
		while(s&&s->next){
			tnodeq.push(s->node);s=s->next;
		}
	}
}
int main(){
	create(root);
	show(root);
}
