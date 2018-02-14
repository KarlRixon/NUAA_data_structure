#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stack>
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
	int locatevex(int vex){			//根据顶点值返回顶点下标 
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
	int firstadjvex(int vex){				//求有向弧的第一个弧头邻接顶点 
		int flag=0,adjvexs[mg.vexnum+1]={0};
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
		for(int i=0;i<mg.vexnum&&mg.vexs[i]!=0;i++)if(mg.vexs[i]==vex)flag=vex;
		if(flag){
			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[flag-1][i].adj)vexadd(adjvexs,i+1);
//			for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
		}
//		for(int i=0;i<mg.vexnum;i++)cout<<adjvexs[i]<<"\t";
//		cout<<"第一个邻接顶点为："<<adjvexs[0]<<endl;
		return adjvexs[0];
	}
	int nextadjvex(int vex,int adjvex){			//求有向弧的下一个个弧头邻接顶点 
		int flag=0,adjvexs[mg.vexnum+1]={0};
		for(int j=0;j<MAX_VERTEX_NUM;j++)if(mg.arcs[vex-1][j].adj)vexadd(adjvexs,j+1);
//		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.arcs[i][flag-1].adj)vexadd(adjvexs,i+1);
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
		CreateDG();
	}
	void TopologicalSort(){
		int indegree[mg.vexnum+1];
		FindIndegree(indegree);
//		for(int i=0;i<MAX_VERTEX_NUM;i++)if(mg.vexs[i])cout<<indegree[i]<<"\t"; 
		stack<int> S;
		for(int i=0;i<mg.vexnum;i++){
			if(!indegree[i])S.push(i);		//0入度顶点入栈 
		}
		int count=0;						//输出顶点计数
		while(!S.empty()){
			int i=S.top();S.pop();
			cout<<mg.vexs[i]<<"\t";++count;
			for(int p=firstadjvex(mg.vexs[i]);p>0&&p<21;p=nextadjvex(mg.vexs[i],p)){
				int k=locatevex(p);
				if(!(--indegree[k]))S.push(k);	//对0入度顶点的每个邻接顶点入度减一，若入度减为0则入栈
			}
		}
		if(count<mg.vexnum)cout<<"此图存在回路，输出的拓扑排序无效"<<endl;
		else cout<<"拓扑排序结束"<<endl;
	}
};

int main(){
	int n=0;
	Graph G;
	while(1){
		cout<<"menu"<<endl;
		cout<<"----1.创建有向图"<<endl;
		cout<<"----2.拓扑排序"<<endl;
		cout<<"----3.显示图的详细信息"<<endl;
		cin>>n;
		switch(n){
			case 1:G.CreateGraph();break;
			case 2:G.TopologicalSort();break;
			case 3:G.show();break;
		}
	} 
}
