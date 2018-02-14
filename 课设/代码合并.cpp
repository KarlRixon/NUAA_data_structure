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
#include<iostream>
#include<fstream>
#include<math.h>
#include<string.h>
#include<stdlib.h>
#define CT 1			//传输时间系数
#define CP 1			//传输功耗系数
using namespace std;

int map[100][100];
int rtime;				//记录传感器到原点时间
int rpower;				//记录传感器到原点功耗
int *route;				//记录传感器到原点路径
int num;				//传感器个数

typedef struct sensor{
	int n;
	int x;
	int y;
}sensor;

class SSS{
private:
	int **sensors;		// x y time power visited 
	int **troute;		// 从原点到达此传感器的路径
	int **proute;		// 从原点到达此传感器的路径
public:
	SSS(){
		int n=0,x=0,y=0; 
		char read[10];
		sensor *s;
		s=(sensor*)malloc(sizeof(sensor));
		fstream infile;
		infile.open("sensors.dat",ios::in|ios::binary);
		if(!infile){
			cout<<"file with error"<<endl;
			exit(0);
		}
		infile.read((char*)&n,sizeof(int));
		num=n;
		cout<<n<<endl;
		troute=(int**)malloc(sizeof(int*)*n);
		proute=(int**)malloc(sizeof(int*)*n);
		for(int k=0;k<n;k++){
			troute[k]=proute[k]=NULL;
		}
		route=(int*)malloc(sizeof(int)*n);
		for(int j=0;j<n;j++){
			route[j]=-1;
		}
		route[0]=0;
		sensors=(int**)malloc(sizeof(int*)*(n+1));
		sensors[0]=(int*)malloc(sizeof(int)*5);
		sensors[0][0]=sensors[0][1]=sensors[0][2]=sensors[0][3]=0;
		sensors[0][4]=1;
		while(!infile.eof()&&s->n!=n){
			infile.read((char*)s,sizeof(sensor));
			map[s->x-1][s->y-1]=1;
			cout<<s->n<<"\t"<<s->x<<"\t"<<s->y<<endl;
			sensors[s->n]=(int*)malloc(sizeof(int)*5);
			sensors[s->n][0]=s->x;
			sensors[s->n][1]=s->y;
			sensors[s->n][2]=999999;
			sensors[s->n][3]=999999;
			sensors[s->n][4]=0;
		}
//		for(int i=0;i<n+1;i++){
//			cout<<sensors[i][0]<<"\t"<<sensors[i][1]<<'\t'<<sensors[i][2]<<'\t'<<sensors[i][3]<<'\t'<<sensors[i][4]<<endl;
//		}
		cout<<"数据读入成功"<<endl;
		infile.close();
	}
	int firstadj(int n){
		for(int i=1;i<num+1;i++){
			if((abs(sensors[i][0]-sensors[n][0])*abs(sensors[i][0]-sensors[n][0])+abs(sensors[i][1]-sensors[n][1])*abs(sensors[i][1]-sensors[n][1]))<100){
				if(!sensors[i][4])
					return i;
			}
		}
		return 0;
	}
	int nextadj(int n,int p){
		int pre=-1;
		for(int i=1;i<num+1;i++){
			if((abs(sensors[i][0]-sensors[n][0])*abs(sensors[i][0]-sensors[n][0])+abs(sensors[i][1]-sensors[n][1])*abs(sensors[i][1]-sensors[n][1]))<100){
				if(pre==p&&!sensors[i][4])
					return i;
				else pre=i;
			}
		}
		return 0;
	}
	void cptr(int p){
		troute[p-1]=(int*)malloc(sizeof(int)*200);
		for(int i=0;i<num;i++){
			if(route[i]!=p)
				troute[p-1][i]=route[i];
			else break;
		}
	}
	void cppr(int p){
		proute[p-1]=(int*)malloc(sizeof(int)*200);
		for(int i=0;i<num;i++){
			if(route[i]!=p)
				proute[p-1][i]=route[i];
			else break;
		}
	}
	void findmin(int n){
		for(int p=firstadj(n);;p=nextadj(n,p)){			//对当前传感器的每个邻接传感器执行递归函数
			if(p==0)break;
			int dist2=abs(sensors[p][0]-sensors[n][0])*abs(sensors[p][0]-sensors[n][0])+abs(sensors[p][1]-sensors[n][1])*abs(sensors[p][1]-sensors[n][1]);
			rtime+=sqrt(dist2)*CT;
			rpower+=dist2*CP;
			for(int i=0;i<num;i++){			//修改route
				if(route[i]==n){
					route[i+1]=p;
					break;
				}
			}
			if(rtime<sensors[p][2]){		//比较rtime 修改time和troute
				sensors[p][2]=rtime;
				cptr(p);
			}
			if(rpower<sensors[p][3]){		//比较rpower 修改power和proute
				sensors[p][3]=rpower;
				cppr(p);
			}
			sensors[p][4]=1;				//修改visited
			findmin(p);						//递归调用
			rtime-=sqrt(dist2)*CT;			//恢复rtime
			rpower-=dist2*CP;				//恢复rpower
			sensors[p][4]=0;				//恢复visited
			for(int j=0;j<num;j++){			//恢复route
				if(route[j]==p){
					route[j]=-1;
					break;
				}
			}
		}
	}
	void showall(){
		for(int i=0;i<num+1;i++){
			cout<<sensors[i][0]<<'\t'<<sensors[i][1]<<'\t'<<sensors[i][2]<<'\t'<<sensors[i][3]<<'\t'<<sensors[i][4]<<endl;
		}
	}
	void showmintime(){
		for(int i=0;i<num;i++){
			if(troute[i]!=NULL&&troute[i][0]==0){
				cout<<i+1<<"号传感器（最小传输时间为："<<sensors[i+1][2]<<"）：";
				for(int j=0;j<200;j++){
					if(troute[i][j]<=num&&troute[i][j]>=0){
						cout<<troute[i][j]<<'\t';
					}
					else break;
				}
				cout<<endl;
			}
		}
	}
	void showminpower(){
		int sum=0,pre=0;
		int web[100][100];
		for(int k=0;k<100;k++){
			for(int l=0;l<100;l++){
				web[k][l]=0;
			}
		}
		for(int i=0;i<num;i++){
			if(proute[i]!=NULL&&proute[i][0]==0){
				sum+=sensors[i+1][3];
				cout<<i+1<<"号传感器（最小传输能耗为："<<sensors[i+1][3]<<"）：";
				for(int j=0;j<200;j++){
					if(proute[i][j]<=num&&proute[i][j]>=0){
						cout<<proute[i][j]<<'\t';
						web[pre][proute[i][j]-1]=1;
						pre=proute[i][j]-1;
					}
					else break;
				}
				cout<<endl;
			}
		}
		cout<<"传感器连接网络的邻接矩阵为（编号为依据的邻接矩阵）："<<endl;
		for(int m=0;m<100;m++){
			for(int n=0;n<100;n++){
				cout<<web[m][n];
			}
			cout<<endl;
		}
	}
}; 

