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
	cout<<"������⣺";
	while(true)
	{
		cin.getline(one.h,41,'\n');
		if(strlen(one.h)==0)
		{
			cout<<"����û�������!"<<endl;
			cout<<"��������⣺";
		}else
			break;
	}
	//cin.getline(one->h,41); 
	cout<<"�����������ݣ�"<<endl;
	while(true)
	{
		cin.getline(one.b,41,'\n');
		if(strlen(one.b)==0)
		{
			cout<<"����û��������!"<<endl;
			cout<<"���������ݣ�";
		}else
			break;
	}
	//cin.getline(one->b,201);
	outfile.seekp(0L,ios::end); 
	outfile.write((char*)&one,sizeof(msg));
	cout<<"����ɹ�"<<endl;
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
	cout<<"����Ҫɾ�������Ա��⣺";
	cin.getline(h,40,'\n');
	//ȡ�����Խṹ�� 
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
		cout<<"�����Բ�����"<<endl;
		return;
	}
	//�������Խṹ�� 
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
	cout<<"ɾ���ɹ�"<<endl;
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
	cout<<"����Ҫ�޸ĵ����Ա��⣺";
	cin.getline(chg.h,40,'\n');
	cout<<"�����޸ĺ���������ݣ�"<<endl;
	cin.getline(chg.b,200,'\n');
	//ȡ�����Խṹ�� 
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
		cout<<"�����Բ�����"<<endl;
		return;
	}
	//�������Խṹ�� 
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
	cout<<"�޸ĳɹ�"<<endl;
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
		cout<<"�ļ��л�û����Ϣ!"<<endl;
		return;
	}
	while(!infile.eof()){
		cout<<"���⣺"<<one.h<<endl;
		cout<<"���ݣ�"<<one.b<<endl<<endl;
		infile.read((char*)&one,sizeof(msg));
	}
	cout<<"������ʾ���"<<endl; 
	infile.close();
}

int main(){
	//cout<<sizeof(msg)<<endl<<sizeof(Msg);
	int n;
	while(1){
		cout<<"ѡ�����԰������"<<endl;
		cout<<"----1.�������"<<endl;
		cout<<"----2.ɾ������"<<endl;
		cout<<"----3.�޸�����"<<endl;
		cout<<"----4.�鿴��������"<<endl;
		cout<<"----5.�˳�����"<<endl;
		cin>>n;
		cin.ignore();
		switch(n){
			case 1:add();break;
			case 2:del();break;
			case 3:chg();break;
			case 4:dsp();break;
			case 5:exit(0);
			default:cout<<"�������"<<endl;
		}
	}
} 
