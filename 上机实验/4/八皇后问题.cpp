#include<stdlib.h>
#include<stdio.h>
#include<iostream> 
using namespace std;

int m[8][8] = {0};//��ʾ���̣���ʼΪ0����ʾδ���ûʺ�
int num = 0;//����Ŀ

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
	//��������Ƿ��лʺ� 
	for(int i=0;i<row;i++)if(m[i][col]==1)return 0;
	//��������������Ƿ��лʺ�
	for(i=row-1,j=col-1;i>=0&&j>=0;i--,j--)if(m[i][j]==1)return 0;
	//��������������Ƿ��лʺ�
	for(i=row-1,j=col+1;i>=0&&j<=7;i--,j++)if(m[i][j]==1)return 0;
	return 1; 
}

void queen(int row){				//�˺�����⵱����ǰrow-1���ѷ��úûʺ��ڵ�row�з��ûʺ�
	for(int col=0;col<8;col++){
		m[row][col]=1;				//���ûʺ� 
		if(check(row,col)){			//����λ���Ƿ�ɷŻʺ� 
			if(row==7)show();		//���һ�����н� 
			else queen(row+1);		//�����һ�� 
		}
		m[row][col]=0;				//��0��ʼ��һ�е�ѭ�� 
	}
}

int main(){
	queen(0);
}