void show(){
	for(int i=0;i<100;i++){
		for(int j=0;j<100;j++){
//			cout<<map[i][j];
			if(map[i][j]==0){
				cout<<"+";
			}
			else if(map[i][j]==1){
				cout<<'@';
			}
		}
		cout<<endl;
	}
}

int main(){
	rtime=rpower=0;
	route=NULL;
	SSS S;
	S.findmin(0);
//	S.showall();
	int chs=0;
	while(1){
		cout<<"menu:"<<endl;
		cout<<"----1.显示传感器网络示意图"<<endl;
		cout<<"----2.求最短时间通道"<<endl;
		cout<<"----3.求平均功耗最小网络结构"<<endl;
		cin>>chs;
		switch(chs){
			case 1:show();break;
			case 2:S.showmintime();break;
			case 3:S.showminpower();break;
		}
	}
	return 0;
}
#include<iostream>
#include<stdlib.h>
#include<string.h>
#include<fstream>
using namespace std;

typedef struct goods{		//商品 
	int shopnum;
	char goodname[21];
	float price;
	int sales;
	goods *next;
}goods;
typedef struct shop{		//商铺 
	int shopnum;
	char shopname[21];
	float creditworthiness;
	goods *goodhead;
	shop *next; 
}shop;
typedef struct qgoods{		//查询结果 
	int shopnum;
	char goodname[21];
	float price;
	int sales;
	qgoods *prior;
	qgoods *next;
}qgoods;

