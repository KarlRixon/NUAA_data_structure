#include<iostream>
#include<fstream>
#include<stdlib.h>
using namespace std;

int map[20][20];		// 1.墙 0.空地 2.经过 3.死胡同 
int record[40];			// 1.上 2.右 3.下 4.左
int flag=0;
int start=0,end=0;

void addrec(int dir){
	
}
void path(int pos[2]){
	int dir=0;
	if(pos[0]==end&&pos[1]==19){
		flag=1;
		return;
	}
	if(map[pos[0]-1][pos[1]]==0){
		dir=1;
		map[pos[0]][pos[1]]=2;
		--pos[0];
		addrec(dir);
		path(pos);
	}
	if(map[pos[0]][pos[1]+1]==0){
		dir=2;
		map[pos[0]][pos[1]]=2;
		++pos[1];
		addrec(dir);
		path(pos);
	}
	if(map[pos[0]+1][pos[1]]==0){
		dir=3;
		map[pos[0]][pos[1]]=2;
		++pos[0];
		addrec(dir);
		path(pos);
	}
	if(map[pos[0]][pos[1]-1]==0){
		dir=4;
		map[pos[0]][pos[1]]=2;
		--pos[1];
		addrec(dir);
		path(pos);
	}
	if(flag)return;
	else{
		if(map[pos[0]][pos[1]-1]==2){
			map[pos[0]][pos[1]]=3;
			--pos[1];
		}
		else if(map[pos[0]+1][pos[1]]==2){
			map[pos[0]][pos[1]]=3;
			++pos[0];
		}
		else if(map[pos[0]][pos[1]+1]==2){
			map[pos[0]][pos[1]]=3;
			++pos[1];
		}
		else if(map[pos[0]-1][pos[1]]==2){
			map[pos[0]][pos[1]]=3;
			--pos[0];
		}
		return;
	}
}
int main(){
	char mapch[20];
	int j=0;
	fstream infile;
	infile.open("map.txt",ios::in);
	if(!infile){
		cout<<"file with error"<<endl;
		exit(0);
	}
	while(!infile.eof()){
		infile.getline(mapch,21*sizeof(char));
		for(int i=0;i<20;i++){
			cout<<mapch[i]<<' ';
			if(mapch[i]=='#'){
				map[j][i]=1;
			}
			else{
				map[j][i]=0;
			}
		}
		cout<<endl;
		++j;
	}
	cout<<"迷宫载入完成"<<endl;
//	for(int m=0;m<20;m++){
//		for(int n=0;n<20;n++){
//			cout<<map[m][n];
//		}
//		cout<<endl;
//	}
	for(int m=0;m<20;m++){
		if(map[m][0]==0){
			start=m;
		}
		if(map[m][19]==0){
			end=m;
		}
	}
//	cout<<start<<"\t"<<end<<endl;
	int pos[2];
	pos[0]=start;
	pos[1]=1;
	path(pos);
	for(int m=0;m<20;m++){
		for(int n=0;n<20;n++){
			if(map[m][n]==1)cout<<'*';
			else if(map[m][n]==0)cout<<' ';
			else if(map[m][n]==2)cout<<'@';
			else if(map[m][n]==3)cout<<' ';
			cout<<' ';
		}
		cout<<endl;
	}
//	cout<<flag<<endl;
	infile.close();
}
