#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include<windows.h>
using namespace std;

typedef struct{
	int *base;
	int front;
	int rear;
}SqQueue;

int main(){
	srand((unsigned)time(NULL));
	int t=rand();
	SqQueue q;
	q.front=q.rear=1;
	q.base=(int*)malloc(sizeof(int)*101);
	for(;q.front!=(q.rear+1)%101;q.rear=q.rear+1){		//初始化队列 
		*(q.base+q.rear-1)=rand()%1000;
	}
//	cout<<q.front<<endl<<q.rear;
	
//	for(int i=1;i<101;i++)cout<<*(q.base+i-1)<<"\t";cout<<endl;
	
	while(1){
		cout<<"保留的最后十个数为："<<endl;
		for(int i=q.rear-11;i<q.rear-1;i++)cout<<*(q.base+i)<<"\t";cout<<endl;
		for(int i=1;i<101;i++)cout<<*(q.base+i-1)<<"\t";cout<<endl;
		int max=q.front;
		for(int i=0;i<100;i++)max=max>*(q.base+i)?max:*(q.base+i);
		cout<<"最大值max= "<<max<<endl;
		q.front=(q.rear+91)%101;
		for(int i=0;i<91;i++,q.rear++){		///注意这里是91 
			if(q.rear==102)q.rear=1;
			*(q.base+q.rear-1)=rand()%1000;
		}
		Sleep(1000);
	}
}