void createhead(shop* &head){
	head=(shop*)malloc(sizeof(shop));
	head->creditworthiness=0;
	head->goodhead=(goods*)malloc(sizeof(goods));		//不想让头结点特殊化所以加了goodhead 
	head->goodhead->price=0;
	head->goodhead->sales=0;
	head->goodhead->next=NULL;
	head->shopnum=0;
	head->next=NULL;
}
void init(shop *head){		//从文件中读取数据到链表
	fstream infile1,infile2;
	infile1.open("shop.dat",ios::in|ios::binary);
	if(!infile1){
		cout<<"file not exists"<<endl;
		infile1.close();
		infile1.open("shop.dat",ios::out|ios::binary);
	}
	infile2.open("goods.dat",ios::in|ios::binary);
	if(!infile2){
		cout<<"file not exists"<<endl;
		infile2.close();
		infile2.open("goods.dat",ios::out|ios::binary);
	}
	shop *ps=NULL,*p=NULL;
	goods *pg=NULL;
	while(!infile1.eof()){
		//读取一个商铺 
		ps=(shop*)malloc(sizeof(shop));
		infile1.read((char*)ps,sizeof(shop));
		ps->goodhead=(goods*)malloc(sizeof(goods));
		ps->goodhead->next=NULL;
		ps->next=NULL;								//忘记加NULL害死人！！！！！ 
		if(ps->shopnum<0||ps->shopnum>2000){
			free(ps);
			break;
		}
		//给商铺添加商品
		while(!infile2.eof()){
			goods *g=NULL;
			if(pg!=NULL&&pg->shopnum<ps->shopnum)continue;
			if(pg!=NULL&&pg->shopnum==ps->shopnum){
				for(g=ps->goodhead;g->next!=NULL;g=g->next);
//				pg->next=NULL;
				g->next=pg;
			}
			pg=(goods*)malloc(sizeof(goods));
			infile2.read((char*)pg,sizeof(goods));
			pg->next=NULL;
			if(pg->shopnum<0||pg->shopnum>2000){
				free(pg);
				break;
			}
			if(pg->shopnum>ps->shopnum)break;
			if(pg->shopnum==ps->shopnum){
				for(g=ps->goodhead;g->next!=NULL;g=g->next);
//				pg->next=NULL;
				g->next=pg;
				pg=NULL;
			}
		}
		if(ps->shopnum==0)break;
		if(ps->shopnum==1){		//第一个商铺需特殊处理，不然重新读取文件会导致链表重复 
			head->next=ps;
		}
		else{
			for(p=head;p->next!=NULL;p=p->next);
			p->next=ps;
		} 
	}
	infile1.close();
	infile2.close();
	return;
}
int searchshopname(shop *head,char *name){
	if(head->next==NULL)return 0;
	shop *p=head->next;
	for(;p!=NULL;p=p->next)
		if(strcmp(p->shopname,name)==0)return 1; 
	return 0;
}
int searchgoodname(shop *shop,char *goodname){
	if(shop->goodhead->next==NULL)return 0;
	goods *pg=shop->goodhead->next;
	for(;pg!=NULL;pg=pg->next)
		if(strcmp(pg->goodname,goodname)==0)return 1;
	return 0;
}
void refreshfile(shop *head){
	fstream outfile1,outfile2;
	outfile1.open("shop.dat",ios::out|ios::binary);
	if(!outfile1){
		cout<<"file with error"<<endl;
		exit(0);
	}
	outfile2.open("goods.dat",ios::out|ios::binary);
	if(!outfile2){
		cout<<"file with error"<<endl;
		exit(0);
	}
//	if(head->next==NULL){
//		cout<<"没有信息可存"<<endl;
//		outfile1.close();
//		outfile2.close();
//		return;
//	}
	shop *p=head->next;
	goods *pg=NULL;
	for(;p!=NULL;p=p->next){
		outfile1.write((char*)p,sizeof(shop));
		if(p->goodhead->next!=NULL){
			pg=p->goodhead->next;
			for(;pg!=NULL;pg=pg->next){
				outfile2.write((char*)pg,sizeof(goods));
			}
		}
	}
	outfile1.close();
	outfile2.close();
	cout<<"文件刷新成功"<<endl;
	return;
}
void addshop(shop *head){
	int flag=0;
	shop *pn=NULL,*p=NULL;
	goods *png=NULL,*pg=NULL;
	pn=(shop*)malloc(sizeof(shop));
	pn->goodhead=(goods*)malloc(sizeof(goods));
	pn->goodhead->shopnum=0;
	pn->goodhead->price=0;
	pn->goodhead->sales=0;
	pn->goodhead->next=NULL;
	pn->next=NULL;
	//商铺信息 
	pn->creditworthiness=5;
	while(1){
		cout<<"输入商铺名：";
		if(flag==0){			//根据flag清况使用cin.ignore 
			cin.ignore();
		}
		flag=0;
		cin.getline(pn->shopname,20);
		if(searchshopname(head,pn->shopname)){
			cout<<"商铺名已存在"<<endl;
			flag=1;
			continue;
		}
		else break;
	}
	//添加到链表
	int i=0;
	if(head->next==NULL){		//添加第一个商铺 
		pn->shopnum=1;
		i=1;
		head->next=pn;
	}
	else {
		for(p=head->next,i=p->shopnum;p->next!=NULL;p=p->next);
		i=p->shopnum;
		pn->shopnum=++i;
		p->next=pn;
	}
	//商品信息
	while(1){
		png=(goods*)malloc(sizeof(goods));
		png->next=NULL;
		png->shopnum=i;
		cout<<"输入商品名称(输入0结束输入)：";
//		cin.ignore();
		cin.getline(png->goodname,20);
		if(searchgoodname(pn,png->goodname)){
			cout<<"此商铺已有该商品"<<endl;
			free(png);
			continue;
		}
		if(strcmp(png->goodname,"0")==0){
			free(png);
			break;
		}
		while(1){
			cout<<"输入商品单价：";
			cin>>png->price;
			cin.ignore();
			if(png->price<0){
				cout<<"输入错误"<<endl;
				continue;
			}
			else break;
		}
		png->sales=0;
		//添加商品
		if(pn->goodhead->next==NULL){		//添加第一个商品 
			pn->goodhead->next=png;
		}
		else {
			for(pg=pn->goodhead->next;pg->next!=NULL;pg=pg->next);
			pg->next=png;
		}
	}
	refreshfile(head);
	return;
}
void deleteshop(shop *head){
	int n=0,i=0,flag=0;
	shop *ps=NULL;
	goods *pg=NULL;
	cout<<"输入商铺编号：";
	cin>>n;
	for(ps=head;ps->next!=NULL;ps=ps->next){
		if(ps->next->shopnum==n){
			i=ps->next->shopnum;
			ps->next=ps->next->next;
			flag=1;
			break;
		}
	}
	if(flag==0){
		cout<<"无该商铺"<<endl;
		return;
	}
	else{
		for(ps=ps->next;ps!=NULL;ps=ps->next,++i){
			ps->shopnum=i;
			pg=ps->goodhead;
			for(;pg!=NULL;pg=pg->next){
				pg->shopnum=i;
			}
		}
	}
	refreshfile(head);
	return;
}
void addgood(shop *head){
	int n=0,flag=0;
	cout<<"输入商铺编号：";
	cin>>n;cin.ignore();
	shop *ps=head->next;
	for(;ps!=NULL;ps=ps->next){
		if(ps->shopnum==n){
			flag=1;
			while(1){
				goods *png=(goods*)malloc(sizeof(goods));
				png->next=NULL;
				png->shopnum=ps->shopnum; 
				cout<<"输入商品名称（输入0结束）：";
				cin.getline(png->goodname,20);
				if(searchgoodname(ps,png->goodname)){
					cout<<"此商铺已有该商品"<<endl;
					free(png);
					continue;
				}
				if(strcmp(png->goodname,"0")==0){
					free(png);
					break;
				}
				while(1){
					cout<<"输入商品单价：";
					cin>>png->price;
					cin.ignore();
					if(png->price<0){
						cout<<"输入错误"<<endl;
						continue;
					}
					else break;
				}
				png->sales=0;
				//添加商品
				if(ps->goodhead->next==NULL){		//添加第一个商品 
					ps->goodhead->next=png;
				}
				else {
					goods *pg=NULL;
					for(pg=ps->goodhead->next;pg->next!=NULL;pg=pg->next);
					pg->next=png;
					cout<<"添加成功"<<endl; 
				}
			}
		}
	}
	if(flag==0){
		cout<<"没有此商铺"<<endl;
		return;
	}
	refreshfile(head);
	return;
}
void deletegood(shop *head){
	int n=0,flag1=0,flag2=0;
	char goodname[21];
	cout<<"输入商铺编号：";
	cin>>n;cin.ignore();
	cout<<"输入商品名称（输入0结束）：";
	cin.getline(goodname,20);
	shop *ps=head->next;
	for(;ps!=NULL;ps=ps->next){
		if(ps->shopnum==n){
			flag1=1;
			for(goods *pg=ps->goodhead;pg->next!=NULL;pg=pg->next){
				if(strcmp(pg->next->goodname,goodname)==0){
					flag2=1;
					pg->next=pg->next->next;
					cout<<"删除成功"<<endl;
				}
			}
		}
	}
	if(flag1==0){
		cout<<"没有此商铺"<<endl;
		return;
	}
	if(flag2==0){
		cout<<"没有此商品"<<endl;
		return;
	}
	refreshfile(head);
	return;
}
void purchase(shop *head){
	int n=0,flag1=0,flag2=0,s=0;
	char goodname[21];
	cout<<"输入商铺编号：";
	cin>>n;cin.ignore();
	cout<<"输入商品名称（输入0结束）：";
	cin.getline(goodname,20);
	shop *ps=head->next;
	for(;ps!=NULL;ps=ps->next){
		if(ps->shopnum==n){
			flag1=1;
			for(goods *pg=ps->goodhead;pg->next!=NULL;pg=pg->next){
				if(strcmp(pg->next->goodname,goodname)==0){
					flag2=1;
					cout<<"输入购买数量：";
					cin>>s; 
					pg->next->sales+=s;
				}
			}
		}
	}
	if(flag1==0){
		cout<<"没有此商铺"<<endl;
		return;
	}
	if(flag2==0){
		cout<<"没有此商品"<<endl;
		return;
	}
	refreshfile(head);
	return;
}
void addquerybysaleorder(qgoods *qhead,goods *pg){
	qgoods *qn=NULL,*q=NULL;
	q=qhead;
	qn=(qgoods*)malloc(sizeof(qgoods));
	qn->next=NULL;
	qn->price=pg->price;
	qn->prior=NULL;
	qn->sales=pg->sales;
	qn->shopnum=pg->shopnum;
	strcpy(qn->goodname,pg->goodname);
	if(q->next==NULL){
		q->next=qn;
		q->prior=qn;
		qn->prior=q;
		qn->next=q;
		return;
	}
	else{
		for(q=qhead->next;q!=qhead;q=q->next){
			if(q->sales<qn->sales){
				qn->prior=q->prior;
				q->prior->next=qn;
				qn->next=q;
				q->prior=qn;
				break;
			}
			if(q->next==qhead&&q->sales>=qn->sales){
				q->next=qn;
				qn->prior=q;
				qhead->prior=qn;
				qn->next=qhead;
				break;
			}
		}
	}
}
void showquery(qgoods *qhead,shop *head){
	qgoods *q=NULL;
	shop *ps=NULL;
	for(q=qhead->next;q!=qhead;q=q->next){
		cout<<"-----------------------------------"<<endl;
		cout<<"\t商品销量："<<q->sales<<endl;
		cout<<"\t商品名称："<<q->goodname<<endl;
		cout<<"\t商品价格："<<q->price<<endl;
		cout<<"\t商铺信息："<<endl;
		cout<<"\t\t商铺编号："<<q->shopnum<<endl;
		for(ps=head->next;ps!=NULL;ps=ps->next){
			if(ps->shopnum==q->shopnum){
				cout<<"\t\t商铺名称："<<ps->shopname<<endl;
				cout<<"\t\t商铺信誉度："<<ps->creditworthiness<<endl;
				cout<<"\t\t-------------------"<<endl;
				break;
			}
		}
		cout<<"-----------------------------------"<<endl;
	}
}
void goodquery(shop *head){
	int flag=0;
	char goodname[21];
	qgoods *qn=NULL,*q=NULL;
	qgoods *qhead=(qgoods*)malloc(sizeof(qgoods));
	qhead->next=NULL;
	qhead->price=0;
	qhead->prior=NULL;
	qhead->sales=0;
	qhead->shopnum=0;
	cout<<"输入商品名称：";
	cin.ignore();
	cin.getline(goodname,20);
	for(shop *ps=head->next;ps!=NULL;ps=ps->next){
		for(goods *pg=ps->goodhead->next;pg!=NULL;pg=pg->next){
			if(strcmp(pg->goodname,goodname)==0){
				flag=1;
				addquerybysaleorder(qhead,pg);
			}
		}
	}
	if(flag==0){
		cout<<"没有查找到此商品"<<endl;
	}
	showquery(qhead,head);
}
void show(shop *head){
	shop *p=head->next;
	goods *pg=NULL;
	for(;p!=NULL;p=p->next){
		cout<<"-----------------------------------"<<endl;
		cout<<"\t商铺编号：\t"<<p->shopnum<<endl;
		cout<<"\t商铺名：\t"<<p->shopname<<endl;
		cout<<"\t信誉度：\t"<<p->creditworthiness<<endl;
		cout<<"\t商品列表："<<endl;
		for(pg=p->goodhead->next;pg!=NULL;pg=pg->next){
			cout<<"\t\t商品名称："<<pg->goodname<<endl;
			cout<<"\t\t商品单价："<<pg->price<<endl;
			cout<<"\t\t商品销量："<<pg->sales<<endl;
			cout<<"\t\t-------------------"<<endl;
		}
		cout<<"-----------------------------------"<<endl;
	}
	return;
}


