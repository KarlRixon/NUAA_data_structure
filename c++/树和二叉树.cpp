#include<iostream>
#include<stdlib.h>
using namespace std;

typedef int SqBiTree[100];		//0号单元存储根节点 

typedef struct BiTNode{
	int data;
	BiTNode *lchild,*rchild;
}BiTNode;

//线索二叉树 
typedef enum PointerTag{Link,Thread};
typedef struct BiThrNode{
	int data;
	BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode;

//双亲表存储表示 
typedef struct PTNode{
	int data;
	int parent; 
}PTNode;
typedef struct PTree{
	PTNode nodes[100];
	int r,n;			//根节点位置和节点数 
}PTree;

//孩子链表存储 
typedef struct CTNode{
	int child;
	CTNode *next;
}CTNode;
typedef struct CTBox{
	int data;
	CTNode *firstchild;
}CTBox;
typedef struct CTree{
	CTBox nodes[100];
	int n,r;			//节点数和根的位置 
}CTree;

//孩子兄弟二叉树
typedef struct CSNode{
	int data;
	CSNode *firstchild,*nextsibling;
}CSNode;

//哈夫曼树
typedef struct HTNode{
	int weight;
	int parent,lchild,rchild;
}HTNode;
typedef char **HuffmanCode;

int main(){
	
}
