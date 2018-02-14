#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
using namespace std;
#define SIZE 100
typedef struct{
	char *ch;
	int length;
}HString;
int main(){
	HString s1;
	char temp;
	int len=0;int i=0;
	char *p=NULL;
	s1.ch=(char*)malloc(sizeof(char)*SIZE);
	p=s1.ch;
	cout<<"输入字符串s1(输入#截止)：";
	for(i=1;i<=SIZE;i++){
		cin>>temp;
		if(temp!='#'){
			*p=temp;p++;
//			len++;
		}else break;
	}
	char *c=NULL;
	c=s1.ch;
	for(i=0;*c;++i,++c);           //*c用于 判断是否在字符串里，否则计数停止 
	s1.length=i;
//	cout<<i;
}