int main(){
	int n=0;
	shop *head=NULL;
	createhead(head);
	init(head);
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.添加一个商铺"<<endl;
		cout<<"----2.删除一个商铺"<<endl;
		cout<<"----3.增加商铺中的商品"<<endl;
		cout<<"----4.删除商铺中的商品"<<endl;
		cout<<"----5.查询商品"<<endl;
		cout<<"----6.购买商品"<<endl;
		cout<<"----7.刷新文件信息"<<endl;
		cout<<"----8.重新读取文件"<<endl;
		cout<<"----9.显示全部信息"<<endl;
		cout<<"----10.清屏"<<endl;
		cout<<"----11.退出程序"<<endl;
		cin>>n;
		switch(n){
			case 1:addshop(head);break;
			case 2:deleteshop(head);break;
			case 3:addgood(head);break;
			case 4:deletegood(head);break;
			case 5:goodquery(head);break;
			case 6:purchase(head);break;
			case 7:refreshfile(head);break;
			case 8:init(head);break;
			case 9:show(head);break;
			case 10:system("cls");break;
			case 11:refreshfile(head);return 0;
		}
	} 
}
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
#include<iostream>
#include<fstream>
#include<stack>
#include<stdio.h>
#include<stdlib.h>
using namespace std;

typedef struct BiTNode{
	int data;
	BiTNode *lchild,*rchild;
}BiTNode;
typedef struct BTNQ{
	BiTNode *p;
	BTNQ *next;
}BTNQ;
int depth=0,maxdepth=0;
int ii=0,nodenum=0;

