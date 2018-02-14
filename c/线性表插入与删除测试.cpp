#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define INIT_SIZE 10
#define INCREMENT 10
using namespace std;

typedef struct list{
	int *a;
	int length;
	int listsize;
}list;

void show(list *p){
	for(int i=0;i<p->length;i++){
		cout<<*(p->a+i)<<"\t";
		if((i+11)%10==0)cout<<endl;
	}
}
list *init(list *p){
	list *q;
	q=(list *)malloc(sizeof(list));
	q->a=(int *)malloc(INIT_SIZE*sizeof(int));
	q->length=INIT_SIZE;
	q->listsize=0;
	for(int i=0;i<INIT_SIZE;i++){
		*(q->a+i)=i;
	}
	p=q;
	return p;
}
list *enlarge(list *p){
	p->a=(int *)realloc(p->a,(p->length+INCREMENT)*sizeof(int));
	p->length+=INCREMENT;
	int *q1=NULL;int i=0,n=0;
	while(1){
		cout<<"输入插入位置下标：";
		cin>>i;
		cout<<"输入插入的数字元素：";
		cin>>n; 
		if(i>=0&&i<=p->length&&n!=0){ 
			q1=(p->a+i); 
			for(int *q=p->a+p->length-1;q>=q1;q--) *q=*(q-1);
			*(p->a+i)=n;
			return p;
		}
	}
}
int main(){
	list *p=NULL;
	p=init(p);
	p=enlarge(p);
	show(p);
}
