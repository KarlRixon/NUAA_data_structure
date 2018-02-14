#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct HTNode{
	int weight;
	int parent,lchild,rchild;
}HTNode;
typedef char** HuffmanCode;			//动态存储哈夫曼编码表

void HuffmanCoding(HTNode* &HT,HuffmanCode &HC,int *letters,int n){
	if(n<=1)return;
	int m=2*n-1;
	HT=(HTNode*)malloc(sizeof(HTNode)*(m+1));			//0号单元未用 
	int i=1;
	HTNode *p;
	for(p=HT;i<=n;++i,++p,++letters){
		p->weight=*letters;
		p->lchild=p->parent=p->rchild=0;
//		*p={*letters,0,0,0};
//		cout<<p->weight;
	}
	for(;i<=m;++i,++p){
		p->lchild=p->parent=p->rchild=p->weight=0;
//		*p={0,0,0,0};
	}
//	for(int l=0;l<m;l++){
//		cout<<l<<":"<<HT[l].weight<<"\t\t"<<HT[l].parent<<"\t"<<HT[l].lchild<<"\t"<<HT[l].rchild<<endl;
//	}
	for(i=n;i<m;++i){		//创建哈弗曼树 
		//在HT[1..i-1]选择parent为0且weight最小的两个节点，其序号记为S1，S2
		int S1=0,S2=0;
		for(int j=0;j<i;j++){
			if(HT[j].parent==0){
				S1=j;
				break;
			}
		}
		for(int j=0;j<i;j++){
			if(HT[j].parent==0&&HT[S1].weight>HT[j].weight){
				S1=j;
			}
		}
		HT[S1].parent=-1;
		for(int j=0;j<i;j++){
			if(HT[j].parent==0){
				S2=j;
				break;
			}
		}
		for(int j=0;j<i;j++){
			if(HT[j].parent==0&&HT[S2].weight>HT[j].weight){
				S2=j;
			}
		}
		HT[S1].parent=i;
		HT[S2].parent=i;
		HT[i].lchild=S1;
		HT[i].rchild=S2;
		HT[i].weight=HT[S1].weight+HT[S2].weight;
//		cout<<S1<<"\t"<<S2<<"\t"<<HT[S1].weight<<"\t"<<HT[S2].weight<<"\t"<<HT[i].weight<<endl;
	}
//	for(int l=0;l<m;l++){
//		cout<<l<<":"<<HT[l].weight<<"\t\t"<<HT[l].parent<<"\t"<<HT[l].lchild<<"\t"<<HT[l].rchild<<endl;
//	}
//	exit(0);
	//从叶子到根逆向求每个字符的哈夫曼编码
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));		//分配n个字符编码的头指针向量 
	char *cd=(char*)malloc(n*sizeof(char));				//分配求编码的工作区间
	cd[n-1]='\0';
	for(i=0;i<n;i++){				//逐个字符求编码 
		int start=n-1;				//编码结束符位置 
		int f=HT[i].parent;
		for(int c=i;f!=0;c=f,f=HT[f].parent){	//从叶节点到根逆向求编码 
			if(HT[f].lchild==c){
				cd[--start]='0';
			}
			else{
				cd[--start]='1';
			}
		}
		HC[i]=(char*)malloc(sizeof(char)*(n-start));	//为第i个字符分配编码空间
		HC[i][n-start-1]='\0';
		strcpy(HC[i],&cd[start]);
	}
	free(cd);
//	for(int k=0;k<n;k++){
//		if(k<26){
//			char a=k+97;
//			cout<<a<<":\t"<<HC[k]<<endl;
//		}
//		else{
//			char a=k+39;
//			cout<<a<<":\t"<<HC[k]<<endl;
//		}
//	}
	cout<<"字符编码完成"<<endl;
	return;
}

