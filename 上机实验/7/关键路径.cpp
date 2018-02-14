#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stack>
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
int ve[MAX_VERTEX_NUM],vl[MAX_VERTEX_NUM];

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
	int locatevex(int vex){			//���ݶ���ֵ���ض����±� 
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)return i;
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
	int firstadjvex(int vex){				//�����򻡵ĵ�һ����ͷ�ڽӶ��� 
		int flag=0,adjvexs[mg.vexnum+1]={0};
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
//			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
//		cout<<"��һ���ڽӶ���Ϊ��"<<adjvexs[0]<<endl;
		return adjvexs[0];
	}
	int nextadjvex(int vex,int adjvex){			//�����򻡵���һ������ͷ�ڽӶ��� 
		int flag=0,adjvexs[mg.vexnum+1]={0};
		for(int j=0;j<MAX_VERTEX_NUM;j++)if(mg.arcs[vex-1][j].adj)vexadd(adjvexs,j+1);
//		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		for(int i=0;i<mg.vexnum;i++){
			if(adjvexs[i]==adjvex&&adjvexs[i+1]){return adjvexs[i+1];}
			else if(adjvexs[i]==adjvex&&!adjvexs[i+1]){return 0;}
		}
	}
	int firstadjtvex(int vex){				//�����򻡵ĵ�һ����ͷ�ڽӶ��� 
		int flag=0,adjvexs[mg.vexnum+1]={0};
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
//		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][vex-1].adj)vexadd(adjvexs,i+1);
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
//		cout<<"��һ���ڽӶ���Ϊ��"<<adjvexs[0]<<endl;
		return adjvexs[0];
	}
	int nextadjtvex(int vex,int adjvex){			//�����򻡵���һ������ͷ�ڽӶ��� 
		int flag=0,adjvexs[mg.vexnum+1]={0};
//		for(int j=0;j<MAX_VERTEX_NUM;j++)if(mg.arcs[vex-1][j].adj)vexadd(adjvexs,j+1);
		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][vex-1].adj)vexadd(adjvexs,i+1);
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		for(int i=0;i<mg.vexnum;i++){
			if(adjvexs[i]==adjvex&&adjvexs[i+1]){return adjvexs[i+1];}
			else if(adjvexs[i]==adjvex&&!adjvexs[i+1]){return 0;}
		}
	}
	void FindIndegree(int indegree[]){
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			if(mg.vexs[i]){
				int count=0;
				for(int j=0;j<MAX_VERTEX_NUM;j++)if(mg.arcs[j][mg.vexs[i]-1].adj)count++;
				indegree[i]=count;
//				cout<<count<<"\t";
			}
		}
	}
	void FindOutdegree(int outdegree[]){
		for(int i=0;i<MAX_VERTEX_NUM;i++){
			if(mg.vexs[i]){
				int count=0;
				for(int j=0;j<MAX_VERTEX_NUM;j++)if(mg.arcs[mg.vexs[i]-1][j].adj)count++;
				outdegree[i]=count;
//				cout<<count<<"\t";
			}
		}
	}
	int TopologicalOrder(){
		int indegree[mg.vexnum+1];
		FindIndegree(indegree);
		for(int i=0;i<MAX_VERTEX_NUM;i++){ve[i]=vl[i]=0;}
//		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.vexs[i])cout<<indegree[i]<<"\t"; 
		stack<int> S;
		for(int i=0;i<mg.vexnum;i++){
			if(!indegree[i])S.push(i);		//0��ȶ�����ջ 
		}
		int count=0;						//����������
		while(!S.empty()){
			int i=S.top();S.pop();
//			cout<<mg.vexs[i]<<"\t";
			++count;
			for(int p=firstadjvex(mg.vexs[i]);p>0&&p<21;p=nextadjvex(mg.vexs[i],p)){
				int k=locatevex(p);
				if(!(--indegree[k]))S.push(k);	//��0��ȶ����ÿ���ڽӶ�����ȼ�һ������ȼ�Ϊ0����ջ
				if((ve[locatevex(mg.vexs[i])]+mg.arcs[mg.vexs[i]-1][p-1].adj)>ve[k]){		//��ve���鸳ֵ 
					ve[k]=ve[locatevex(mg.vexs[i])]+mg.arcs[mg.vexs[i]-1][p-1].adj;
				}
			}
		}
		if(count<mg.vexnum){cout<<"��ͼ���ڻ�·������������Ч���޷���ؼ�·��"<<endl;return 0;}
		else {return 1;}
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
		CreateDN();
	}
	void CriticalPath(){
		int latest=0,n=0,count=0;
		if(!TopologicalOrder())return;
//		for(int i=0;i<mg.vexnum;i++)cout<<ve[i]<<"\t";cout<<endl;
		for(int i=0;i<mg.vexnum;i++){latest=latest<ve[i]?ve[i]:latest;if(latest==ve[i])n=i;}
		stack<int> S;
		S.push(n);
		for(int i=0;i<mg.vexnum;i++)vl[i]=latest;
//		for(int i=0;i<mg.vexnum;i++)cout<<vl[i]<<"\t";cout<<endl;
		int outdegree[mg.vexnum+1];
		FindOutdegree(outdegree);
		while(!S.empty()){				//����������������vl���� 
			int i=S.top();S.pop();
			++count;
			for(int p=firstadjtvex(mg.vexs[i]);p>0&&p<21;p=nextadjtvex(mg.vexs[i],p)){
				int k=locatevex(p);
				if(!(--outdegree[k]))S.push(k);	//��0���ȶ����ÿ���ڽӶ�����ȼ�һ�������ȼ�Ϊ0����ջ
				if((vl[locatevex(mg.vexs[i])]-mg.arcs[p-1][mg.vexs[i]-1].adj)<vl[k]){		//��vl���鸳ֵ 
					vl[k]=vl[locatevex(mg.vexs[i])]-mg.arcs[p-1][mg.vexs[i]-1].adj;
				}
			}
		}
		if(count<mg.vexnum){cout<<"��ͼ���ڻ�·������������Ч���޷���ؼ�·��"<<endl;}
//		for(int i=0;i<mg.vexnum;i++)cout<<ve[i]<<"\t";cout<<endl;
//		for(int i=0;i<mg.vexnum;i++)cout<<vl[i]<<"\t";cout<<endl;
//		����������������ؼ�����ɵĹؼ�·�� 
		int indegree[mg.vexnum+1];
		for(int i=0;i<MAX_VERTEX_NUM;i++)visited[i]=0;
		FindIndegree(indegree);
		for(int i=0;i<mg.vexnum;i++){
			if(!indegree[i])S.push(i);		//0��ȶ�����ջ 
		}
		count=0;
		cout<<"�ؼ�·��Ϊ��\t";
		while(!S.empty()){
			int i=S.top();S.pop();
//			cout<<mg.vexs[i]<<"\t";
			++count;
			for(int p=firstadjvex(mg.vexs[i]);p>=0&&p<21;p=nextadjvex(mg.vexs[i],p)){
				int k=locatevex(p);
				if(!(--indegree[k]))S.push(k);	//��0��ȶ����ÿ���ڽӶ�����ȼ�һ������ȼ�Ϊ0����ջ
				if(ve[locatevex(mg.vexs[i])]==vl[locatevex(mg.vexs[i])]&&!visited[locatevex(mg.vexs[i])]){
					cout<<mg.vexs[locatevex(mg.vexs[i])]<<"->";
					visited[locatevex(mg.vexs[i])]=1;
				}
				if(k<0||k>=mg.vexnum)break;
			}
		}cout<<endl;
		if(count<mg.vexnum){cout<<"��ͼ���ڻ�·������������Ч���޷���ؼ�·��"<<endl;}
	}
};

int main(){
	int n=0;
	Graph G;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.��������ͼ"<<endl;
		cout<<"----2.�ؼ�·��"<<endl;
		cout<<"----3.��ʾͼ����ϸ��Ϣ"<<endl;
		cin>>n;
		switch(n){
			case 1:G.CreateGraph();break;
			case 2:G.CriticalPath();break;
			case 3:G.show();break;
		}
	}
}
