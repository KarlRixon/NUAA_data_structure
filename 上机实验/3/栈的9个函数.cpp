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
			cout<<"�ڴ����ʧ��"<<endl;
			exit(0);
		}
		S.stacksize=STACK_INIT_SIZE;
		S.top=S.base;
		cout<<"\tջ��ʼ���ɹ�"<<endl; 
		return 1;
	}
	int DestroyStack(){
		S.top=NULL;
		free(S.base);
		S.stacksize=0;
		S.base=NULL;
		cout<<"\tջ���ٳɹ�"<<endl;
		return 1;
	}
	int ClearStack(){
		S.top=S.base;
		cout<<"\tջ��ճɹ�"<<endl;
		return 1;
	}
	int StackEmpty(){
		if(S.top==S.base){
			cout<<"ջΪ��"<<endl;
		}else cout<<"ջ����"<<endl;
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
			cout<<"ջ��,����ֵ";return 0;
		}
	}
	int Push(){
		if(StackLength()==S.stacksize){
			S.base=(int*)realloc(S.base,sizeof(int)*(S.stacksize+STACK_INCREMENT));
			S.stacksize+=STACK_INCREMENT;
		}
		cout<<"������ջԪ�أ�";
		cin>>*(S.top);
		S.top++;
		cout<<"��ջ�ɹ�"<<endl;
	}
	int Pop(){
		if(S.base!=S.top){
			S.top--;
			return *S.top;
		}
		else{
			cout<<"ջ��,����ֵ";return 0;
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
		cout<<"��ѡ���ܣ�"<<endl;
		cout<<"----1.��ʼ��ջ"<<endl;
		cout<<"----2.����ջ"<<endl;
		cout<<"----3.���ջ"<<endl;
		cout<<"----4.�ж��Ƿ�Ϊ��ջ"<<endl; 
		cout<<"----5.��ջ�ĳ���"<<endl;
		cout<<"----6.�鿴ջ��Ԫ��"<<endl;
		cout<<"----7.��ջ������Ԫ��"<<endl;
		cout<<"----8.����ջ��Ԫ��"<<endl;
		cout<<"----9.��ջ�׵�ջ������Ԫ��"<<endl;
		cout<<"----10.����"<<endl;
		cin>>n;
		switch(n){
			case 1:S.InitStack();break;
			case 2:S.DestroyStack();break;
			case 3:S.ClearStack();break;
			case 4:S.StackEmpty();break;
			case 5:cout<<S.StackLength()<<"��Ԫ��"<<endl;break;
			case 6:cout<<S.GetTop()<<endl;break; 
			case 7:S.Push();break;
			case 8:cout<<S.Pop()<<"Ԫ�ص���"<<endl;break;
			case 9:S.StackTraverse(visit);break;
			case 10:system("cls");break;
		}
	}
}
