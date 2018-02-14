#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
	char s[7],c[21];int next[5];
	int i=1,j=0;
	next[0]=5;next[1]=0;s[0]=5;c[0]=19;
	cout<<"输入待匹配串：";
	for(int n=1;n<20;n++){
		cin>>c[n];
	} 
	cout<<"输入模式串：";
	for(int n=1;n<6;n++){
		cin>>s[n];
	}
//	cout<<endl;
	while(i<s[0]){
		if(j==0||s[i]==s[j]){++i;++j;next[i]=j;}
		else j=next[j];
	}
	//开始匹配
	cout<<"输入比较开始位置：";
	cin>>i;
	j=1;
	while(i<=c[0]&&j<=s[0]){
		if(j==0||c[i]==s[j]){++i;++j;}
		else j=next[j];
	}
	if(j>s[0]) cout<<"匹配位置为："<<i-s[0]<<endl;
	else cout<<"匹配失败"<<endl;
	//匹配结束 
	cout<<"模式串next数组：";
	for(int n=1;n<6;n++){
		cout<<next[n]<<" ";
	}cout<<endl;
	for(int n=1;n<=c[0];n++)cout<<c[n];cout<<endl;
	for(int n=1;n<i-s[0];n++)cout<<"#";
	for(int n=1;n<=s[0];n++)cout<<s[n];
	cout<<endl;
} 
