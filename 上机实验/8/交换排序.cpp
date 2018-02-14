#include <iostream>
using namespace std;

int nums[12];

int main(){
	for(int i=0;i<11;i++){
		cout<<"输入第"<<i+1<<"个数：";
		cin>>nums[i]; 
	}
	for(int i=10;i>0;i--){
		for(int j=i;j>=0;j--){
			if(nums[i]>nums[j]){
				int t=nums[i];
				nums[i]=nums[j];
				nums[j]=t;
			}
		}
	}
	for(int i=0;i<11;i++)cout<<nums[i]<<"\t";cout<<endl; 
}
