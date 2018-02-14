#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

class num{
	int n;
public:
	void in(int num){
		n=num;
	}
	void out(){
		cout<<n;
	}
	int val(){
		return n;
	}
};
int main(){
 	int nu;
 	num a;
 	cout<<"¸³Öµ£º";
 	cin>>nu;
 	a.in(nu);
 	a.out();
 }
