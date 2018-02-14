#include<iostream>
#include<stdlib.h>
#include<queue>
#include<windows.h>
using namespace std;
#define INFINITY INT_MAX		//最大值 
#define MAX_VERTEX_NUM 20		//最大顶点个数 
typedef enum {DG,UDG,DN,UDN} GraphKind;		//有向图 有向网 无向图 无向网
typedef struct ArcCell{
	int adj;					//顶点关系 无权图为1或0 有权图为权值 
//	InfoType *info;					//该弧相关信息指针 
}ArcCell,AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];
typedef struct{
	int vexs[MAX_VERTEX_NUM+1];	//顶点向量
	AdjMatrix arcs;				//邻接矩阵
	int vexnum,arcnum;			//图的当前顶点数和弧数
	GraphKind kind;				//图的种类 
}MGraph;
int visited[MAX_VERTEX_NUM];

class Graph{
private:
	MGraph mg;
	void addvex(int n){					//添加节点 
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
			cout<<"输入有向弧（例如 '1 2' 意思是1->2，输入 '0 0' 结束）：";
			cin>>tail>>head;
			if(head==0&&tail==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"输入错误"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=1;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"创建成功"<<endl;
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
			cout<<"输入弧（例如 '1 2' 意思是1--2，输入 '0 0' 结束）：";
			cin>>tail>>head;
			if(head==0&&tail==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"输入错误"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=1;
				mg.arcs[head-1][tail-1].adj=1;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"创建成功"<<endl;
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
			cout<<"输入弧及权值（例如 '1 2 3' 意思是1--2 权值为3，输入 '0 0 0' 结束）：";
			cin>>tail>>head>>adj;
			if(head==0&&tail==0&&adj==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM||adj<1){cout<<"输入错误"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=adj;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"创建成功"<<endl;
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
			cout<<"输入弧及权值（例如 '1 2 3' 意思是1--2 权值为3，输入 '0 0 0' 结束）：";
			cin>>tail>>head>>adj;
			if(head==0&&tail==0&&adj==0)break;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM||adj<1){cout<<"输入错误"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=adj;
				mg.arcs[head-1][tail-1].adj=adj;
				mg.arcnum++;addvex(head);addvex(tail);
			}
		}
		cout<<"创建成功"<<endl;
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
//		cout<<"第一个邻接顶点为："<<adjvexs[0]<<endl;
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
	void show(){						//显示图的详细信息 
		cout<<"-----------------------------"<<endl;
		cout<<"图的种类为："<<mg.kind<<endl<<"当前顶点数："<<mg.vexnum<<endl<<"当前弧数："<<mg.arcnum<<endl;
		cout<<"顶点向量："<<endl;for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++)cout<<mg.vexs[i]<<"\t";
		cout<<endl<<"邻接矩阵："<<endl;
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
		cout<<"选择图的类型（1.有向图2.无向图3.有向网4.无向网）：";
		cin>>n;
		switch(n){
			case 1:CreateDG();break;
			case 2:CreateUDG();break;
			case 3:CreateDN();break;
			case 4:CreateUDN();break;
			default:cout<<"输入错误"<<endl;
		}
	}
	void DestroyGraph(){
		free(mg.arcs);
		free(mg.vexs);
		mg.arcnum=mg.vexnum=0;
		cout<<"销毁成功"<<endl;
	}
	void LocateVex(){
		int vex=0,flag=0;
		cout<<"输入顶点值："<<endl;
		cin>>vex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			cout<<"顶点下标为："<<flag<<endl;
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)cout<<"以此顶点为尾的弧为："<<flag<<"\t"<<i+1;cout<<endl;
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)cout<<"以此顶点为头的弧为："<<i+1<<"\t"<<flag;cout<<endl;
		}else{
			cout<<"没有该顶点"<<endl;
		}
	}
	void GetVex(){
		int n=0;
		cout<<"输入顶点下标：";
		cin>>n;
		if(n>0&&n<=mg.vexnum)cout<<"顶点值为："<<mg.vexs[n-1]<<endl;
	}
	void PutVex(){
		int vex=0,nvex=0,flag=0,adj=0;
		cout<<"输入顶点值：";
		cin>>vex;
		cout<<"输入新值：";
		cin>>nvex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex){flag=vex;mg.vexs[i]=nvex;}
		if(flag){
//			cout<<"顶点下标为："<<flag<<endl;
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj){adj=mg.arcs[flag-1][i].adj;mg.arcs[flag-1][i].adj=0;mg.arcs[nvex-1][i].adj=adj;}
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj){adj=mg.arcs[i][flag-1].adj;mg.arcs[i][flag-1].adj=0;mg.arcs[i][nvex-1].adj=adj;}
			cout<<"赋值成功"<<endl;
		}else{
			cout<<"没有该顶点"<<endl;
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
		cout<<"输入顶点值："<<endl;
		cin>>vex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}else{
			cout<<"没有该顶点"<<endl;return;
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		cout<<"第一个邻接顶点为："<<adjvexs[0]<<endl;
	}
	void NextAdjVex(){
		int vex=0,flag=0,adjvexs[mg.vexnum+1]={0},adjvex=0;
		cout<<"输入顶点值："<<endl;
		cin>>vex;
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}else{
			cout<<"没有该顶点"<<endl;return;
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t"; 
		cout<<"输入该顶点的一个邻接顶点：";
		cin>>adjvex;
		for(int i=0;i<mg.vexnum;i++){
			if(adjvexs[i]==adjvex&&adjvexs[i+1]){cout<<"下一个邻接顶点为："<<adjvexs[i+1]<<endl;return;}
			else if(adjvexs[i]==adjvex&&!adjvexs[i+1]){cout<<"已经是最后一个邻接顶点"<<endl;return;}
		}cout<<"没有此邻接顶点"<<endl;
	}
	void InsertVex(){
		int vex=0;
		cout<<"输入新节点值：";
		cin>>vex;
		addvex(vex);
		mg.vexnum++;
		cout<<"添加成功\n顶点向量："<<endl;for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++)cout<<mg.vexs[i]<<"\t";
	}
	void DeleteVex(){
		int vex=0;
		cout<<"输入要删除节点的值：";
		cin>>vex;
		deletevex(vex);
		mg.vexnum--;
		cout<<"添加成功\n顶点向量："<<endl;for(int i=0;i<MAX_VERTEX_NUM&&mg.vexs[i]!=0;i++)cout<<mg.vexs[i]<<"\t";
		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[vex-1][i].adj){mg.arcs[vex-1][i].adj=0;mg.arcnum--;}
		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][vex-1].adj){mg.arcs[i][vex-1].adj=0;mg.arcnum--;}
	}
	void InsertArc(){
		int head=0,tail=0,adj=0;
		while(1){
			cout<<"输入弧（例如 '1 2' 意思是1->2或1--2）：";
			cin>>tail>>head;
			cout<<"输入权值（若是图则输入0或1，网则输入权值）：";
			cin>>adj;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"输入错误"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=adj; 
				mg.arcnum++;addvex(head);addvex(tail);
				break;
			}
		}
		cout<<"添加成功"<<endl;
	}
	void DeleteArc(){
		int head=0,tail=0;
		while(1){
			cout<<"输入要删除的弧（例如 '1 2' 意思是1->2或1--2）：";
			cin>>tail>>head;
			if(tail<1||tail>MAX_VERTEX_NUM||head<1||head>MAX_VERTEX_NUM){cout<<"输入错误"<<endl;continue;}
			else{
				mg.arcs[tail-1][head-1].adj=0;
				mg.arcnum--;
				break;
			}
		}
		cout<<"删除成功"<<endl;
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
		cout<<"----1.创建图"<<endl;
		cout<<"----2.销毁图"<<endl;
		cout<<"----3.返回顶点位置"<<endl;
		cout<<"----4.返回顶点值"<<endl;
		cout<<"----5.给顶点赋值"<<endl;
		cout<<"----6.返回顶点的第一个邻接顶点"<<endl;
		cout<<"----7.返回顶点相对于一个邻接顶点的下一个邻接顶点"<<endl;
		cout<<"----8.增添新顶点"<<endl;
		cout<<"----9.删除顶点及相关弧"<<endl;
		cout<<"----10.增添弧"<<endl;
		cout<<"----11.删除弧"<<endl;
		cout<<"----12.深度优先遍历"<<endl;
		cout<<"----13.广度优先遍历"<<endl;
		cout<<"----14.显示图的详细信息"<<endl;
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