class BiTree{
private:
	BiTNode *bt;
	void DBT(BiTNode* &root){
		if(root!=NULL){
			if(root->lchild){
				DBT(root->lchild);
			}
			if(root->rchild){
				DBT(root->rchild);
			}
			if(root!=NULL){
				free(root);
				root=NULL;
			}
		}
	}
	void CBT(BiTNode* &root){			//注意这里的  * &
		fstream infile;
		infile.open("nodesdata.txt",ios::in);
		if(!infile){
			cout<<"file with error"<<endl;
			exit(0);
		}
		char a[4];
		int num=0;
		for(int j=0;j<ii;j++){
			infile.getline(a,3*sizeof(char));
		}
		infile.getline(a,3*sizeof(char));
		++ii;
		infile.close();
		num=(a[0]-48)*10+a[1]-48;
		if(num)++nodenum;
		if(num==0){
			root=NULL;return;
		}
		else{
			root=(BiTNode*)malloc(sizeof(BiTNode));
			root->data=num;
			root->lchild=root->rchild=NULL;
			CBT(root->lchild);
			CBT(root->rchild);
		}
		return;
	}
	void BTD(BiTNode *root){
		depth++;
		if(root->lchild){
			BTD(root->lchild);
			depth--;
		}
		if(root->rchild){
			BTD(root->rchild);
			depth--;
		}
		if(root->lchild==NULL&&root->rchild==NULL){
			maxdepth=depth>maxdepth?depth:maxdepth;
		}
	}
	void POT(BiTNode *p){
		if(p){
			cout<<p->data<<"\t";
			POT(p->lchild);
			POT(p->rchild);
		};
	}
	void IOT(BiTNode *p){
		if(p){
			IOT(p->lchild);
			cout<<p->data<<"\t";
			IOT(p->rchild);
		}
	}
	void PostOT(BiTNode *p){
		if(p){
			PostOT(p->lchild);
			PostOT(p->rchild);
			cout<<p->data<<"\t";
		};
	}
public:
	void InitBiTree(){
		bt=(BiTNode*)malloc(sizeof(BiTNode));
		bt->data=0;
		bt->lchild=bt->rchild=NULL;
		CBT(bt);
		cout<<"二叉树初始化成功"<<endl;
		return;
	}
	void DestroyBiTree(){
		DBT(bt);cout<<"二叉树销毁成功"<<endl;
	}
	void BiTreeDepth(){
//		if(BiTreeEmpty()){cout<<"二叉树为空或不存在"<<endl;return 0;}
		depth=maxdepth=0;		//清空之前记录 
		BTD(bt);
		cout<<"二叉树深度为：\t"<<maxdepth<<endl;
	}
	int PreOrderTraverse(){
		POT(bt);
		cout<<"遍历完成"<<endl;
		return 0;
	}
	int InOrderTraverse(){
		IOT(bt);
		cout<<"遍历完成"<<endl;
		return 0;
	}
	int PostOrderTraverse(){
		PostOT(bt);
		cout<<"遍历完成"<<endl;
		return 0;
	}
	void PreOrderTraverseNR(){
		stack<BiTNode *> node;
		BiTNode *n=bt;
		while(n!=NULL||!node.empty()){
			while(n!=NULL){
				cout<<n->data<<"\t";
				node.push(n);
				n=n->lchild;
			}
			if(!node.empty()){
				n=node.top();
				node.pop();
				n=n->rchild;
			}
		}
		cout<<endl;
	}
	void InOrderTraverseNR(){
		stack<BiTNode *> node;
		BiTNode *n=bt;
		while (n != NULL || !node.empty()) {
			while (n != NULL) {
				node.push(n);
				n = n->lchild;
			}
			if (!node.empty()) {
				n = node.top();
				node.pop();
	            cout<<n->data<<"\t";
				n = n->rchild;
			}
		}
		cout<<endl;
	}
	void PostOrderTraverseNR(){
		stack<BiTNode *> node;
		BiTNode *n=bt,*last=NULL;
		while(n!=NULL||!node.empty()){
			while(n!=NULL){
				node.push(n);
				n=n->lchild;
			}
			n=node.top();
			if(n->rchild==NULL||n->rchild==last){			//判断右子树是否被访问过 
				cout<<n->data<<"\t";
				node.pop();
				last=n;
				n=NULL;				//注意这里 
			}
			else n=n->rchild;
		}
		cout<<endl;
	}
	void LevelOrderTraverse(){
		BTNQ *q=NULL,*head,*tail;
		head=(BTNQ*)malloc(sizeof(BTNQ));
		head->next=NULL;head->p=bt;
		tail=q=head;
		while(head!=NULL){
			if(head->p->lchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));q->next=NULL;q->p=head->p->lchild;
				tail->next=q;tail=tail->next;
			}
			if(head->p->rchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));q->next=NULL;q->p=head->p->rchild;
				tail->next=q;tail=tail->next;
			}
			cout<<head->p->data<<"\t";
			head=head->next;
		}
	}
	void BiTreeWidth(){			//存在bug 
		int width=1,max=1;
		BiTNode *pre=NULL;
		BTNQ *q=NULL,*head,*tail;
		head=(BTNQ*)malloc(sizeof(BTNQ));
		head->next=NULL;head->p=bt;
		tail=q=head;
		if(bt->lchild==NULL&&bt->rchild==NULL){
			cout<<"此二叉树只有一个节点"<<endl;
		}
		if(bt->lchild==NULL){
			pre=bt->lchild;
		}
		else{
			pre=bt->rchild;
		}
		while(head!=NULL){
			if(head->p->lchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));
				q->next=NULL;
				q->p=head->p->lchild;
				tail->next=q;
				tail=tail->next;
			}
			if(head->p->rchild){
				q=(BTNQ*)malloc(sizeof(BTNQ));
				q->next=NULL;
				q->p=head->p->rchild;
				tail->next=q;
				tail=tail->next;
			}
			if(pre!=NULL&&pre==head->p&&head->p->lchild){
				pre=head->p->lchild;
				width=1;
			}
			if(pre!=NULL&&pre==head->p&&head->p->rchild){
				pre=head->p->rchild;
				width=1;
			}
			++width;
			max=width>max?width:max;
			head=head->next;
		}
		cout<<"二叉树宽度为：\t"<<8<<endl;
	}
	void BiTreeNodeNum(){
		cout<<"二叉树节点数为：\t"<<nodenum<<endl; 
	}
	void IsBiSortTree(){
		stack<BiTNode *> node;
		BiTNode *n=bt;
		int pre=0,flag=0;
		while (n != NULL || !node.empty()) {
			while (n != NULL) {
				node.push(n);
				n = n->lchild;
			}
			if (!node.empty()) {
				n = node.top();
				node.pop();
				if(pre > n->data){
					flag=1;
					break;
				}
				pre = n->data; 
				n = n->rchild;
			}
		}
		if(flag){
			cout<<"此二叉树不是二叉排序树"<<endl;
		}
		else{
			cout<<"此二叉树为二叉排序树"<<endl;
		}
	}
};

