#include<iostream>
#include<queue>
#include<stack> 
#include<stdlib.h>
using namespace std;

typedef struct SqStack{
	char *base;
	char *top;
	int stacksize;
}SqStack;
typedef struct QNode{
	int data;
	QNode *next;
}QNode;
typedef struct LinkQueue{
	QNode *front;
	QNode *rear;
}LinkQueue;

int main(){
	int n=0;
	cin>>n;
//	stack<int> s;
//	for(;n!=0;){
//		s.push(n);
//		cin>>n;
//	}
//	while(!s.empty()){
//		n=s.top();
//		s.pop();
//		cout<<n<<"\t";
//	}cout<<endl;
	
	queue<int> q;
	for(;n!=0;){
		q.push(n);
		cin>>n;
	}
	while(!q.empty()){
		n=q.front();
		cout<<n<<"\t";
		q.pop();
	}cout<<endl;
}