int main(){
	int letters[52]={0};			//字符出现次数 
	float rates[52]={0};			//字符出现频率 
	int sum=0;						//总字符数 
	int n=0;						//实际出现的字符种类数 
	char line[150];					//读取一行字符
	char **HC;						//存储哈夫曼编码 
	HTNode *HT=NULL;				//哈夫曼树节点数组 
	HC=(char**)malloc(sizeof(char*)*52); 
	fstream infile;
	infile.open("Hamlet.txt",ios::in);
	if(!infile){
		cout<<"file with error"<<endl;
		exit(0); 
	}
	cout<<"统计字符数据中，请稍候。。。"<<endl;
	while(!infile.eof()){
		infile.getline(line,150);
		for(int i=0;i<150;i++){
			switch(line[i]){
				case 'a':++letters[0];break;
				case 'b':++letters[1];break;
				case 'c':++letters[2];break;
				case 'd':++letters[3];break;
				case 'e':++letters[4];break;
				case 'f':++letters[5];break;
				case 'g':++letters[6];break;
				case 'h':++letters[7];break;
				case 'i':++letters[8];break;
				case 'j':++letters[9];break;
				case 'k':++letters[10];break;
				case 'l':++letters[11];break;
				case 'm':++letters[12];break;
				case 'n':++letters[13];break;
				case 'o':++letters[14];break;
				case 'p':++letters[15];break;
				case 'q':++letters[16];break;
				case 'r':++letters[17];break;
				case 's':++letters[18];break;
				case 't':++letters[19];break;
				case 'u':++letters[20];break;
				case 'v':++letters[21];break;
				case 'w':++letters[22];break;
				case 'x':++letters[23];break;
				case 'y':++letters[24];break;
				case 'z':++letters[25];break;
				case 'A':++letters[26];break;
				case 'B':++letters[27];break;
				case 'C':++letters[28];break;
				case 'D':++letters[29];break;
				case 'E':++letters[30];break;
				case 'F':++letters[31];break;
				case 'G':++letters[32];break;
				case 'H':++letters[33];break;
				case 'I':++letters[34];break;
				case 'J':++letters[35];break;
				case 'K':++letters[36];break;
				case 'L':++letters[37];break;
				case 'M':++letters[38];break;
				case 'N':++letters[39];break;
				case 'O':++letters[40];break;
				case 'P':++letters[41];break;
				case 'Q':++letters[42];break;
				case 'R':++letters[43];break;
				case 'S':++letters[44];break;
				case 'T':++letters[45];break;
				case 'U':++letters[46];break;
				case 'V':++letters[47];break;
				case 'W':++letters[48];break;
				case 'X':++letters[49];break;
				case 'Y':++letters[50];break;
				case 'Z':++letters[51];break;
				default:break;
			}
		}
	}
//	for(int i=0;i<52;i++){
//		cout<<letters[i]<<"\t";
//	}
	for(int k=0;k<52;k++){
		if(k<26){
			char a=k+97;
			cout<<a<<":"<<letters[k]<<"\t";
		}
		else{
			char a=k+39;
			cout<<a<<":"<<letters[k]<<"\t";
		}
	}
	cout<<endl;
	infile.close();
	for(int i=0;i<52;i++){
		sum+=letters[i];
	}
	for(int i=0;i<52;i++){
		rates[i]=(float)letters[i]/sum;
		if(rates[i])++n;
//		cout<<rates[i]<<"\t";
	}
//	cout<<n;
	HuffmanCoding(HT,HC,letters,52);		//生成编码表 
	//存储编码表 
	fstream outfile;
	outfile.open("HuffmanCode.txt",ios::out);
	if(!outfile){
		cout<<"file with error"<<endl;
		exit(0);
	}
	for(int k=0;k<52;k++){
		if(k<26){
			char a=k+97;
			outfile.put(a);
			outfile.put(':');
			for(int i=0;i<20;i++){
				if(HC[k][i]!='\0'){
					outfile.put(HC[k][i]);
				}
				if(HC[k][i]=='\0')break;
			}
			outfile.put('\n');
		}
		else{
			char a=k+39;
			outfile.put(a);
			outfile.put(':');
			for(int i=0;i<20;i++){
				if(HC[k][i]!='\0'){
					outfile.put(HC[k][i]);
				}
				if(HC[k][i]=='\0')break;
			}
			outfile.put('\n');
		}
	}
	cout<<"编码表已存储"<<endl; 
	outfile.close();
	//生成编码结果
	outfile.open("CodingResult.dat",ios::out|ios::binary);
	infile.open("Hamlet.txt",ios::in);
	if(!outfile||!infile){
		cout<<"file with error"<<endl;
		exit(0);
	}
	char r;
	while(!infile.eof()){
		r=infile.get();
//		cout<<r;
		if(r<123&&r>96){
			for(int i=0;i<20;i++){
				if(HC[r-97][i]=='\0')break;
				outfile.write((char*)&HC[r-97][i],sizeof(char));
			}
		}
		else if(r<91&&r>64){
			for(int i=0;i<20;i++){
				if(HC[r-39][i]=='\0')break;
				outfile.write((char*)&HC[r-39][i],sizeof(char));
			}
		}
	}
	outfile.close();
	infile.close();
	//根据编码结果还原文章
	infile.open("CodingResult.dat",ios::in|ios::binary);
	outfile.open("Return.txt",ios::out);
	if(!outfile||!infile){
		cout<<"file with error"<<endl;
		exit(0);
	}
	char read[20]={'2'};
	while(!infile.eof()){
		for(int i=0;i<20;i++){
			if(read[i]!='1'&&read[i]!='0'){
				infile.read((char*)&read[i],sizeof(char));
				read[i+1]='\0';
				break;
			}
		}
//		cout<<read<<endl;
		for(int i=0;i<52;i++){
			if(strcmp(read,HC[i])==0){
				if(i<26)outfile.put(i+97);
				else if(i>=26)outfile.put(i+39);
				for(int j=0;j<20;j++)read[j]='2';
			}
		}
	}
	infile.close();
	outfile.close();
	cout<<"文章还原完成"<<endl;
	return 0;
}
