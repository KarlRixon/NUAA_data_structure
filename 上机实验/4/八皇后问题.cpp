#include<stdlib.h>
#include<stdio.h>
#include<iostream> 
using namespace std;

int m[8][8] = {0};//表示棋盘，初始为0，表示未放置皇后
int num = 0;//解数目

void show(){
	num++;
	cout<<"anser "<<num<<":"<<endl;
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			cout<<m[i][j]<<"  ";
		}cout<<endl;
	}
	cout<<"-------------------------"<<endl;
}

int check(int row,int col){
	int i=0,j=0;
	if(row==0)return 1;
	//检查纵向是否有皇后 
	for(int i=0;i<row;i++)if(m[i][col]==1)return 0;
	//检查左上至右下是否有皇后
	for(i=row-1,j=col-1;i>=0&&j>=0;i--,j--)if(m[i][j]==1)return 0;
	//检查左下至右上是否有皇后
	for(i=row-1,j=col+1;i>=0&&j<=7;i--,j++)if(m[i][j]==1)return 0;
	return 1; 
}

void queen(int row){				//此函数求解当棋盘前row-1行已放置好皇后，在第row行放置皇后
	for(int col=0;col<8;col++){
		m[row][col]=1;				//放置皇后 
		if(check(row,col)){			//检查此位置是否可放皇后 
			if(row==7)show();		//输出一个可行解 
			else queen(row+1);		//检查下一行 
		}
		m[row][col]=0;				//置0开始下一列的循环 
	}
}

int main(){
	queen(0);
}
