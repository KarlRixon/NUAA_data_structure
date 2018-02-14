#include <iostream>
using namespace std;

int hashmap[12];

void hashadd(int temp){
	if(hashmap[temp%11]==0)hashmap[temp%11]=temp;
	else{
		for(int i=1;;i++){
			cout<<(temp%11+i*i)%11<<"\t"<<(temp%11+i*i*(-1))%11<<endl;
			if(hashmap[(temp%11+i*i)%11]==0){hashmap[(temp%11+i*i)%11]=temp;break;}
			else if((temp%11+i*i*(-1))<0){
				int n=0;
				for(n=(temp%11+i*i*(-1));n<0;n+=12);
				if(hashmap[n]==0)hashmap[n]=temp;
			}
			else if(hashmap[temp%11+i*i*(-1)]==0){hashmap[temp%11+i*i*(-1)]=temp;break;}
		}
	}
}
void show(){
	for(int i=0;i<11;i++)cout<<hashmap[i]<<"\t";cout<<endl;
}
int main(){
	int temp=0;
	for(int i=0;i<11;i++){
		hashmap[i]=0;
//		cout<<hashmap[i]<<"\t";
	}
	for(int i=0;i<11;i++){
		cout<<"输入第"<<i+1<<"个正整数（输入0结束输入）：";
		cin>>temp;
		if(temp==0)break;
		hashadd(temp);
		show();
	}
}
