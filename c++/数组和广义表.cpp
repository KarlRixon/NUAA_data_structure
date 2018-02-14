#include<iostream>
#include<stdlib.h>
using namespace std; 

typedef struct Array{
	int *base;		//数组元素基址
	int dim;		//数组维数
	int *bounds;	//数组维界基址
	int *constants;	//数组映像函数常量基址 
}Array;

typedef struct Triple{
	int i,j;			//非零元行下标、列下标 
	int e;
}Triple;
typedef struct TSMatrix{
	Triple data[1001];	//非零元三元组表，data[0]未用
	int mu,nu,tu;		//矩阵行数、列数、非零元个数 
}TSMatrix;

typedef struct OLNode{
	int i,j;
	int e;
	OLNode *right,*down;		//该非零元所在行表和列表的后继链域 
}OLNode;
typedef struct CrossList{
	OLNode **rhead,**chead;		//行和列链表头指针向量基址 
	int mu,nu,tu;
}CrossList;

typedef enum{ATOM,LIST}ElemTag;
typedef struct GLNode{
	ElemTag tag;				//公共部分，区分原子节点和表节点 
	union {						//原子节点与表节点的联合部分 
		int atom;
		struct{struct GLNode *hp,*tp;}ptr;		//hp表头 tp表尾 
	};
}GList;

int main(){
//	GList *a;
//	a=(GList*)malloc(sizeof(GList));
}
