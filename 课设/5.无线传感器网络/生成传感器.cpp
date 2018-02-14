#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
#include<time.h>
using namespace std;

typedef struct sensor{
	int n;
	int x;
	int y;
}sensor;

int main(){
	srand((unsigned)time(NULL));
	sensor *s;
	s=(sensor*)malloc(sizeof(sensor));
	fstream outfile;
	outfile.open("sensors.dat",ios::out|ios::binary);
	if(!outfile){
		cout<<"file with error"<<endl;
		exit(0);
	}
	cout<<"输入产生传感器的数量：";
	int n=0;
	cin>>n;
	int srec[n][2];
	for(int i=0;i<n;i++){
		srec[i][0]=srec[i][1]=0;
	}
	outfile.write((char*)&n,sizeof(int));
	int flag=0; 
	for(int i=0;i<n;){						//防止随机产生的传感器重复 
		s->n=i+1;
		s->x=rand()%100+1;
		s->y=rand()%100+1;
		for(int j=0;j<i;j++){
			if(s->x==srec[j][0]&&s->y==srec[j][1]){
//				cout<<"!"<<endl;
				flag=1;
			}
		}
		if(flag==1){
			flag=0;
			continue;
		}
		i++;
		srec[i][0]=s->x;
		srec[i][1]=s->y;
//		cout<<s->x<<'\t'<<s->y<<endl;
		outfile.write((char*)s,sizeof(sensor));
	}
	outfile.close();
	fstream infile;
	infile.open("sensors.dat",ios::in|ios::binary);
	infile.read((char*)&n,sizeof(int));
	cout<<n<<endl;
	for(int i=0;i<n;i++){
		infile.read((char*)s,sizeof(sensor));
		cout<<s->n<<'\t'<<s->x<<'\t'<<s->y<<endl;
	}
	infile.close();
	return 0;
}
