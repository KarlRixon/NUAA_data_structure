#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<iostream>
using namespace std;
#define INITSIZE 10
#define INCREMENT 5

typedef struct SqStack{
	char *base;
	char *top;
	int stacksize;
}SqStack;

int main(){
	char t;
	int state=1;
	SqStack stack;
	stack.stacksize=INITSIZE;
	stack.base=(char*)malloc(sizeof(char)*INITSIZE);
	stack.top=stack.base;
	cout<<"����(,),[,],{,}����ƥ����ԣ�"<<endl;
	while(1){
		cin>>t;
		if(t=='#')break;
		if(t=='('||t=='['||t=='{'){
			*(stack.top)=t;
			stack.top++;
		}
		if(t==')'){
			if(*(stack.top-1)=='('){
				stack.top--;
			}else state=0;
		}
		if(t==']'){
			if(*(stack.top-1)=='['){
				stack.top--;
			}else state=0;
		}
		if(t=='}'){
			if(*(stack.top-1)=='{'){
				stack.top--;
			}else state=0;
		}
//		else cout<<"�������"<<endl;continue;
	}
	if(stack.base==stack.top&&state==1)cout<<"����ƥ����ȷ"<<endl;
	else cout<<"����ƥ�����"<<endl;
}
