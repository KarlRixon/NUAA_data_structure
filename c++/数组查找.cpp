#include <iostream>
using namespace std;
int main(){
	int arr[11],n;
	for(int i=0;i<10;i++){
		arr[i]=i;
	}
	for(int i=0;i<10;i++){
		cout<<arr[i];
	}
	cout<<"����Ԫ���±꣺";
	cin>>n;
	for(int i=0;i<10;i++){
		if(i==n){
			cout<<arr[i];
		}
	}
}
