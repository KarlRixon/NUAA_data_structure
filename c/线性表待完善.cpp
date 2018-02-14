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
		cout<<"功能："<<endl;
		cout<<"----0.初始化"<<endl;
		cout<<"----1.销毁"<<endl;
		cout<<"----2.置空"<<endl;
		cout<<"----3.判断是否为空"<<endl;
		cout<<"----4.元素个数"<<endl;
		cout<<"----5.按位序查询元素"<<endl; 
		cout<<"----6.按内容查询元素"<<endl;
		cout<<"----7.元素前驱"<<endl;
		cout<<"----8.元素后驱"<<endl;
		cout<<"----9.遍历（打印）元素"<<endl;
		cout<<"----10.改变元素"<<endl;
		cout<<"----11.插入元素"<<endl;
		cout<<"----12.删除元素"<<endl;
		cout<<"----13.清屏"<<endl;
		cin>>n;
		switch(n){
			case 0:Init(demo);break;
			case 1:Destroy(demo);break;
			case 2:Clear(demo);break;
			case 3:if(IsEmpty(demo))cout<<"这是空表"<<endl;else cout<<"非空"<<endl;break;
			case 4:cout<<Length(demo)<<endl;break;
//			case 5:int k=0,e=0;cout<<"输入位序：";cin>>k;GetElem(demo,k,e);cout<<"元素内容为："<<e<<endl;break;
//			case 6:int k=0,e=0;cout<<"输入元素内容：";cin>>e;if(LocateElem(demo,k,e))cout<<"元素下标为："<<k<<endl;break;
			case 7:;break;
		}
	}
}
