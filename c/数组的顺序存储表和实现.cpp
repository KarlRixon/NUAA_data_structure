#include<stdlib.h>
#include<stdio.h>
#include<iostream> 
using namespace std;

typedef struct {
	int *base;			//����Ԫ�ػ�ַ 
	int dim;			//����ά�� 
	int *bounds;		//����ά���ַ 
	int *constants;		//����ӳ����������ַ 
}Array;

void show(Array *arr){
	int dim=arr->dim,sum=1;
	for(int i=0;i<dim;i++)sum*=*(arr->bounds);
	cout<<"����ά�磺"<<endl;for(int i=0;i<dim;i++)cout<<*(arr->bounds+i)<<"\t";cout<<endl;
	cout<<"����ӳ������"<<endl;for(int i=0;i<dim;i++)cout<<*(arr->constants+i)<<"\t";cout<<endl;
	cout<<"����Ԫ�أ�"<<endl;
	for(int i=0;i<sum;i++)cout<<*(arr->base+sum)<<"\t";cout<<endl;		//�д����� 
}
Array *InitArray(Array *arr){
	arr=(Array*)malloc(sizeof(Array));
	int dim=0,n=0,sum=1;
	while(1){
		cout<<"��������ά����";
		cin>>dim;
		if(dim>0){
			arr->dim=dim;
			break;
		}else cout<<"�������"<<endl;
	}
	arr->bounds=(int*)malloc(sizeof(int)*dim);
	arr->constants=(int*)malloc(sizeof(int)*dim);
	for(int i=0;i<dim;i++){
		while(1){
			cout<<"�����"<<i+1<<"ά��Ԫ�ظ�����";
			cin>>n;
			if(n>0){
				*(arr->bounds+i)=n;
				*(arr->constants+i)=sum-1;
				sum*=n;
				break;
			}else cout<<"�������"<<endl;
		}
	}
	//��ӳ�����ĳ���Ci��������constans 		�˴��ص㾫�� 
	*(arr->constants+dim-1)=1;
	for(int i=dim-2;i>=0;i--)*(arr->constants+i)=*(arr->bounds+i+1)*(*(arr->constants+i+1)); 
	//											�˴��ص㾫�� 
	arr->base=(int*)malloc(sizeof(int)*sum);
//	cout<<sum<<endl;
	show(arr);
	return arr;
}
void CalOffset(Array *arr){
	if(arr==NULL){cout<<"���鲻����"<<endl;return;}
	int dim=arr->dim,n=0,m=0,offset=0;
	int *subscript=(int*)malloc(sizeof(int)*dim);
	for(int i=0;i<dim;i++){
		while(1){
			cout<<"����Ԫ�ص�"<<i+1<<"ά�±꣺";
			cin>>m;
			if(m>0&&m<=*(arr->bounds+i)){
				*(subscript+i)=m;
				offset+=*(arr->constants+i)*m;
				break;
			}else cout<<"�������"<<endl;
		}
	}
	cout<<"Ԫ���±�Ϊ����";
	for(int i=0;i<dim;i++)cout<<*(subscript+i)<<" ";
	cout<<"��"<<endl<<"Ԫ����Ե�ַΪ��"<<offset<<endl;
}

int main(){
	Array *arr=NULL;
	int n=0;
	while(1){
		cout<<"ѡ���ܣ�"<<endl;
		cout<<"----1.��ʼ������"<<endl;
		cout<<"----2.��������"<<endl;
		cout<<"----3.�޸�Ԫ��"<<endl;
		cout<<"----4.���±����Ԫ��"<<endl;
		cout<<"----5.�����±����Ԫ���������е����λ��"<<endl;
		cout<<"----6.�������λ�ò���Ԫ��"<<endl;
		cout<<"----7.�������"<<endl;
		cout<<"----8.����"<<endl;
		cin>>n;
		switch(n){
			case 1:arr=InitArray(arr);break;
			case 2:break;
			case 3:break;
			case 4:break;
			case 5:CalOffset(arr);break;
			case 6:break;
			case 7:break;
			case 8:system("cls");break;
			default:break;
		}
	}
}
