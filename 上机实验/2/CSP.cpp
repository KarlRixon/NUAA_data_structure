#include<iostream>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

int main(){
	int n=0,min=0,max=0,sc=0,lc=0;
	bool flag=false;
	cin>>n;
	int a[n+1];
	for(int i=0;i<n;i++){
		cin>>a[i];
		if(i==0)min=max=a[i];
		min=min<a[i]?min:a[i];
		max=max>a[i]?max:a[i];
	}
//	for(int i=0;i<n;i++)cout<<a[i]<<"\t";cout<<endl;
//	cout<<min<<endl<<max;
	for(int num=min;num<=max;num++){
		sc=0;lc=0;
		for(int i=0;i<n;i++){
			if(a[i]<num)lc++;
			else if(a[i]>num)sc++; 
		}
		if(lc==sc){cout<<num<<"\t";flag=true;}
	}
	if(!flag)cout<<-1;
	cout<<endl;
}
