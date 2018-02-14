#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std; 

int main(){
	int n=0,val=0,count=0;
	printf("输入矩阵阶数:\n");
	scanf("%d",&n);
	int a[n][n],b[n][n],c[n][n];
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<"输入矩阵a第"<<i+1<<"行第"<<j+1<<"列元素：";
			scanf("%d",&a[i][j]);
			count++;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			cout<<"输入矩阵b第"<<i+1<<"行第"<<j+1<<"列元素：";
			scanf("%d",&b[i][j]);
			count++;
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			c[i][j]=0;
			for(int k=0;k<n;k++){
				c[i][j]+=a[i][k]*b[k][j];
				count++;
			}
		}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			printf("%d\t",c[i][j]);
			count++;
		}
		printf("\n");
	}
	cout<<"----共进行了"<<count<<"次计算"<<endl; 
}
