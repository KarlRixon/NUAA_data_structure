#include<iostream>
#include<stdlib.h>
using namespace std;

//ͼ���ڽӾ����ʾ 
typedef enum {DG,DN,UDG,UDN}GraphKind;		//����ͼ��������������ͼ��������
typedef struct ArcCell{
	int adj;		//�����ϵ���� 0��1��Ȩֵ 
}ArcCell,AdjMatrix[20][20];
typedef struct MGraph{
	int vexs[20];	//��������
	AdjMatrix arcs;	//�ڽӾ���
	int vexnum,arcnum;
	GraphKind kind; 
}MGraph;

//ͼ���ڽӱ�洢��ʾ
typedef struct ArcNode{
	int adjvex;			//�û�ָ��Ķ����λ��
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

//����ͼ��ʮ������洢��ʾ
typedef struct ArcBox{
	int tailvex,headvex;	//�û���β��ͷ�����λ�� 
	ArcBox *hlink,*tlink;	//��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
	char *info;				//�û������Ϣ��ָ�� 
}ArcBox;
typedef struct VexNode{
	int data;
	ArcBox *firstin,*firstout;	//�ֱ�ָ��ö����һ���뻡�ͳ��� 
}VexNode;
typedef struct OLGraph{
	VexNode xlist[20];
	int vexnum,arcnum;
}OLGraph;

int main(){
	
} 
