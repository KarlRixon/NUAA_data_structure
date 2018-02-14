#include<stdio.h>
#include<iostream>
using namespace std;
#define MAXSTRLEN 255

typedef unsigned char SString[MAXSTRLEN+1];
int main(){
	char temp;
	SString s1,s2,T;
	cout<<"ÊäÈë×Ö·û´®s1(ÊäÈë#½ØÖ¹)£º";
	int i;
	for(i=1;i<=MAXSTRLEN;i++){
		cin>>temp;
		if(temp!='#'){
			s1[i]=temp;
		}else break;
	}
	s1[0]=i-1;
	cout<<"s1 = "<<s1+1<<"\ts1.len = "<<(int)s1[0]<<endl;
	cout<<"ÊäÈë×Ö·û´®s2(ÊäÈë#½ØÖ¹)£º";
	for(i=1;i<MAXSTRLEN;i++){
		cin>>temp;
		if(temp!='#'){
			s2[i]=temp;
		}else break;
	}
	s2[0]=i-1;
	cout<<"s2 = "<<s2+1<<"\ts2.len = "<<(int)s2[0]<<endl;
	//T[1..s1[0]]=s1[1..s1[0]];
	//´ýÐø 
}
