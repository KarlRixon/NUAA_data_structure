#include<stdlib.h>
#include<stdio.h>
#include<iostream> 
using namespace std;

typedef struct {
	int *base;			//数组元素基址 
	int dim;			//数组维数 
	int *bounds;		//数组维界基址 
	int *constants;		//数组映像函数常量基址 
}Array;

void show(Array *arr){
	int dim=arr->dim,sum=1;
	for(int i=0;i<dim;i++)sum*=*(arr->bounds);
	cout<<"数组维界："<<endl;for(int i=0;i<dim;i++)cout<<*(arr->bounds+i)<<"\t";cout<<endl;
	cout<<"数组映像函数："<<endl;for(int i=0;i<dim;i++)cout<<*(arr->constants+i)<<"\t";cout<<endl;
	cout<<"数组元素："<<endl;
	for(int i=0;i<sum;i++)cout<<*(arr->base+sum)<<"\t";cout<<endl;		//有待改善 
}
Array *InitArray(Array *arr){
	arr=(Array*)malloc(sizeof(Array));
	int dim=0,n=0,sum=1;
	while(1){
		cout<<"输入数组维数：";
		cin>>dim;
		if(dim>0){
			arr->dim=dim;
			break;
		}else cout<<"输入错误"<<endl;
	}
	arr->bounds=(int*)malloc(sizeof(int)*dim);
	arr->constants=(int*)malloc(sizeof(int)*dim);
	for(int i=0;i<dim;i++){
		while(1){
			cout<<"输入第"<<i+1<<"维的元素个数：";
			cin>>n;
			if(n>0){
				*(arr->bounds+i)=n;
				*(arr->constants+i)=sum-1;
				sum*=n;
				break;
			}else cout<<"输入错误"<<endl;
		}
	}
	//求映像函数的常数Ci，并存入constans 		此处重点精华 
	*(arr->constants+dim-1)=1;
	for(int i=dim-2;i>=0;i--)*(arr->constants+i)=*(arr->bounds+i+1)*(*(arr->constants+i+1)); 
	//											此处重点精华 
	arr->base=(int*)malloc(sizeof(int)*sum);
//	cout<<sum<<endl;
	show(arr);
	return arr;
}
void CalOffset(Array *arr){
	if(arr==NULL){cout<<"数组不存在"<<endl;return;}
	int dim=arr->dim,n=0,m=0,offset=0;
	int *subscript=(int*)malloc(sizeof(int)*dim);
	for(int i=0;i<dim;i++){
		while(1){
			cout<<"输入元素第"<<i+1<<"维下标：";
			cin>>m;
			if(m>0&&m<=*(arr->bounds+i)){
				*(subscript+i)=m;
				offset+=*(arr->constants+i)*m;
				break;
			}else cout<<"输入错误"<<endl;
		}
	}
	cout<<"元素下标为：（";
	for(int i=0;i<dim;i++)cout<<*(subscript+i)<<" ";
	cout<<"）"<<endl<<"元素相对地址为："<<offset<<endl;
}

int main(){
	Array *arr=NULL;
	int n=0;
	while(1){
		cout<<"选择功能："<<endl;
		cout<<"----1.初始化数组"<<endl;
		cout<<"----2.销毁数组"<<endl;
		cout<<"----3.修改元素"<<endl;
		cout<<"----4.按下标查找元素"<<endl;
		cout<<"----5.根据下标计算元素在数组中的相对位置"<<endl;
		cout<<"----6.根据相对位置查找元素"<<endl;
		cout<<"----7.输出数组"<<endl;
		cout<<"----8.清屏"<<endl;
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
