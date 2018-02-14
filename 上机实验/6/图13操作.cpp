#include<iostream>
#include<stdlib.h>
#include<queue>
#include<windows.h>
using namespace std;
#define INFINITY INT_MAX		//���ֵ 
#define MAX_VERTEX_NUM 20		//��󶥵���� 
typedef enum {DG,UDG,DN,UDN} GraphKind;		//����ͼ ������ ����ͼ ������
typedef struct ArcCell{
	int adj;					//�����ϵ ��ȨͼΪ1��0 ��ȨͼΪȨֵ 
//	InfoType *info;					//�û������Ϣָ�� 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	int vexs[MAX_VERTEX_NUM+1];	//��������
	AdjMatrix arcs;				//�ڽӾ���
	int vexnum,arcnum;			//ͼ�ĵ�ǰ�������ͻ���
	GraphKind kind;				//ͼ������ 
}MGraph;
int visited[MAX_VERTEX_NUM];

class Graph{
private:
	MGraph mg;
	void addvex(int n){					//��ӽڵ� 
		int flag=0;
		for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++){
			if(mg.vexs[i]==n){flag=1;break;}
		}
		if(!flag){mg.vexs[mg.vexnum]=n;mg.vexnum++;}
	}
	void deletevex(int n){
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			if(mg.vexs[i]==n){
				mg.vexs[i]=0;
				for(int j=i;j<MAX_VERTEX_NUM&&mg.vexs[j+1];j++){
					int t=mg.vexs[j];
					mg.vexs[j]=mg.vexs[j+1];
					mg.vexs[j+1]=t;
				}
			}
		}
	}
	void CreateDG(){
		int head=0,tail=0;
		mg.kind=DG;
		mg.arcnum=mg.vexnum=0;
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			for(int j=0;j<MAX_VERTEX_NUM;j++){
				mg.arcs[i][j].adj=0;
			}
		}
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			mg.vexs[i]=0;
		}
		while(1){
			cout<<"�������򻡣����� '1 2' ��˼��1->2������ '0 0' ��������";
			cin>>tail>>head;
			if(head==0&&tail==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"�������"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=1;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"�����ɹ�"<<endl;
		show(); 
	}
	void CreateUDG(){
		int head=0,tail=0;
		mg.kind=UDG;
		mg.arcnum=mg.vexnum=0;
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			for(int j=0;j<MAX_VERTEX_NUM;j++){
				mg.arcs[i][j].adj=0;
			}
		}
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			mg.vexs[i]=0;
		}
		while(1){
			cout<<"���뻡������ '1 2' ��˼��1--2������ '0 0' ��������";
			cin>>tail>>head;
			if(head==0&&tail==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"�������"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=1;
				mg.arcs[head-1][tail-1].adj=1;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"�����ɹ�"<<endl;
		show();
	}
	void CreateDN(){
		int head=0,tail=0,adj=0;
		mg.kind=DN;
		mg.arcnum=mg.vexnum=0;
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			for(int j=0;j<MAX_VERTEX_NUM;j++){
				mg.arcs[i][j].adj=0;
			}
		}
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			mg.vexs[i]=0;
		}
		while(1){
			cout<<"���뻡��Ȩֵ������ '1 2 3' ��˼��1--2 ȨֵΪ3������ '0 0 0' ��������";
			cin>>tail>>head>>adj;
			if(head==0&&tail==0&&adj==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM||adj<1){cout<<"�������"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=adj;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"�����ɹ�"<<endl;
		show();
	}
	void CreateUDN(){
		int head=0,tail=0,adj=0;
		mg.kind=UDN;
		mg.arcnum=mg.vexnum=0;
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			for(int j=0;j<MAX_VERTEX_NUM;j++){
				mg.arcs[i][j].adj=0;
			}
		}
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			mg.vexs[i]=0;
		}
		while(1){
			cout<<"���뻡��Ȩֵ������ '1 2 3' ��˼��1--2 ȨֵΪ3������ '0 0 0' ��������";
			cin>>tail>>head>>adj;
			if(head==0&&tail==0&&adj==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM||adj<1){cout<<"�������"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=adj;
				mg.arcs[head-1][tail-1].adj=adj;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"�����ɹ�"<<endl;
		show();
	}
	int locatevex(int vex){
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)return i;
	}
	int firstadjvex(int vex){
		int flag=0,adjvexs[mg.vexnum+1]={0};
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
//		cout<<"��һ���ڽӶ���Ϊ��"<<adjvexs[0]<<endl;
		return adjvexs[0];
	}
	int nextadjvex(int vex,int adjvex){
		int flag=0,adjvexs[mg.vexnum+1]={0};
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		for(int i=0;i<mg.vexnum;i++){
			if(adjvexs[i]==adjvex&&adjvexs[i+1]){return adjvexs[i+1];}
			else if(adjvexs[i]==adjvex&&!adjvexs[i+1]){return 0;}
		}
	}
	void DFS(int v){
		visited[v]=1;
		cout<<mg.vexs[v]<<"\t";
		for(int w=firstadjvex(mg.vexs[v]);w>=0&&nextadjvex(mg.vexs[v],w);w=nextadjvex(mg.vexs[v],w)){
			if(!visited[locatevex(w)])DFS(locatevex(w));
		}
	}
