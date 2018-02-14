#include<iostream>
#include<stdlib.h>
using namespace std; 

typedef struct Array{
	int *base;		//����Ԫ�ػ�ַ
	int dim;		//����ά��
	int *bounds;	//����ά���ַ
	int *constants;	//����ӳ����������ַ 
}Array;

typedef struct Triple{
	int i,j;			//����Ԫ���±ꡢ���±� 
	int e;
}Triple;
typedef struct TSMatrix{
	Triple data[1001];	//����Ԫ��Ԫ���data[0]δ��
	int mu,nu,tu;		//��������������������Ԫ���� 
}TSMatrix;

typedef struct OLNode{
	int i,j;
	int e;
	OLNode *right,*down;		//�÷���Ԫ�����б���б�ĺ������ 
}OLNode;
typedef struct CrossList{
	OLNode **rhead,**chead;		//�к�������ͷָ��������ַ 
	int mu,nu,tu;
}CrossList;

typedef enum{ATOM,LIST}ElemTag;
typedef struct GLNode{
	ElemTag tag;				//�������֣�����ԭ�ӽڵ�ͱ�ڵ� 
	union {						//ԭ�ӽڵ����ڵ�����ϲ��� 
		int atom;
		struct{struct GLNode *hp,*tp;}ptr;		//hp��ͷ tp��β 
	};
}GList;

int main(){
//	GList *a;
//	a=(GList*)malloc(sizeof(GList));
}
