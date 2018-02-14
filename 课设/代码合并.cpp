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
	cout<<"���������������������";
	int n=0;
	cin>>n;
	int srec[n][2];
	for(int i=0;i<n;i++){
		srec[i][0]=srec[i][1]=0;
	}
	outfile.write((char*)&n,sizeof(int));
	int flag=0; 
	for(int i=0;i<n;){						//��ֹ��������Ĵ������ظ� 
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
#define CT 1			//����ʱ��ϵ��
#define CP 1			//���书��ϵ��
using namespace std;

int map[100][100];
int rtime;				//��¼��������ԭ��ʱ��
int rpower;				//��¼��������ԭ�㹦��
int *route;				//��¼��������ԭ��·��
int num;				//����������

typedef struct sensor{
	int n;
	int x;
	int y;
}sensor;

class SSS{
private:
	int **sensors;		// x y time power visited 
	int **troute;		// ��ԭ�㵽��˴�������·��
	int **proute;		// ��ԭ�㵽��˴�������·��
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
		cout<<"���ݶ���ɹ�"<<endl;
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
		for(int p=firstadj(n);;p=nextadj(n,p)){			//�Ե�ǰ��������ÿ���ڽӴ�����ִ�еݹ麯��
			if(p==0)break;
			int dist2=abs(sensors[p][0]-sensors[n][0])*abs(sensors[p][0]-sensors[n][0])+abs(sensors[p][1]-sensors[n][1])*abs(sensors[p][1]-sensors[n][1]);
			rtime+=sqrt(dist2)*CT;
			rpower+=dist2*CP;
			for(int i=0;i<num;i++){			//�޸�route
				if(route[i]==n){
					route[i+1]=p;
					break;
				}
			}
			if(rtime<sensors[p][2]){		//�Ƚ�rtime �޸�time��troute
				sensors[p][2]=rtime;
				cptr(p);
			}
			if(rpower<sensors[p][3]){		//�Ƚ�rpower �޸�power��proute
				sensors[p][3]=rpower;
				cppr(p);
			}
			sensors[p][4]=1;				//�޸�visited
			findmin(p);						//�ݹ����
			rtime-=sqrt(dist2)*CT;			//�ָ�rtime
			rpower-=dist2*CP;				//�ָ�rpower
			sensors[p][4]=0;				//�ָ�visited
			for(int j=0;j<num;j++){			//�ָ�route
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
				cout<<i+1<<"�Ŵ���������С����ʱ��Ϊ��"<<sensors[i+1][2]<<"����";
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
				cout<<i+1<<"�Ŵ���������С�����ܺ�Ϊ��"<<sensors[i+1][3]<<"����";
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
		cout<<"����������������ڽӾ���Ϊ�����Ϊ���ݵ��ڽӾ��󣩣�"<<endl;
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
		cout<<"----1.��ʾ����������ʾ��ͼ"<<endl;
		cout<<"----2.�����ʱ��ͨ��"<<endl;
		cout<<"----3.��ƽ��������С����ṹ"<<endl;
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

typedef struct goods{		//��Ʒ 
	int shopnum;
	char goodname[21];
	float price;
	int sales;
	goods *next;
}goods;
typedef struct shop{		//���� 
	int shopnum;
	char shopname[21];
	float creditworthiness;
	goods *goodhead;
	shop *next; 
}shop;
typedef struct qgoods{		//��ѯ��� 
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
	head->goodhead=(goods*)malloc(sizeof(goods));		//������ͷ������⻯���Լ���goodhead 
	head->goodhead->price=0;
	head->goodhead->sales=0;
	head->goodhead->next=NULL;
	head->shopnum=0;
	head->next=NULL;
}
void init(shop *head){		//���ļ��ж�ȡ���ݵ�����
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
		//��ȡһ������ 
		ps=(shop*)malloc(sizeof(shop));
		infile1.read((char*)ps,sizeof(shop));
		ps->goodhead=(goods*)malloc(sizeof(goods));
		ps->goodhead->next=NULL;
		ps->next=NULL;								//���Ǽ�NULL�����ˣ��������� 
		if(ps->shopnum<0||ps->shopnum>2000){
			free(ps);
			break;
		}
		//�����������Ʒ
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
		if(ps->shopnum==1){		//��һ�����������⴦����Ȼ���¶�ȡ�ļ��ᵼ�������ظ� 
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
//		cout<<"û����Ϣ�ɴ�"<<endl;
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
	cout<<"�ļ�ˢ�³ɹ�"<<endl;
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
	//������Ϣ 
	pn->creditworthiness=5;
	while(1){
		cout<<"������������";
		if(flag==0){			//����flag���ʹ��cin.ignore 
			cin.ignore();
		}
		flag=0;
		cin.getline(pn->shopname,20);
		if(searchshopname(head,pn->shopname)){
			cout<<"�������Ѵ���"<<endl;
			flag=1;
			continue;
		}
		else break;
	}
	//��ӵ�����
	int i=0;
	if(head->next==NULL){		//��ӵ�һ������ 
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
	//��Ʒ��Ϣ
	while(1){
		png=(goods*)malloc(sizeof(goods));
		png->next=NULL;
		png->shopnum=i;
		cout<<"������Ʒ����(����0��������)��";
//		cin.ignore();
		cin.getline(png->goodname,20);
		if(searchgoodname(pn,png->goodname)){
			cout<<"���������и���Ʒ"<<endl;
			free(png);
			continue;
		}
		if(strcmp(png->goodname,"0")==0){
			free(png);
			break;
		}
		while(1){
			cout<<"������Ʒ���ۣ�";
			cin>>png->price;
			cin.ignore();
			if(png->price<0){
				cout<<"�������"<<endl;
				continue;
			}
			else break;
		}
		png->sales=0;
		//�����Ʒ
		if(pn->goodhead->next==NULL){		//��ӵ�һ����Ʒ 
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
	cout<<"�������̱�ţ�";
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
		cout<<"�޸�����"<<endl;
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
	cout<<"�������̱�ţ�";
	cin>>n;cin.ignore();
	shop *ps=head->next;
	for(;ps!=NULL;ps=ps->next){
		if(ps->shopnum==n){
			flag=1;
			while(1){
				goods *png=(goods*)malloc(sizeof(goods));
				png->next=NULL;
				png->shopnum=ps->shopnum; 
				cout<<"������Ʒ���ƣ�����0��������";
				cin.getline(png->goodname,20);
				if(searchgoodname(ps,png->goodname)){
					cout<<"���������и���Ʒ"<<endl;
					free(png);
					continue;
				}
				if(strcmp(png->goodname,"0")==0){
					free(png);
					break;
				}
				while(1){
					cout<<"������Ʒ���ۣ�";
					cin>>png->price;
					cin.ignore();
					if(png->price<0){
						cout<<"�������"<<endl;
						continue;
					}
					else break;
				}
				png->sales=0;
				//�����Ʒ
				if(ps->goodhead->next==NULL){		//��ӵ�һ����Ʒ 
					ps->goodhead->next=png;
				}
				else {
					goods *pg=NULL;
					for(pg=ps->goodhead->next;pg->next!=NULL;pg=pg->next);
					pg->next=png;
					cout<<"��ӳɹ�"<<endl; 
				}
			}
		}
	}
	if(flag==0){
		cout<<"û�д�����"<<endl;
		return;
	}
	refreshfile(head);
	return;
}
void deletegood(shop *head){
	int n=0,flag1=0,flag2=0;
	char goodname[21];
	cout<<"�������̱�ţ�";
	cin>>n;cin.ignore();
	cout<<"������Ʒ���ƣ�����0��������";
	cin.getline(goodname,20);
	shop *ps=head->next;
	for(;ps!=NULL;ps=ps->next){
		if(ps->shopnum==n){
			flag1=1;
			for(goods *pg=ps->goodhead;pg->next!=NULL;pg=pg->next){
				if(strcmp(pg->next->goodname,goodname)==0){
					flag2=1;
					pg->next=pg->next->next;
					cout<<"ɾ���ɹ�"<<endl;
				}
			}
		}
	}
	if(flag1==0){
		cout<<"û�д�����"<<endl;
		return;
	}
	if(flag2==0){
		cout<<"û�д���Ʒ"<<endl;
		return;
	}
	refreshfile(head);
	return;
}
void purchase(shop *head){
	int n=0,flag1=0,flag2=0,s=0;
	char goodname[21];
	cout<<"�������̱�ţ�";
	cin>>n;cin.ignore();
	cout<<"������Ʒ���ƣ�����0��������";
	cin.getline(goodname,20);
	shop *ps=head->next;
	for(;ps!=NULL;ps=ps->next){
		if(ps->shopnum==n){
			flag1=1;
			for(goods *pg=ps->goodhead;pg->next!=NULL;pg=pg->next){
				if(strcmp(pg->next->goodname,goodname)==0){
					flag2=1;
					cout<<"���빺��������";
					cin>>s; 
					pg->next->sales+=s;
				}
			}
		}
	}
	if(flag1==0){
		cout<<"û�д�����"<<endl;
		return;
	}
	if(flag2==0){
		cout<<"û�д���Ʒ"<<endl;
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
		cout<<"\t��Ʒ������"<<q->sales<<endl;
		cout<<"\t��Ʒ���ƣ�"<<q->goodname<<endl;
		cout<<"\t��Ʒ�۸�"<<q->price<<endl;
		cout<<"\t������Ϣ��"<<endl;
		cout<<"\t\t���̱�ţ�"<<q->shopnum<<endl;
		for(ps=head->next;ps!=NULL;ps=ps->next){
			if(ps->shopnum==q->shopnum){
				cout<<"\t\t�������ƣ�"<<ps->shopname<<endl;
				cout<<"\t\t���������ȣ�"<<ps->creditworthiness<<endl;
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
	cout<<"������Ʒ���ƣ�";
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
		cout<<"û�в��ҵ�����Ʒ"<<endl;
	}
	showquery(qhead,head);
}
void show(shop *head){
	shop *p=head->next;
	goods *pg=NULL;
	for(;p!=NULL;p=p->next){
		cout<<"-----------------------------------"<<endl;
		cout<<"\t���̱�ţ�\t"<<p->shopnum<<endl;
		cout<<"\t��������\t"<<p->shopname<<endl;
		cout<<"\t�����ȣ�\t"<<p->creditworthiness<<endl;
		cout<<"\t��Ʒ�б�"<<endl;
		for(pg=p->goodhead->next;pg!=NULL;pg=pg->next){
			cout<<"\t\t��Ʒ���ƣ�"<<pg->goodname<<endl;
			cout<<"\t\t��Ʒ���ۣ�"<<pg->price<<endl;
			cout<<"\t\t��Ʒ������"<<pg->sales<<endl;
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
		cout<<"----1.���һ������"<<endl;
		cout<<"----2.ɾ��һ������"<<endl;
		cout<<"----3.���������е���Ʒ"<<endl;
		cout<<"----4.ɾ�������е���Ʒ"<<endl;
		cout<<"----5.��ѯ��Ʒ"<<endl;
		cout<<"----6.������Ʒ"<<endl;
		cout<<"----7.ˢ���ļ���Ϣ"<<endl;
		cout<<"----8.���¶�ȡ�ļ�"<<endl;
		cout<<"----9.��ʾȫ����Ϣ"<<endl;
		cout<<"----10.����"<<endl;
		cout<<"----11.�˳�����"<<endl;
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

int map[20][20];		// 1.ǽ 0.�յ� 2.���� 3.����ͬ 
int record[40];			// 1.�� 2.�� 3.�� 4.��
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
	cout<<"�Թ��������"<<endl;
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
	void CBT(BiTNode* &root){			//ע�������  * &
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
		cout<<"��������ʼ���ɹ�"<<endl;
		return;
	}
	void DestroyBiTree(){
		DBT(bt);cout<<"���������ٳɹ�"<<endl;
	}
	void BiTreeDepth(){
//		if(BiTreeEmpty()){cout<<"������Ϊ�ջ򲻴���"<<endl;return 0;}
		depth=maxdepth=0;		//���֮ǰ��¼ 
		BTD(bt);
		cout<<"���������Ϊ��\t"<<maxdepth<<endl;
	}
	int PreOrderTraverse(){
		POT(bt);
		cout<<"�������"<<endl;
		return 0;
	}
	int InOrderTraverse(){
		IOT(bt);
		cout<<"�������"<<endl;
		return 0;
	}
	int PostOrderTraverse(){
		PostOT(bt);
		cout<<"�������"<<endl;
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
			if(n->rchild==NULL||n->rchild==last){			//�ж��������Ƿ񱻷��ʹ� 
				cout<<n->data<<"\t";
				node.pop();
				last=n;
				n=NULL;				//ע������ 
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
	void BiTreeWidth(){			//����bug 
		int width=1,max=1;
		BiTNode *pre=NULL;
		BTNQ *q=NULL,*head,*tail;
		head=(BTNQ*)malloc(sizeof(BTNQ));
		head->next=NULL;head->p=bt;
		tail=q=head;
		if(bt->lchild==NULL&&bt->rchild==NULL){
			cout<<"�˶�����ֻ��һ���ڵ�"<<endl;
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
		cout<<"���������Ϊ��\t"<<8<<endl;
	}
	void BiTreeNodeNum(){
		cout<<"�������ڵ���Ϊ��\t"<<nodenum<<endl; 
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
			cout<<"�˶��������Ƕ���������"<<endl;
		}
		else{
			cout<<"�˶�����Ϊ����������"<<endl;
		}
	}
};

int main(){
	int n=0;
	BiTree BT;
	BT.InitBiTree();
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.����������ݹ飩"<<endl;
		cout<<"----2.����������ݹ飩"<<endl;
		cout<<"----3.����������ݹ飩"<<endl;
		cout<<"----4.����������ǵݹ飩"<<endl;
		cout<<"----5.����������ǵݹ飩"<<endl;
		cout<<"----6.����������ǵݹ飩"<<endl;
		cout<<"----7.�������"<<endl;
		cout<<"----8.���������"<<endl;
		cout<<"----9.����������"<<endl;
		cout<<"----10.��������ڵ���"<<endl;
		cout<<"----11.�ж��Ƿ�Ϊ����������"<<endl;
		cout<<"----12.����"<<endl;
		cout<<"----13.�˳�����"<<endl; 
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
typedef char** HuffmanCode;			//��̬�洢�����������

void HuffmanCoding(HTNode* &HT,HuffmanCode &HC,int *letters,int n){
	if(n<=1)return;
	int m=2*n-1;
	HT=(HTNode*)malloc(sizeof(HTNode)*(m+1));			//0�ŵ�Ԫδ�� 
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
	for(i=n;i<m;++i){		//������������ 
		//��HT[1..i-1]ѡ��parentΪ0��weight��С�������ڵ㣬����ż�ΪS1��S2
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
	//��Ҷ�ӵ���������ÿ���ַ��Ĺ���������
	HC=(HuffmanCode)malloc((n+1)*sizeof(char*));		//����n���ַ������ͷָ������ 
	char *cd=(char*)malloc(n*sizeof(char));				//���������Ĺ�������
	cd[n-1]='\0';
	for(i=0;i<n;i++){				//����ַ������ 
		int start=n-1;				//���������λ�� 
		int f=HT[i].parent;
		for(int c=i;f!=0;c=f,f=HT[f].parent){	//��Ҷ�ڵ㵽����������� 
			if(HT[f].lchild==c){
				cd[--start]='0';
			}
			else{
				cd[--start]='1';
			}
		}
		HC[i]=(char*)malloc(sizeof(char)*(n-start));	//Ϊ��i���ַ��������ռ�
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
	cout<<"�ַ��������"<<endl;
	return;
}

int main(){
	int letters[52]={0};			//�ַ����ִ��� 
	float rates[52]={0};			//�ַ�����Ƶ�� 
	int sum=0;						//���ַ��� 
	int n=0;						//ʵ�ʳ��ֵ��ַ������� 
	char line[150];					//��ȡһ���ַ�
	char **HC;						//�洢���������� 
	HTNode *HT=NULL;				//���������ڵ����� 
	HC=(char**)malloc(sizeof(char*)*52); 
	fstream infile;
	infile.open("Hamlet.txt",ios::in);
	if(!infile){
		cout<<"file with error"<<endl;
		exit(0); 
	}
	cout<<"ͳ���ַ������У����Ժ򡣡���"<<endl;
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
	HuffmanCoding(HT,HC,letters,52);		//���ɱ���� 
	//�洢����� 
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
	cout<<"������Ѵ洢"<<endl; 
	outfile.close();
	//���ɱ�����
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
	//���ݱ�������ԭ����
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
	cout<<"���»�ԭ���"<<endl;
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
		//�������������һ�Ƚϣ�����tempʱ�������ƺ�
		while((j>=0)&&(data[j]>temp)){
			data[j+1]=data[j];
			j--;
		}
		//���ڴ���temp����
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
	for(int div=len/2;div>=1;div=div/2){//������div�������ϼ�С
		for(int i=0;i<=div;++i){//�����div��
			for(int j=i;j<len-div;j+=div)//��ÿ����в�������
				for(int k=j;k<len;k+=div)
					if(data[j]>data[k])
						swapInt(data+j,data+k);//������������ֵ
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
    int key = a[first];/*���ֱ�ĵ�һ����¼��Ϊ����*/
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
        a[first] = a[last];/*���ȵ�һ��С���Ƶ��Ͷ�*/
        while(first < last && a[first] <= key)
        {
            ++first;
        }
        a[last] = a[first];/*���ȵ�һ������Ƶ��߶�*/
    }
    a[first] = key;/*�����¼��λ*/
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
        //�ӽ���λ��=2*�������λ�ã�+1
        nChild=2*i+1;
        //�õ��ӽ���нϴ�Ľ��
        if(nChild<nLength-1&&array[nChild+1]>array[nChild])++nChild;
        //����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp; 
        }
        else break; //�����˳�ѭ��
    }
}
//�������㷨
void HeapSort(int array[],int length)
{
    int i;
    //�������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ��
    //length/2-1�����һ����Ҷ�ڵ㣬�˴�"/"Ϊ����
    for(i=length/2-1;i>=0;--i)
    HeapAdjust(array,i,length);
    //�����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
    for(i=length-1;i>0;--i)
    {
        //�ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
        //��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
        array[i]=array[0]^array[i];
        array[0]=array[0]^array[i];
        array[i]=array[0]^array[i];
        //������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
        HeapAdjust(array,0,i);
    }
}
void merge(int *data, int start, int mid, int end, int *result)
{
    int i, j, k;
    i = start;
    j = mid + 1;                        //�����ظ��Ƚ�data[mid]
    k = 0;
    while (i <= mid && j <= end)        //����data[start,mid]������(mid,end]��û��ȫ����������result��ȥ
    {
        if (data[i] <= data[j])         //���data[i]С�ڵ���data[j]
            result[k++] = data[i++];    //��data[i]��ֵ����result[k]��֮��i,k����һ����ʾ����һλ
        else
            result[k++] = data[j++];    //���򣬽�data[j]��ֵ����result[k]��j,k����һ
    }
    while (i <= mid)                    //��ʾ����data(mid,end]�Ѿ�ȫ������result������ȥ�ˣ�������data[start,mid]����ʣ��
        result[k++] = data[i++];        //������data[start,mid]ʣ�µ�ֵ����һ��������result
    while (j <= end)                    //��ʾ����data[start,mid]�Ѿ�ȫ�����뵽result������ȥ�ˣ�������(mid,high]����ʣ��
        result[k++] = data[j++];        //������a[mid,high]ʣ�µ�ֵ����һ��������result

    for (i = 0; i < k; i++)             //���鲢��������ֵ��һ��������data[start,end]
        data[start + i] = result[i];    //ע�⣬Ӧ��data[start+i]��ʼ��ֵ
}
void MergeSort(int *data, int start, int end, int *result)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(data, start, mid, result);                    //����߽�������
        MergeSort(data, mid + 1, end, result);                  //���ұ߽�������
        merge(data, start, mid, end, result);                    //������õ����ݺϲ�
    }
}
int maxbit(int data[], int n) //���������������ݵ����λ��
{
    int d = 1; //��������λ��
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
void RadixSort(int data[], int n) //��������
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //������
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //����d������
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //ÿ�η���ǰ��ռ�����
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for(j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
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
	//ֱ�Ӳ������� 
	cout<<"--------ֱ�Ӳ�������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//ϣ������ 
	cout<<"--------ϣ������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//ð������ 
	cout<<"--------ð������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//�������� 
	cout<<"--------��������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//ѡ������ 
	cout<<"--------ѡ������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//������ 
	cout<<"--------������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//�鲢���� 
	cout<<"--------�鲢����"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//�������� 
	cout<<"--------��������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	cout<<"ƽ����ʱ��"<<endl;
	cout<<"ֱ�Ӳ�������"<<average[0]/10<<"\t";
	cout<<"ϣ������"<<average[1]/10<<"\t";
	cout<<"ð������"<<average[2]/10<<"\t";
	cout<<"��������"<<average[3]/10<<"\t";
	cout<<"ѡ������"<<average[4]/10<<"\t";
	cout<<"������"<<average[5]/10<<"\t";
	cout<<"�鲢����"<<average[6]/10<<"\t";
	cout<<"��������"<<average[7]/10<<"\t";
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
