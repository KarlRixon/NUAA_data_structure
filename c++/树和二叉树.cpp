#include<iostream>
#include<stdlib.h>
using namespace std;

typedef int SqBiTree[100];		//0�ŵ�Ԫ�洢���ڵ� 

typedef struct BiTNode{
	int data;
	BiTNode *lchild,*rchild;
}BiTNode;

//���������� 
typedef enum PointerTag{Link,Thread};
typedef struct BiThrNode{
	int data;
	BiThrNode *lchild,*rchild;
	PointerTag LTag,RTag;
}BiThrNode;

//˫�ױ�洢��ʾ 
typedef struct PTNode{
	int data;
	int parent; 
}PTNode;
typedef struct PTree{
	PTNode nodes[100];
	int r,n;			//���ڵ�λ�úͽڵ��� 
}PTree;

//��������洢 
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
	int n,r;			//�ڵ����͸���λ�� 
}CTree;

//�����ֵܶ�����
typedef struct CSNode{
	int data;
	CSNode *firstchild,*nextsibling;
}CSNode;

//��������
typedef struct HTNode{
	int weight;
	int parent,lchild,rchild;
}HTNode;
typedef char **HuffmanCode;

int main(){
	
}
