#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
	char s[7],c[21];int next[5];
	int i=1,j=0;
	next[0]=5;next[1]=0;s[0]=5;c[0]=19;
	cout<<"�����ƥ�䴮��";
	for(int n=1;n<20;n++){
		cin>>c[n];
	} 
	cout<<"����ģʽ����";
	for(int n=1;n<6;n++){
		cin>>s[n];
	}
//	cout<<endl;
	while(i<s[0]){
		if(j==0||s[i]==s[j]){++i;++j;next[i]=j;}
		else j=next[j];
	}
	//��ʼƥ��
	cout<<"����ȽϿ�ʼλ�ã�";
	cin>>i;
	j=1;
	while(i<=c[0]&&j<=s[0]){
		if(j==0||c[i]==s[j]){++i;++j;}
		else j=next[j];
	}
	if(j>s[0]) cout<<"ƥ��λ��Ϊ��"<<i-s[0]<<endl;
	else cout<<"ƥ��ʧ��"<<endl;
	//ƥ����� 
	cout<<"ģʽ��next���飺";
	for(int n=1;n<6;n++){
		cout<<next[n]<<" ";
	}cout<<endl;
	for(int n=1;n<=c[0];n++)cout<<c[n];cout<<endl;
	for(int n=1;n<i-s[0];n++)cout<<"#";
	for(int n=1;n<=s[0];n++)cout<<s[n];
	cout<<endl;
} 
