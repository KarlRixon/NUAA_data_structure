#include<iostream>
#include<stdlib.h>
using namespace std;

typedef struct HTNode{
	int weight;
	HTNode *parent,*lchild,*rchild;
}HTNode;
//typedef char **HuffmanCode;			//动态存储哈夫曼编码表
int n=0;

int empty(int weights[]){
	for(int i=0;i<n;i++){
		if(weights[i]!=0)return 0;
	}return 1;
}
int popsmall(int weights[]){
	if(empty(weights))return 101;
	int k=0,small=101;
	for(int i=0;i<n;i++){
		if(weights[i]!=0){
			small=small<weights[i]?small:weights[i];
			if(small==weights[i])k=i;
		}
	}
	weights[k]=0;return small;
}
int getsmall(int weights[]){
	if(empty(weights))return 101;
	int small=101;
	for(int i=0;i<n;i++)if(weights[i]!=0)small=small<weights[i]?small:weights[i];
	return small;
}
int emptyroots(HTNode *roots[]){
	for(int i=0;i<n;i++)if(roots[i]!=NULL)return 0;
	return 1;
}
int getsmallroots(HTNode *roots[]){
	HTNode *p=NULL;
	int small=101;
	for(int i=0;i<n;i++){
		p=roots[i];
		if(p!=NULL)small=small<p->weight?small:p->weight;
	}
	return small;
}
HTNode *popsmallroots(HTNode *roots[]){
	if(emptyroots(roots))return NULL;
	HTNode *p=NULL,*root=NULL;
	p=(HTNode*)malloc(sizeof(HTNode));p->weight=101;
	int k=0;
	for(int i=0;i<n;i++){
		if(roots[i]){
			p=p->weight<roots[i]->weight?p:roots[i];
			if(p=roots[i])k=i;
		}
	}
	roots[k]=NULL;return p;
}
void pushroot(HTNode *roots[],HTNode *root){
	for(int i=0;i<n;i++){
		if(roots[i]==NULL){roots[i]=root;return;}
	}
}
int oneroot(HTNode *roots[]){
	int nn=0;
	for(int i=0;i<n;i++){
		if(roots[i]!=NULL)nn++;
	}
	if(nn==1)return nn;
	else return 0;
}
void visit(HTNode *root){
	if(root->lchild)visit(root->lchild);
	cout<<root->weight<<"\t";
	if(root->rchild)visit(root->rchild);
}

int main(){
	cout<<"输入权值的数目：";
	cin>>n;
	int weights[n+1];
	cout<<"输入权值（1-100）："<<endl; 
	for(int i=0;i<n;i++){
		while(1){
			cin>>weights[i];
			if(weights[i]>0&&weights[i]<101)break;
			else cout<<"重新输入"<<endl;
		}
	}
//	for(int i=0;i<n;i++)cout<<weights[i]<<"\t";
	HTNode *pn=NULL,*l=NULL,*r=NULL,*root=NULL,*roots[n];
	for(int i=0;i<n;i++)roots[i]=NULL;
	int a=popsmall(weights),b=popsmall(weights);
	root=(HTNode*)malloc(sizeof(HTNode));root->parent=NULL;root->weight=(a+b);
	root->lchild=(HTNode*)malloc(sizeof(HTNode));root->rchild=(HTNode*)malloc(sizeof(HTNode));
	root->lchild->lchild=root->lchild->rchild=root->rchild->lchild=root->rchild->rchild=NULL;
	root->lchild->parent=root->rchild->parent=root;
	root->lchild->weight=a;root->rchild->weight=b;
	roots[0]=root;
	while(!empty(weights)||!emptyroots(roots)){
//		cout<<popsmall(weights)<<"\t";
		if(getsmall(weights)<getsmallroots(roots)){
			l=(HTNode*)malloc(sizeof(HTNode));
			l->weight=popsmall(weights);l->lchild=l->rchild=l->parent=NULL;
			if(getsmall(weights)<getsmallroots(roots)){
				r=(HTNode*)malloc(sizeof(HTNode));
				r->weight=popsmall(weights);r->lchild=r->rchild=r->parent=NULL;
			}else{
				r=popsmallroots(roots);
			}
		}else if(getsmall(weights)>getsmallroots(roots)){
			l=popsmallroots(roots);
			if(getsmall(weights)<getsmallroots(roots)){
				r=(HTNode*)malloc(sizeof(HTNode));
				r->weight=popsmall(weights);r->lchild=r->rchild=r->parent=NULL;
			}else{
				r=popsmallroots(roots);
			}
		}
		root=(HTNode*)malloc(sizeof(HTNode));root->parent=NULL;root->weight=(l->weight+r->weight);
		root->lchild=l;root->rchild=r;
		root->lchild->parent=root->rchild->parent=root;
		pushroot(roots,root);
		if(empty(weights)&&oneroot(roots))break;
	}
	cout<<"创建成功"<<endl;
	cout<<"中序遍历："<<endl; 
	visit(root);
}
