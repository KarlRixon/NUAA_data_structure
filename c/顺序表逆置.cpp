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
	p=reverse(p);
	cout<<"���ú�����Ա�Ϊ��"<<endl;
	show(p);
}
