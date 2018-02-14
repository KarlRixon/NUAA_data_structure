#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define INIT_SIZE 10
#define INCREMENT 10
using namespace std;

typedef struct list{
	int *a;
	int length;			//���Ա��С 
	int listsize;		//�洢Ԫ������ 
}list;

void show(list *p){
	if(p==NULL)cout<<"���Ա�����"<<endl;
	else if(p->a==NULL)cout<<"���Ա�Ϊ�ձ�"<<endl;
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
	cout<<"��������Ԫ�أ�"<<p->length<<"�����ڣ�����0��������"<<endl;
	for(int i=0;i<p->length;i++){
		cout<<"�����"<<i+1<<"������Ԫ�أ�";
		cin>>num;
		if(num!=0){
			*(p->a+i)=num;
			p->listsize+=1;
//			cout<<"listsize:"<<p->listsize;
		}
		else break;
	}
	cout<<"��������Ϊ��"<<endl;
	show(p);
	cout<<endl;
	return p;
}
list *insertelem(list *p){
//	cout<<"listsize:"<<p->listsize<<endl;
//	cout<<"listlength:"<<p->length<<endl;
	if(p==NULL){
		cout<<"���Ա�����"<<endl;
		return p;
	}
	else if(p->a==NULL){
		cout<<"���Ա�Ϊ��"<<endl;
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
		cout<<"�������λ���±꣺";
		cin>>i;
		cout<<"������������Ԫ�أ�";
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
		cout<<"���Ա�����"<<endl;
		return p;
	}
	else if(p->a==NULL){
		cout<<"���Ա�Ϊ��"<<endl;
		return p;
	}
	int *q1=NULL;int i=0;
	while(1){
		cout<<"����ɾ��Ԫ�ص��±꣺";
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
	if(p==NULL)cout<<"���Ա����ڣ��޷�����"<<endl;
	else{
		p->a=NULL;
		p->length=0;
		p->listsize=0;
	}
}
void listempty(list *p){
	if(p==NULL)cout<<"���Ա�����"<<endl;
	else if(p->a==NULL)cout<<"���Ա�Ϊ��"<<endl;
	else cout<<"���Ա�Ϊ��"<<endl; 
}
void getlistsize(list *p){
	if(p==NULL)cout<<"���Ա�����"<<endl;
	else if(p->a==NULL)cout<<"���Ա�Ϊ��"<<endl;
	else if(p!=NULL)cout<<"���Ա�Ԫ�ظ���Ϊ"<<p->listsize<<endl;
}
void getelem(list *p){
	int n=0;int *q=NULL; 
	if(p==NULL)cout<<"���Ա�����"<<endl;
	else if(p->a==NULL)cout<<"���Ա�Ϊ��"<<endl;
	else{
		while(1){
			cout<<"�����ȡ�ڼ���Ԫ�ص�ֵ��";
			cin>>n;
			if(n<1||n>p->listsize)cout<<"�������"<<endl;
			else break;
		}
		q=p->a;
		for(int i=0;i<n-1;i++){
			q++;
		}
		cout<<"��"<<n<<"��Ԫ��ֵΪ"<<*q<<endl;
	}
}
void priorelem(list *p){
	int n=0;int *q=NULL; 
	if(p==NULL)cout<<"���Ա�����"<<endl;
	else if(p->a==NULL)cout<<"���Ա�Ϊ��"<<endl;
	else{
		while(1){
			cout<<"�����ȡ�ڼ���Ԫ�ص�ǰ��ֵ��";
			cin>>n;
			if(n<2||n>p->listsize)cout<<"�������"<<endl;
			else break;
		}
		q=p->a;
		for(int i=0;i<n-2;i++){
			q++;
		}
		cout<<"��"<<n<<"��Ԫ�ص�ǰ��ֵΪ"<<*q<<endl;
	}
}
void nextelem(list *p){
	int n=0;int *q=NULL; 
	if(p==NULL)cout<<"���Ա�����"<<endl;
	else if(p->a==NULL)cout<<"���Ա�Ϊ��"<<endl;
	else{
		while(1){
			cout<<"�����ȡ�ڼ���Ԫ�صĺ��ֵ��";
			cin>>n;
			if(n<1||n>p->listsize-1)cout<<"�������"<<endl;
			else break;
		}
		q=p->a;
		for(int i=0;i<n;i++){
			q++;
		}
		cout<<"��"<<n<<"��Ԫ�صĺ��ֵΪ"<<*q<<endl;
	}
}

int main(){
	int n=0;
	list *p;
	p=NULL;
	while(1){
		cout<<"����"<<endl;
		cout<<"----1.�������Ա�"<<endl;
		cout<<"----2.����Ԫ��"<<endl;
		cout<<"----3.ɾ��Ԫ��"<<endl;
		cout<<"----4.�鿴����Ԫ��"<<endl;
		cout<<"----5.����"<<endl;
		cout<<"----6.�������Ա�"<<endl;
		cout<<"----7.�����Ա�����Ϊ�ձ�"<<endl;
		cout<<"----8.�ж����Ա��Ƿ�Ϊ��"<<endl;
		cout<<"----9.��ȡ���Ա���Ԫ�ظ���"<<endl;
		cout<<"----10.��ȡ���Ա�Ԫ��ֵ"<<endl;
		cout<<"----11.��ȡԪ��ǰ��"<<endl;
		cout<<"----12.��ȡԪ�غ��"<<endl; 
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