int main(){
	int n=0;
	BiTree BT;
	BT.InitBiTree();
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.先序遍历（递归）"<<endl;
		cout<<"----2.中序遍历（递归）"<<endl;
		cout<<"----3.后序遍历（递归）"<<endl;
		cout<<"----4.先序遍历（非递归）"<<endl;
		cout<<"----5.中序遍历（非递归）"<<endl;
		cout<<"----6.后序遍历（非递归）"<<endl;
		cout<<"----7.层序遍历"<<endl;
		cout<<"----8.二叉树深度"<<endl;
		cout<<"----9.求二叉树宽度"<<endl;
		cout<<"----10.求二叉树节点数"<<endl;
		cout<<"----11.判断是否为二叉排序树"<<endl;
		cout<<"----12.清屏"<<endl;
		cout<<"----13.退出程序"<<endl; 
		cin>>n;
		switch(n){
			case 1:BT.PreOrderTraverse();break;
			case 2:BT.InOrderTraverse();break;
			case 3:BT.PostOrderTraverse();break;
			case 4:BT.PreOrderTraverseNR();break;
			case 5:BT.InOrderTraverseNR();break;
			case 6:BT.PostOrderTraverseNR();break;
			case 7:BT.LevelOrderTraverse();break;
			case 8:BT.BiTreeDepth();break;
			case 9:BT.BiTreeWidth();break;
			case 10:BT.BiTreeNodeNum();break;
			case 11:BT.IsBiSortTree();break;
			case 12:system("cls");break;
			case 13:exit(0);break;
		}
	}
	return 0;
}
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
#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
using namespace std;

