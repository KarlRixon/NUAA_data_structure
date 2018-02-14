#include<iostream>
#include<stdlib.h>
using namespace std;

//图的邻接矩阵表示 
typedef enum {DG,DN,UDG,UDN}GraphKind;		//有向图，有向网，无向图，无向网
typedef struct ArcCell{
	int adj;		//顶点关系类型 0、1、权值 
}ArcCell,AdjMatrix[20][20];
typedef struct MGraph{
	int vexs[20];	//顶点向量
	AdjMatrix arcs;	//邻接矩阵
	int vexnum,arcnum;
	GraphKind kind; 
}MGraph;

//图的邻接表存储表示
typedef struct ArcNode{
	int adjvex;			//该弧指向的顶点的位置
	ArcNode *nextarc; 
	char *info;
}ArcNode;
typedef struct VNode{
	int data;
	ArcNode *firstarc;
}VNode,AdjList[20];
typedef struct ALGraph{
	AdjList vertices;
	int vexnum,arcnum;
	int kind;
}ALGraph;

//有向图的十字链表存储表示
typedef struct ArcBox{
	int tailvex,headvex;	//该弧的尾和头顶点的位置 
	ArcBox *hlink,*tlink;	//弧头相同和弧尾相同的弧的链域
	char *info;				//该弧相关信息的指针 
}ArcBox;
typedef struct VexNode{
	int data;
	ArcBox *firstin,*firstout;	//分别指向该顶点第一条入弧和出弧 
}VexNode;
typedef struct OLGraph{
	VexNode xlist[20];
	int vexnum,arcnum;
}OLGraph;

int main(){
	
} 
