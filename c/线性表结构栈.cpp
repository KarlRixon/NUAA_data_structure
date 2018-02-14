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
	SqStack stack;
	stack.stacksize=INITSIZE;
	stack.base=(int*)malloc(sizeof(int)*INITSIZE);
	stack.top=stack.base;
	while(1){
		cout<<"输入入栈元素（输入0结束）：";
		cin>>t;
		if((stack.top-stack.base)==stack.stacksize){
			stack.base=(int*)realloc(stack.base,sizeof(int)*(stack.stacksize+INCREMENT));
			stack.stacksize+=INCREMENT;
			stack.top=stack.base+i;
		}
		if(t==0){
			r=i;
			for(i;i<stack.stacksize;i++){
				*(stack.base+i)=0;
			}
			break;
		}
		*stack.top=t;
		stack.top++;
		i++;
	}
	
	cout<<"开始出栈"<<endl;
	for(;r>0;r--){
		if(getch()&&*(stack.base+r-1)!=0){
			cout<<*(stack.top-1)<<endl;
			stack.top--;
		}
	}
	if(stack.base==stack.top){
		cout<<endl<<"栈空"<<endl;
	}
}
