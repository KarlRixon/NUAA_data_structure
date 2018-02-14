#include<iostream>
using namespace std;
int main(){
	int a[11]={1,2,3,4,5,6,7,8,9,0};
	int *p=NULL;
	p=&a[0];
	for(int i=0;i<10;i++){
		cout<<*p;
		p++;
	}
}