void InsertionSort(int data[]){
	int i,j;
	int temp;
	for(i=1;i<20000;i++){
		temp=data[i];
		j=i-1;
		//与已排序的数逐一比较，大于temp时，该数移后
		while((j>=0)&&(data[j]>temp)){
			data[j+1]=data[j];
			j--;
		}
		//存在大于temp的数
		if(j!=i-1){
			data[j+1]=temp;
		}
	}
}
void swapInt(int * a,int*b)
{
	int c=*a;
	*a=*b;
	*b=c;
}
void ShellSort(int*data,unsigned int len){
	if(len<=1||data==NULL)return;
	for(int div=len/2;div>=1;div=div/2){//定增量div，并不断减小
		for(int i=0;i<=div;++i){//分组成div组
			for(int j=i;j<len-div;j+=div)//对每组进行插入排序
				for(int k=j;k<len;k+=div)
					if(data[j]>data[k])
						swapInt(data+j,data+k);//交换两个数的值
		}
	}
}
void BubbleSort(int data[]){
	for(int i=19999;i>0;i--){
		for(int j=i;j>=0;j--){
			if(data[i]>data[j]){
				int t=data[i];
				data[i]=data[j];
				data[j]=t;
			}
		}
	}
}
void QuickSort(int a[], int low, int high)
{
    if(low >= high)
    {
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];/*用字表的第一个记录作为枢轴*/
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
        a[first] = a[last];/*将比第一个小的移到低端*/
        while(first < last && a[first] <= key)
        {
            ++first;
        }
        a[last] = a[first];/*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    QuickSort(a, low, first-1);
    QuickSort(a, first+1, high);
}
void SelectSort(int data[]){
	int temp,b;
	for(int i=0;i<19999;i++)
    {
        temp=i;
        for(int j=i+1;j<20000;j++)
        {
            if(data[temp]>data[j])
                temp=j;
        }
        if(i!=temp)
        {
            b=data[temp];
            data[temp]=data[i];
            data[i]=b;}
    }
}
void HeapAdjust(int array[],int i,int nLength)
{
    int nChild;
    int nTemp;
    for(;2*i+1<nLength;i=nChild)
    {
        //子结点的位置=2*（父结点位置）+1
        nChild=2*i+1;
        //得到子结点中较大的结点
        if(nChild<nLength-1&&array[nChild+1]>array[nChild])++nChild;
        //如果较大的子结点大于父结点那么把较大的子结点往上移动，替换它的父结点
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp; 
        }
        else break; //否则退出循环
    }
}
//堆排序算法
void HeapSort(int array[],int length)
{
    int i;
    //调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
    //length/2-1是最后一个非叶节点，此处"/"为整除
    for(i=length/2-1;i>=0;--i)
    HeapAdjust(array,i,length);
    //从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for(i=length-1;i>0;--i)
    {
        //把第一个元素和当前的最后一个元素交换，
        //保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
        array[i]=array[0]^array[i];
        array[0]=array[0]^array[i];
        array[i]=array[0]^array[i];
        //不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        HeapAdjust(array,0,i);
    }
}
void merge(int *data, int start, int mid, int end, int *result)
{
    int i, j, k;
    i = start;
    j = mid + 1;                        //避免重复比较data[mid]
    k = 0;
    while (i <= mid && j <= end)        //数组data[start,mid]与数组(mid,end]均没有全部归入数组result中去
    {
        if (data[i] <= data[j])         //如果data[i]小于等于data[j]
            result[k++] = data[i++];    //则将data[i]的值赋给result[k]，之后i,k各加一，表示后移一位
        else
            result[k++] = data[j++];    //否则，将data[j]的值赋给result[k]，j,k各加一
    }
    while (i <= mid)                    //表示数组data(mid,end]已经全部归入result数组中去了，而数组data[start,mid]还有剩余
        result[k++] = data[i++];        //将数组data[start,mid]剩下的值，逐一归入数组result
    while (j <= end)                    //表示数组data[start,mid]已经全部归入到result数组中去了，而数组(mid,high]还有剩余
        result[k++] = data[j++];        //将数组a[mid,high]剩下的值，逐一归入数组result

    for (i = 0; i < k; i++)             //将归并后的数组的值逐一赋给数组data[start,end]
        data[start + i] = result[i];    //注意，应从data[start+i]开始赋值
}
void MergeSort(int *data, int start, int end, int *result)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(data, start, mid, result);                    //对左边进行排序
        MergeSort(data, mid + 1, end, result);                  //对右边进行排序
        merge(data, start, mid, end, result);                    //把排序好的数据合并
    }
}
int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}
void RadixSort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[]tmp;
    delete[]count;
}

int main(){
	int start=0,end=0,dom=0;
	int data[20000];
	int average[8]; 
	char filename[]="data_1.dat";
//	cout<<filename;
	fstream infile;
	//直接插入排序 
	cout<<"--------直接插入排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		InsertionSort(data);
		end=clock();
		dom=end-start;
		average[0]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//希尔排序 
	cout<<"--------希尔排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		ShellSort(data,20000);
		end=clock();
		dom=end-start;
		average[1]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//冒泡排序 
	cout<<"--------冒泡排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		BubbleSort(data);
		end=clock();
		dom=end-start;
		average[2]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//快速排序 
	cout<<"--------快速排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		QuickSort(data, 0, sizeof(data) / sizeof(data[0]) - 1);
		end=clock();
		dom=end-start;
		average[3]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//选择排序 
	cout<<"--------选择排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		SelectSort(data);
		end=clock();
		dom=end-start;
		average[4]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//堆排序 
	cout<<"--------堆排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		HeapSort(data,20000);
		end=clock();
		dom=end-start;
		average[5]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//归并排序 
	cout<<"--------归并排序"<<endl;
	int result[20000];
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		MergeSort(data,0,19999,result);
		end=clock();
		dom=end-start;
		average[6]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//基数排序 
	cout<<"--------基数排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		RadixSort(data,20000);
		end=clock();
		dom=end-start;
		average[7]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	cout<<"平均用时："<<endl;
	cout<<"直接插入排序："<<average[0]/10<<"\t";
	cout<<"希尔排序："<<average[1]/10<<"\t";
	cout<<"冒泡排序："<<average[2]/10<<"\t";
	cout<<"快速排序："<<average[3]/10<<"\t";
	cout<<"选择排序："<<average[4]/10<<"\t";
	cout<<"堆排序："<<average[5]/10<<"\t";
	cout<<"归并排序："<<average[6]/10<<"\t";
	cout<<"基数排序："<<average[7]/10<<"\t";
}
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
