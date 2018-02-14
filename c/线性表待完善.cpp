#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define INIT_SIZE 10
#define INCREASEMENT 10
using namespace std;

typedef struct list{
	int *a;
	int length;
	int listsize;
}list;
void Init(list &demo){
	demo.a=(int *)malloc(INIT_SIZE*sizeof(int));
	if(!demo.a) exit(0);
	demo.length=0;
	demo.listsize=INIT_SIZE;
	return;
}
void Destroy(list &demo){
	demo.a=NULL;
	demo.length=0;
	demo.listsize=0;
	return;
}
void Clear(list &demo){
	for(int i=0;i<sizeof(demo.a)/sizeof(int);i++){
		demo.a[i]=0;
	}
	demo.length=0;
	return;
}
bool IsEmpty(list demo){
	if(demo.a==NULL) return true;
	for(int i=0;i<sizeof(demo.a)/sizeof(int);i++){
		if(demo.a[i]!=0) return false;
	}
	return true;
}
int Length(list demo){
	return demo.length;
}
void GetElem(list demo,int k,int &e){
	e=demo.a[k-1];
}
int LocateElem(list demo,int &k,int e){
	for(int i=0;i<sizeof(demo.a)/sizeof(int);i++){
		if(demo.a[i]==e){
			k=i;
			return 1;
		}
	}
	return 0;
}
void PriorElem(list demo,int cur_e,int &pre_e){
	for(int i=0;i<sizeof(demo.a)/sizeof(int);i++){
		if(demo.a[i]==cur_e) pre_e=demo.a[i-1];
	}
	return;
}
void NextElem(list demo,int cur_e,int &next_e){
	for(int i=0;i<sizeof(demo.a)/sizeof(int);i++){
		if(demo.a[i]==cur_e) next_e=demo.a[i-1];
	}
	return;
}
void Traverse(list demo){
	for(int i=0;i<sizeof(demo.a)/sizeof(int);i++){
		printf("%d ",demo.a[i]);
	}
	printf("\n");
}
void ChangeElem(list demo,int i,int chg){
	demo.a[i-1]=chg;
}
void Insert(list &demo,int k,int e){
	
}

int main(){
	list demo;
	Init(demo);
	int n=0;
	while(1){
		cout<<"���ܣ�"<<endl;
		cout<<"----0.��ʼ��"<<endl;
		cout<<"----1.����"<<endl;
		cout<<"----2.�ÿ�"<<endl;
		cout<<"----3.�ж��Ƿ�Ϊ��"<<endl;
		cout<<"----4.Ԫ�ظ���"<<endl;
		cout<<"----5.��λ���ѯԪ��"<<endl; 
		cout<<"----6.�����ݲ�ѯԪ��"<<endl;
		cout<<"----7.Ԫ��ǰ��"<<endl;
		cout<<"----8.Ԫ�غ���"<<endl;
		cout<<"----9.��������ӡ��Ԫ��"<<endl;
		cout<<"----10.�ı�Ԫ��"<<endl;
		cout<<"----11.����Ԫ��"<<endl;
		cout<<"----12.ɾ��Ԫ��"<<endl;
		cout<<"----13.����"<<endl;
		cin>>n;
		switch(n){
			case 0:Init(demo);break;
			case 1:Destroy(demo);break;
			case 2:Clear(demo);break;
			case 3:if(IsEmpty(demo))cout<<"���ǿձ�"<<endl;else cout<<"�ǿ�"<<endl;break;
			case 4:cout<<Length(demo)<<endl;break;
//			case 5:int k=0,e=0;cout<<"����λ��";cin>>k;GetElem(demo,k,e);cout<<"Ԫ������Ϊ��"<<e<<endl;break;
//			case 6:int k=0,e=0;cout<<"����Ԫ�����ݣ�";cin>>e;if(LocateElem(demo,k,e))cout<<"Ԫ���±�Ϊ��"<<k<<endl;break;
			case 7:;break;
		}
	}
}
