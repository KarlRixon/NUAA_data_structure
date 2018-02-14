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
