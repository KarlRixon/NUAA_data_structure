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
	cout<<"���빺Ʊ������";
	int n=0,m=0;while(1){cin>>n;if(n>0)break;else cout<<"��������"<<endl;}
	int train[20][6];
	for(int i=0;i<20;i++){		//��λ��ʼ��Ϊ0 
		for(int j=0;j<5;j++){
			train[i][j]=0;
		}
	}
//	showtrain(train);
	int row=0,col=0,flag=0;		//0˵��������һ�в��ң�1˵����Ʊ�ɹ� 
	for(int i=0;i<n;i++){
		flag=0;
		cout<<"��"<<i+1<<"�ι�Ʊ������";
		while(1){cin>>m;if(m>0&&m<6)break;else cout<<"��������"<<endl;}
		for(int i=0;i<20;i++){		//���� 
			for(int j=0;j<5;j++){		//����
				if(train[i][j])continue;	//���ǿ����������� 
				if(train[i][j]==0){		//�ҵ���λ�Ϳ�ʼ���� 
//					row=i;col=j; 
					if(5>=(j+m)){			//��������
						for(int k=j;k<(j+m);k++){		//�����λ 
							train[i][k]=1;
							cout<<i*5+k+1<<"\t";
						}flag=1;cout<<endl;
					}else flag=0;		//�������� 
				}
				break;			//���ҵ��˿��������������ѭ�� 
			}
			if(flag)break;		//�����˴ι�Ʊ 
		}
	}
//	showtrain(train);
}
