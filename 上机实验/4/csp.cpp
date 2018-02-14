#include<iostream>
#include<stdlib.h>
#include<stdio.h>
using namespace std;

void showtrain(int train[20][6]){
	for(int i=0;i<20;i++){
		for(int j=0;j<5;j++){
			cout<<"\t"<<train[i][j];
		}cout<<endl;
	}
}

int main(){
	cout<<"输入购票次数：";
	int n=0,m=0;while(1){cin>>n;if(n>0)break;else cout<<"重新输入"<<endl;}
	int train[20][6];
	for(int i=0;i<20;i++){		//座位初始化为0 
		for(int j=0;j<5;j++){
			train[i][j]=0;
		}
	}
//	showtrain(train);
	int row=0,col=0,flag=0;		//0说明跳到下一行查找，1说明购票成功 
	for(int i=0;i<n;i++){
		flag=0;
		cout<<"第"<<i+1<<"次购票个数：";
		while(1){cin>>m;if(m>0&&m<6)break;else cout<<"重新输入"<<endl;}
		for(int i=0;i<20;i++){		//逐行 
			for(int j=0;j<5;j++){		//逐列
				if(train[i][j])continue;	//不是空座，继续找 
				if(train[i][j]==0){		//找到空位就开始尝试 
//					row=i;col=j; 
					if(5>=(j+m)){			//可以连坐
						for(int k=j;k<(j+m);k++){		//填充座位 
							train[i][k]=1;
							cout<<i*5+k+1<<"\t";
						}flag=1;cout<<endl;
					}else flag=0;		//不可连坐 
				}
				break;			//若找到了空座，则必跳出此循环 
			}
			if(flag)break;		//跳出此次购票 
		}
	}
//	showtrain(train);
}
