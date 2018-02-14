#include<iostream>
#include<fstream>
#include<time.h> 
#include<stdlib.h>
using namespace std;

int main(){
	int num=0,nums[20000];
	char filename[]="data_1.dat";
	fstream outfile;
	for(int j=0;j<10;j++){
		filename[5]=j+48;
		outfile.open(filename,ios::out|ios::binary);
		if(!outfile){
			cout<<"file with error"<<endl;
			exit(0);
		}
		srand((unsigned)time(NULL));
		for(int i=0;i<20000;i++){
			num=rand();
			outfile.write((char*)&num,sizeof(int));
		}
		outfile.seekg(0,ios::beg);
//		while(!outfile.eof()){
//			outfile.read((char*)&num,sizeof(int));
//			cout<<num<<"\t"; 
//		}
//		for(int i=0;i<20000;i++){
//			outfile.read((char*)&nums[i],sizeof(int));
//			cout<<nums[i]<<"\t";
//		}
		outfile.close();
	}
}
