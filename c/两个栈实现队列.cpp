#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
using namespace std;
#define INITSIZE 10
#define INCREMENT 5

typedef struct SqStack{
	int *base;
	int *top;
	int stacksize;
}SqStack;

int main(){
	int t=0,i=0,r=0;
	SqStack stack,stack2;
	stack.stacksize=stack2.stacksize=INITSIZE;
	stack.base=(int*)malloc(sizeof(int)*INITSIZE);
	stack2.base=(int*)malloc(sizeof(int)*INITSIZE);
	stack.top=stack.base;
	stack2.top=stack2.base;
	while(1){
		cout<<"输入入队元素（输入0结束）：";
		cin>>t;
		if((stack.top-stack.base)==stack.stacksize){
			stack.base=(int*)realloc(stack.base,sizeof(int)*(stack.stacksize+INCREMENT));
			stack.stacksize+=INCREMENT;
			stack.top=stack.base+i;
		}
		if(t==0)break; 
//		if(t==0){
//			r=i;
//			for(i;i<stack.stacksize;i++){
//				*(stack.base+i)=0;
//			}
//			break;
//		}
		*stack.top=t;
		stack.top++;
		i++;
	}
	
	cout<<"开始出队"<<endl;
	i=0;
	while(1){
		t=*(stack.top-1);
		stack.top--;
		if((stack2.top-stack2.base)==stack2.stacksize){
			stack2.base=(int*)realloc(stack2.base,sizeof(int)*(stack2.stacksize+INCREMENT));
			stack2.stacksize+=INCREMENT;
			stack2.top=stack2.base+i;
		}
		*stack2.top=t;
		stack2.top++;
		i++;
		if(stack.base==stack.top)break;
	}
	while(1){
		cout<<*(stack.top-1)<<endl;
		stack.top--;
		if(stack.base==stack.top){
		cout<<endl<<"栈空"<<endl;
		}
	}
}
