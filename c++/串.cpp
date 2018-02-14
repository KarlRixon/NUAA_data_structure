#include<iostream>
#include<string.h>
#include<stdlib.h>
using namespace std;

int main(){
	char *s=NULL;
	s=(char*)malloc(sizeof(char)*20);
	s[19]='\0';
	s[17]=s[18]='1';
	char t[10];
	strcpy(t,&s[17]);
	cout<<t<<endl;
	s[0]='1';s[1]='\0';
	cout<<s<<endl;
	s=(char*)realloc(s,sizeof(char)*10);
	cout<<s;
}
