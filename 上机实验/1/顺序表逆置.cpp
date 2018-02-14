#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define INIT_SIZE 10
#define INCREMENT 10
using namespace std;

typedef struct list{
	int *a;
	int length;			//线性表大小 
	int listsize;		//存储元素数量 
}list;

void show(list *p){
	if(p==NULL)cout<<"线性表不存在"<<endl;
	else if(p->a==NULL)cout<<"线性表为空表"<<endl;
	else{ 
		for(int i=0;i<p->listsize;i++){
			cout<<"\t"<<*(p->a+i);
			if((i+11)%10==0)cout<<endl;
		}
	}
}
list *reverse(list *p){
	int t=0;int *n=p->a,*m=p->a+p->listsize-1;
//	cout<<*n<<*m;
	for(int i=0;i<p->listsize/2;i++){
		t=*n;*n=*m;*m=t;
		n++;m--;
	}
	return p;
}
int main(){
	list *p;
	p=NULL;
	p=(list *)malloc(sizeof(list));
	p->a=NULL;
	p->a=(int *)malloc(sizeof(int)*INIT_SIZE);
	p->length=INIT_SIZE;
	p->listsize=0;
	int num=0;
	cout<<"输入数字元素（"<<p->length<<"个以内，输入0结束）："<<endl;
	for(int i=0;i<p->length;i++){
		cout<<"输入第"<<i+1<<"个数字元素：";
		cin>>num;
		if(num!=0){
			*(p->a+i)=num;
			p->listsize+=1;
//			cout<<"listsize:"<<p->listsize;
		}
		else break;
	}
	cout<<"数字序列为："<<endl;
	show(p);
	cout<<endl;
	p=reverse(p);
	cout<<"逆置后的线性表为："<<endl;
	show(p);
}