public:
	void show(){						//��ʾͼ����ϸ��Ϣ 
		cout<<"-----------------------------"<<endl;
		cout<<"ͼ������Ϊ��"<<mg.kind<<endl<<"��ǰ��������"<<mg.vexnum<<endl<<"��ǰ������"<<mg.arcnum<<endl;
		cout<<"����������"<<endl;for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++)cout<<mg.vexs[i]<<"\t";
		cout<<endl<<"�ڽӾ���"<<endl;
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			for(int j=0;j<MAX_VERTEX_NUM;j++){
				if(mg.arcs[i][j].adj){
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_RED);
					cout<<mg.arcs[i][j].adj<<" ";
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_RED);
					continue;
				}
				cout<<mg.arcs[i][j].adj<<" ";
			}cout<<endl;
		}
	}
	void CreateGraph(){
//		mg=(MGraph*)malloc(sizeof(MGraph));
		int n=0;
		cout<<"ѡ��ͼ�����ͣ�1.����ͼ2.����ͼ3.������4.����������";
		cin>>n;
		switch(n){
			case 1:CreateDG();break;
			case 2:CreateUDG();break;
			case 3:CreateDN();break;
			case 4:CreateUDN();break;
			default:cout<<"�������"<<endl;
		}
	}
	void DestroyGraph(){
		free(mg.arcs);
		free(mg.vexs);
		mg.arcnum=mg.vexnum=0;
		cout<<"���ٳɹ�"<<endl;
	}
	void LocateVex(){
		int vex=0,flag=0;
		cout<<"���붥��ֵ��"<<endl;
		cin>>vex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			cout<<"�����±�Ϊ��"<<flag<<endl;
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)cout<<"�Դ˶���Ϊβ�Ļ�Ϊ��"<<flag<<"\t"<<i+1;cout<<endl;
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)cout<<"�Դ˶���Ϊͷ�Ļ�Ϊ��"<<i+1<<"\t"<<flag;cout<<endl;
		}else{
			cout<<"û�иö���"<<endl;
		}
	}
	void GetVex(){
		int n=0;
		cout<<"���붥���±꣺";
		cin>>n;
		if(n>0&&n<=mg.vexnum)cout<<"����ֵΪ��"<<mg.vexs[n-1]<<endl;
	}
	void PutVex(){
		int vex=0,nvex=0,flag=0,adj=0;
		cout<<"���붥��ֵ��";
		cin>>vex;
		cout<<"������ֵ��";
		cin>>nvex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex){flag=vex;mg.vexs[i]=nvex;}
		if(flag){
//			cout<<"�����±�Ϊ��"<<flag<<endl;
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj){adj=mg.arcs[flag-1][i].adj;mg.arcs[flag-1][i].adj=0;mg.arcs[nvex-1][i].adj=adj;}
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj){adj=mg.arcs[i][flag-1].adj;mg.arcs[i][flag-1].adj=0;mg.arcs[i][nvex-1].adj=adj;}
			cout<<"��ֵ�ɹ�"<<endl;
		}else{
			cout<<"û�иö���"<<endl;
		}
	}
	void vexadd(int vex[],int n){
		int i=0,flag=0;
		for(i=0;i<mg.vexnum;i++){
			if(vex[i]==n)flag=1;
		}
		if(!flag){
			for(int i=0;i<mg.vexnum;i++)
				if(vex[i]==0){vex[i]=n;break;}
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<vex[i]<<"\t";cout<<endl;
//		cout<<n<<"\t"<<flag<<endl;
	}
	void FirstAdjVex(){
		int vex=0,flag=0,adjvexs[mg.vexnum+1]={0};
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		cout<<"���붥��ֵ��"<<endl;
		cin>>vex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}else{
			cout<<"û�иö���"<<endl;return;
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		cout<<"��һ���ڽӶ���Ϊ��"<<adjvexs[0]<<endl;
	}
	void NextAdjVex(){
		int vex=0,flag=0,adjvexs[mg.vexnum+1]={0},adjvex=0;
		cout<<"���붥��ֵ��"<<endl;
		cin>>vex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}else{
			cout<<"û�иö���"<<endl;return;
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t"; 
		cout<<"����ö����һ���ڽӶ��㣺";
		cin>>adjvex;
		for(int i=0;i<mg.vexnum;i++){
			if(adjvexs[i]==adjvex&&adjvexs[i+1]){cout<<"��һ���ڽӶ���Ϊ��"<<adjvexs[i+1]<<endl;return;}
			else if(adjvexs[i]==adjvex&&!adjvexs[i+1]){cout<<"�Ѿ������һ���ڽӶ���"<<endl;return;}
		}cout<<"û�д��ڽӶ���"<<endl;
	}
	void InsertVex(){
		int vex=0;
		cout<<"�����½ڵ�ֵ��";
		cin>>vex;
		addvex(vex);
		mg.vexnum++;
		cout<<"��ӳɹ�\n����������"<<endl;for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++)cout<<mg.vexs[i]<<"\t";
	}
	void DeleteVex(){
		int vex=0;
		cout<<"����Ҫɾ���ڵ��ֵ��";
		cin>>vex;
		deletevex(vex);
		mg.vexnum--;
		cout<<"��ӳɹ�\n����������"<<endl;for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++)cout<<mg.vexs[i]<<"\t";
		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[vex-1][i].adj){mg.arcs[vex-1][i].adj=0;mg.arcnum--;}
		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][vex-1].adj){mg.arcs[i][vex-1].adj=0;mg.arcnum--;}
	}
	void InsertArc(){
		int head=0,tail=0,adj=0;
		while(1){
			cout<<"���뻡������ '1 2' ��˼��1->2��1--2����";
			cin>>tail>>head;
			cout<<"����Ȩֵ������ͼ������0��1����������Ȩֵ����";
			cin>>adj;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"�������"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=adj; 
				mg.arcnum++;addvex(head);addvex(tail);
				break;
			}
		}
		cout<<"��ӳɹ�"<<endl;
	}
	void DeleteArc(){
		int head=0,tail=0;
		while(1){
			cout<<"����Ҫɾ���Ļ������� '1 2' ��˼��1->2��1--2����";
			cin>>tail>>head;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"�������"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=0;
				mg.arcnum--;
				break;
			}
		}
		cout<<"ɾ���ɹ�"<<endl;
	}
	void DFSTraverse(){
		for(int i=0;i<MAX_VERTEX_NUM;i++)visited[i]=0;
		for(int i=0;i<mg.vexnum;i++){
			if(!visited[i])DFS(i);
		}
		cout<<endl;
	}
	void BFSTraverse(){
		for(int i=0;i<MAX_VERTEX_NUM;i++)visited[i]=0;
		queue<int> vexq;
		for(int i=0;i<mg.vexnum;i++){
			if(!visited[i]){
				visited[i]=1;
				cout<<mg.vexs[i]<<"\t";
				vexq.push(i);
				while(!vexq.empty()){
					int u=vexq.front();
					vexq.pop();
					for(int w=firstadjvex(mg.vexs[u]);w>=0&&nextadjvex(mg.vexs[u],w);w=nextadjvex(mg.vexs[u],w)){
						if(!visited[locatevex(w)]){
							visited[locatevex(w)]=1;
							cout<<w<<"\t";
							vexq.push(locatevex(w));
						}
					}
				}
			}
		}
		
		
		cout<<endl;
	}
};

