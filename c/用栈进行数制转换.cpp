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
	int r=0,num=0,N=1;
	SqStack stack;
	stack.stacksize=INITSIZE;
	stack.base=(int*)malloc(sizeof(int)*INITSIZE);
	stack.top=stack.base;
	cout<<"�����ת����ʮ��������";
	cin>>num;
	while(num){
		N=num%8;
		*stack.top=N;
		stack.top++;
		num/=8;
	}
	
	cout<<"ת�������Ϊ��";
	while(1){		
		cout<<*(stack.top-1);
		stack.top--;
		if(stack.base==stack.top)break;
	}
}
