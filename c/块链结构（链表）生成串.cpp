#include<stdio.h>
#include<stdlib.h> 
#include<iostream>
using namespace std;
#define SIZE 5

typedef struct Chunk{
	char ch[SIZE];
	Chunk *next;
}Chunk;
typedef struct{
	Chunk *head,*tail;
	int curlen;
}Lstring;

int main(){
	Chunk *s=NULL;
	s=(Chunk*)malloc(sizeof(Chunk));
	s->next=NULL;
	Lstring s1;
	s1.curlen=0;
	s1.head=s;
	s1.tail=s;
	while(1){
		if(s1.tail->next==NULL){             //´ýÐø 
			
		}
	}
}
