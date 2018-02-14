#include<iostream>
#define MAXSIZE 10
#define MU 3
#define NU 5
#define TU 5
using namespace std;
 
typedef struct{
	int i,j;	//非零元素下标 
	int e;
}Triple;
typedef struct{
	Triple data[MAXSIZE+1];		//非零元三元组表，data[0]未用 
	int mu,nu,tu;				//矩阵的行数，列数，非零元个数 
}TSMatrix;

void showtsm(TSMatrix tsm){		//显示矩阵 
	int flag=0;
	for(int i=1;i<=tsm.mu;i++){
		for(int j=1;j<=tsm.nu;j++){
			for(int k=1;k<=tsm.tu;k++){
				if(i==tsm.data[k].i&&j==tsm.data[k].j){cout<<"\t"<<tsm.data[k].e;flag=1;}
			}if(!flag)cout<<"\t"<<0;flag=0;
		}cout<<endl;
	}
}

void transpose(TSMatrix tsm,TSMatrix &tsm2){
	tsm2.mu=tsm.nu;tsm2.nu=tsm.mu;tsm2.tu=tsm.tu;
	tsm2.data[0].e=tsm2.data[0].i=tsm2.data[0].j=0;
	int q=1;
	for(int col=1;col<=tsm.nu;col++){
		for(int p=1;p<=tsm.tu;p++){
			if(tsm.data[p].j==col){
				tsm2.data[q].i=tsm.data[p].j;
				tsm2.data[q].j=tsm.data[p].i;
				tsm2.data[q].e=tsm.data[p].e;
				++q;
			}
		}
	}
}

int main(){
	TSMatrix tsm,tsm2;
	tsm.mu=MU;tsm.nu=NU;tsm.tu=TU;
	tsm.data[0].e=tsm.data[0].i=tsm.data[0].j=0;
	cout<<"依次输入三元组："<<endl;
	for(int i=1;i<=tsm.tu;i++){
		cin>>tsm.data[i].i>>tsm.data[i].j>>tsm.data[i].e;		//输入部分没有检错 
	}
//	for(int i=1;i<=tsm.tu;i++){cout<<tsm.data[i].i<<"\t"<<tsm.data[i].j<<"\t"<<tsm.data[i].e<<endl;}
	cout<<"矩阵视图："<<endl;
	showtsm(tsm);
	transpose(tsm,tsm2);
	cout<<"转置后的三元组："<<endl;
	for(int i=1;i<=tsm2.tu;i++){cout<<tsm2.data[i].i<<"\t"<<tsm2.data[i].j<<"\t"<<tsm2.data[i].e<<endl;}
	cout<<"转置后的矩阵："<<endl;
	showtsm(tsm2);
}