int main(){
	int n=0;
	Graph G;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.����ͼ"<<endl;
		cout<<"----2.����ͼ"<<endl;
		cout<<"----3.���ض���λ��"<<endl;
		cout<<"----4.���ض���ֵ"<<endl;
		cout<<"----5.�����㸳ֵ"<<endl;
		cout<<"----6.���ض���ĵ�һ���ڽӶ���"<<endl;
		cout<<"----7.���ض��������һ���ڽӶ������һ���ڽӶ���"<<endl;
		cout<<"----8.�����¶���"<<endl;
		cout<<"----9.ɾ�����㼰��ػ�"<<endl;
		cout<<"----10.����"<<endl;
		cout<<"----11.ɾ����"<<endl;
		cout<<"----12.������ȱ���"<<endl;
		cout<<"----13.������ȱ���"<<endl;
		cout<<"----14.��ʾͼ����ϸ��Ϣ"<<endl;
		cin>>n;
		switch(n){
			case 1:G.CreateGraph();break;
			case 2:G.DestroyGraph();break;
			case 3:G.LocateVex();break;
			case 4:G.GetVex();break;
			case 5:G.PutVex();break;
			case 6:G.FirstAdjVex();break;
			case 7:G.NextAdjVex();break;
			case 8:G.InsertVex();break;
			case 9:G.DeleteVex();break;
			case 10:G.InsertArc();break;
			case 11:G.DeleteArc();break;
			case 12:G.DFSTraverse();break;
			case 13:G.BFSTraverse();break;
			case 14:G.show();break;
		}
	} 
}
