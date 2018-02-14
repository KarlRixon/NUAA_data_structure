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
		for(int i=0;i<p->length;i++){
			cout<<"\t"<<*(p->a+i);
			if((i+11)%10==0)cout<<endl;
		}
	}
}
list *init(list *p){
	list *q;
	q=(list *)malloc(sizeof(list));
	q->a=(int *)malloc(INIT_SIZE*sizeof(int));
	q->length=INIT_SIZE;
	q->listsize=0;
	for(int i=0;i<INIT_SIZE;i++){
		*(q->a+i)=0;
	}
	p=q;
	return p;
}
list *createlist(list *p){
	p=init(p);
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
	return p;
}
list *insertelem(list *p){
//	cout<<"listsize:"<<p->listsize<<endl;
//	cout<<"listlength:"<<p->length<<endl;
	if(p==NULL){
		cout<<"线性表不存在"<<endl;
		return p;
	}
	else if(p->a==NULL){
		cout<<"线性表为空"<<endl;
		return p;
	}
	if(p->listsize==p->length){
		p->a=(int *)realloc(p->a,(p->length+INCREMENT)*sizeof(int));
		p->length+=INCREMENT;
		for(int i=0;i<INCREMENT;i++){
			*(p->a+i+p->length-INCREMENT)=0;
		}
	}
	int *q1=NULL;int i=0,n=0;
	while(1){
		cout<<"输入插入位置下标：";
		cin>>i;
		cout<<"输入插入的数字元素：";
		cin>>n; 
		if(i>=0&&i<=p->listsize+1&&n!=0){ 
			q1=(p->a+i); 
			for(int *q=p->a+p->length-1;q>=q1;q--) *q=*(q-1);
			*(p->a+i-1)=n;
			p->listsize+=1;
			return p;
		}
	}
}
list *deleteelem(list *p){
	if(p==NULL){
		cout<<"线性表不存在"<<endl;
		return p;
	}
	else if(p->a==NULL){
		cout<<"线性表为空"<<endl;
		return p;
	}
	int *q1=NULL;int i=0;
	while(1){
		cout<<"输入删除元素的下标：";
		cin>>i;
		if(i>=0&&i<=p->listsize){
			q1=p->a+p->listsize-1;
			for(int *q=p->a+i-1;q<=q1;q++) *q=*(q+1);
			*q1=0;
			p->listsize-=1;
			if(p->length-p->listsize==INCREMENT){
				p->a=(int *)realloc(p->a,(p->length-INCREMENT)*sizeof(int));
				p->length-=INCREMENT;
			}
			return p;
		}
	}
}
list *destroylist(list *p){
	p=NULL;
	return p;
}
list *clearlist(list *p){
	if(p==NULL)cout<<"线性表不存在，无法重置"<<endl;
	else{
		p->a=NULL;
		p->length=0;
		p->listsize=0;
	}
}
void listempty(list *p){
	if(p==NULL)cout<<"线性表不存在"<<endl;
	else if(p->a==NULL)cout<<"线性表为空"<<endl;
	else cout<<"线性表不为空"<<endl; 
}
void getlistsize(list *p){
	if(p==NULL)cout<<"线性表不存在"<<endl;
	else if(p->a==NULL)cout<<"线性表为空"<<endl;
	else if(p!=NULL)cout<<"线性表元素个数为"<<p->listsize<<endl;
}
void getelem(list *p){
	int n=0;int *q=NULL; 
	if(p==NULL)cout<<"线性表不存在"<<endl;
	else if(p->a==NULL)cout<<"线性表为空"<<endl;
	else{
		while(1){
			cout<<"你想获取第几个元素的值：";
			cin>>n;
			if(n<1||n>p->listsize)cout<<"输入错误"<<endl;
			else break;
		}
		q=p->a;
		for(int i=0;i<n-1;i++){
			q++;
		}
		cout<<"第"<<n<<"个元素值为"<<*q<<endl;
	}
}
void priorelem(list *p){
	int n=0;int *q=NULL; 
	if(p==NULL)cout<<"线性表不存在"<<endl;
	else if(p->a==NULL)cout<<"线性表为空"<<endl;
	else{
		while(1){
			cout<<"你想获取第几个元素的前驱值：";
			cin>>n;
			if(n<2||n>p->listsize)cout<<"输入错误"<<endl;
			else break;
		}
		q=p->a;
		for(int i=0;i<n-2;i++){
			q++;
		}
		cout<<"第"<<n<<"个元素的前驱值为"<<*q<<endl;
	}
}
void nextelem(list *p){
	int n=0;int *q=NULL; 
	if(p==NULL)cout<<"线性表不存在"<<endl;
	else if(p->a==NULL)cout<<"线性表为空"<<endl;
	else{
		while(1){
			cout<<"你想获取第几个元素的后继值：";
			cin>>n;
			if(n<1||n>p->listsize-1)cout<<"输入错误"<<endl;
			else break;
		}
		q=p->a;
		for(int i=0;i<n;i++){
			q++;
		}
		cout<<"第"<<n<<"个元素的后继值为"<<*q<<endl;
	}
}

int main(){
	int n=0;
	list *p;
	p=NULL;
	while(1){
		cout<<"功能"<<endl;
		cout<<"----1.创建线性表"<<endl;
		cout<<"----2.插入元素"<<endl;
		cout<<"----3.删除元素"<<endl;
		cout<<"----4.查看所有元素"<<endl;
		cout<<"----5.清屏"<<endl;
		cout<<"----6.销毁线性表"<<endl;
		cout<<"----7.将线性表重置为空表"<<endl;
		cout<<"----8.判断线性表是否为空"<<endl;
		cout<<"----9.获取线性表中元素个数"<<endl;
		cout<<"----10.获取线性表元素值"<<endl;
		cout<<"----11.获取元素前驱"<<endl;
		cout<<"----12.获取元素后继"<<endl; 
		cin>>n;
		switch(n){
			case 1:p=createlist(p);break;
			case 2:p=insertelem(p);break;
			case 3:p=deleteelem(p);break;
			case 4:show(p);break;
			case 5:system("cls");
			case 6:p=destroylist(p);break;
			case 7:p=clearlist(p);break;
			case 8:listempty(p);break;
			case 9:getlistsize(p);break;
			case 10:getelem(p);break;
			case 11:priorelem(p);break;
			case 12:nextelem(p);break;
		}
	}
}
