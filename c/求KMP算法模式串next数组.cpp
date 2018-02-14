#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;

int main(){
	char s[11];int next[11];
	int i=1,j=0;
	next[0]=9;next[1]=0;s[0]=9;
	cout<<"ÊäÈëÄ£Ê½´®£º";
	for(int n=1;n<10;n++){
		cin>>s[n];
	}
	while(i<s[0]){
		if(j==0||s[i]==s[j]){++i;++j;next[i]=j;}
		else j=next[j];
	}
	for(int n=0;n<10;n++){
	cout<<next[n]<<" ";
	}
} 
