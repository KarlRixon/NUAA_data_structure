#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#define STACK_INIT_SIZE 100
#define STACK_INCREMENT 10
using namespace std;

typedef struct{
	int *base;
	int *top;
	int stacksize;
}SqStack;
class Stack{
private:
	SqStack S;
public:
	int InitStack(){
		S.base=(int*)malloc(sizeof(int)*STACK_INIT_SIZE);
		if(!S.base){
			cout<<"内存分配失败"<<endl;
			exit(0);
		}
		S.stacksize=STACK_INIT_SIZE;
		S.top=S.base;
		cout<<"\t栈初始化成功"<<endl; 
		return 1;
	}
	int DestroyStack(){
		S.top=NULL;
		free(S.base);
		S.stacksize=0;
		S.base=NULL;
		cout<<"\t栈销毁成功"<<endl;
		return 1;
	}
	int ClearStack(){
		S.top=S.base;
		cout<<"\t栈清空成功"<<endl;
		return 1;
	}
	int StackEmpty(){
		if(S.top==S.base){
			cout<<"栈为空"<<endl;
		}else cout<<"栈不空"<<endl;
		return 1;
	}
	int StackLength(){
		int *p=S.base,i=0;
		while(p!=S.top){
			p++;i++;
		}
		return i; 
	}
	int GetTop(){
		if(S.base!=S.top)return *(S.top-1);
		else{
			cout<<"栈空,返回值";return 0;
		}
	}
	int Push(){
		if(StackLength()==S.stacksize){
			S.base=(int*)realloc(S.base,sizeof(int)*(S.stacksize+STACK_INCREMENT));
			S.stacksize+=STACK_INCREMENT;
		}
		cout<<"输入入栈元素：";
		cin>>*(S.top);
		S.top++;
		cout<<"入栈成功"<<endl;
	}
	int Pop(){
		if(S.base!=S.top){
			S.top--;
			return *S.top;
		}
		else{
			cout<<"栈空,返回值";return 0;
		}
	}
	int StackTraverse(int(*visit)(int)){
		int *p=S.base;
		for(;p<S.top;p++){
			visit(*p);
		}
		cout<<endl;
		return 1;
	}
};
int visit(int e){
	cout<<e*2<<"\t";
}
int main(){
	Stack S;int n=0;
	while(1){
		cout<<"请选择功能："<<endl;
		cout<<"----1.初始化栈"<<endl;
		cout<<"----2.销毁栈"<<endl;
		cout<<"----3.清空栈"<<endl;
		cout<<"----4.判断是否为空栈"<<endl; 
		cout<<"----5.求栈的长度"<<endl;
		cout<<"----6.查看栈顶元素"<<endl;
		cout<<"----7.从栈顶插入元素"<<endl;
		cout<<"----8.弹出栈顶元素"<<endl;
		cout<<"----9.从栈底到栈顶遍历元素"<<endl;
		cout<<"----10.清屏"<<endl;
		cin>>n;
		switch(n){
			case 1:S.InitStack();break;
			case 2:S.DestroyStack();break;
			case 3:S.ClearStack();break;
			case 4:S.StackEmpty();break;
			case 5:cout<<S.StackLength()<<"个元素"<<endl;break;
			case 6:cout<<S.GetTop()<<endl;break; 
			case 7:S.Push();break;
			case 8:cout<<S.Pop()<<"元素弹出"<<endl;break;
			case 9:S.StackTraverse(visit);break;
			case 10:system("cls");break;
		}
	}
}
