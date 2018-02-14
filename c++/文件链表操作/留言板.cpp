#include<iostream>
#include<fstream>
#include<string.h>
#include<stdlib.h>
using namespace std;

typedef struct Msg{
	char h[41];
	char b[201];
	Msg* next;
} msg,*msgp;

void add(){
	msg one;
	one.next=NULL;
	fstream outfile;
	outfile.open("msg.dat",ios::out|ios::app|ios::binary);
	if(outfile.fail()){
		cout<<"file with error";
		exit(0);
	}
	cout<<"输入标题：";
	while(true)
	{
		cin.getline(one.h,41,'\n');
		if(strlen(one.h)==0)
		{
			cout<<"您还没输入标题!"<<endl;
			cout<<"请输入标题：";
		}else
			break;
	}
	//cin.getline(one->h,41); 
	cout<<"输入留言内容："<<endl;
	while(true)
	{
		cin.getline(one.b,41,'\n');
		if(strlen(one.b)==0)
		{
			cout<<"您还没输入内容!"<<endl;
			cout<<"请输入内容：";
		}else
			break;
	}
	//cin.getline(one->b,201);
	outfile.seekp(0L,ios::end); 
	outfile.write((char*)&one,sizeof(msg));
	cout<<"保存成功"<<endl;
	outfile.close();
}
void del(){
	Msg one;
	bool isexist=false;
	char h[41];
	one.next=NULL;
	fstream infile;
	infile.open("msg.dat",ios::in|ios::binary);
	if(infile.fail()){
		cout<<"file with error";
		return;
	}
	cout<<"输入要删除的留言标题：";
	cin.getline(h,40,'\n');
	//取出留言结构体 
	msgp head,p,q;
	q=head=&one;
	p=(msgp)malloc(sizeof(msg));
	infile.clear();
	infile.seekg(0L,ios::beg);
	infile.read((char*)p,sizeof(msg));
	while(!infile.eof()){
		if(strcmp(p->h,h)!=0){
			q->next=p;
			q=p;
		}
		else isexist=true;
		p=(msgp)malloc(sizeof(msg));
		infile.read((char*)p,sizeof(msg));
	}
	infile.close();
	if(!isexist){
		cout<<"该留言不存在"<<endl;
		return;
	}
	//存入留言结构体 
	fstream outfile;
	outfile.seekp(0,ios::beg); 
	outfile.open("msg.dat",ios::out|ios::binary);
	if(outfile.fail()){
		cout<<"file with error";
		return; 
	}
	q=head->next;
	while(q!=NULL){
		outfile.write((char*)q,(sizeof(msg)));
		q=q->next;
	}
	outfile.close();
	cout<<"删除成功"<<endl;
}
void chg(){
	Msg one,chg;
	bool isexist=false;
	chg.next=NULL;
	fstream infile;
	infile.open("msg.dat",ios::in|ios::binary);
	if(infile.fail()){
		cout<<"file with error";
		return;
	}
	cout<<"输入要修改的留言标题：";
	cin.getline(chg.h,40,'\n');
	cout<<"输入修改后的留言内容："<<endl;
	cin.getline(chg.b,200,'\n');
	//取出留言结构体 
	msgp head,p,q;
	q=head=&one;
	p=(msgp)malloc(sizeof(msg));
	infile.clear();
	infile.seekg(0L,ios::beg);
	infile.read((char*)p,sizeof(msg));
	while(!infile.eof()){
		if(strcmp(p->h,chg.h)!=0){
			q->next=p;
			q=p;
		}
		else{
			q->next=&chg;
			q=&chg;
			isexist=true;	
		}
		p=(msgp)malloc(sizeof(msg));
		infile.read((char*)p,sizeof(msg));
	}
	infile.close();
	if(!isexist){
		cout<<"该留言不存在"<<endl;
		return;
	}
	//存入留言结构体 
	fstream outfile;
	outfile.seekp(0,ios::beg); 
	outfile.open("msg.dat",ios::out|ios::binary);
	if(outfile.fail()){
		cout<<"file with error";
		return; 
	}
	q=head->next;
	while(q!=NULL){
		outfile.write((char*)q,(sizeof(msg)));
		q=q->next;
	}
	outfile.close();
	cout<<"修改成功"<<endl;
}
void dsp(){
//	msgp one;
//	one=(msgp)malloc(sizeof(msg));
//	one->next=NULL;
	msg one;
	one.next=NULL;
	fstream infile;
	infile.open("msg.dat",ios::in|ios::binary);
	if(infile.fail()){
		cout<<"file with error";
		return;
	}
	infile.clear();
	infile.seekg(0L,ios::beg);
	infile.read((char*)&one,sizeof(msg));
	if(infile.eof( )){
		cout<<"文件中还没有信息!"<<endl;
		return;
	}
	while(!infile.eof()){
		cout<<"标题："<<one.h<<endl;
		cout<<"内容："<<one.b<<endl<<endl;
		infile.read((char*)&one,sizeof(msg));
	}
	cout<<"留言显示完毕"<<endl; 
	infile.close();
}

int main(){
	//cout<<sizeof(msg)<<endl<<sizeof(Msg);
	int n;
	while(1){
		cout<<"选择留言板操作："<<endl;
		cout<<"----1.添加留言"<<endl;
		cout<<"----2.删除留言"<<endl;
		cout<<"----3.修改留言"<<endl;
		cout<<"----4.查看所有留言"<<endl;
		cout<<"----5.退出程序"<<endl;
		cin>>n;
		cin.ignore();
		switch(n){
			case 1:add();break;
			case 2:del();break;
			case 3:chg();break;
			case 4:dsp();break;
			case 5:exit(0);
			default:cout<<"输入错误"<<endl;
		}
	}
} 
