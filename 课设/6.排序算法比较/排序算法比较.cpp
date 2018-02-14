#include<iostream>
#include<fstream>
#include<time.h>
#include<stdlib.h>
using namespace std;

void InsertionSort(int data[]){
	int i,j;
	int temp;
	for(i=1;i<20000;i++){
		temp=data[i];
		j=i-1;
		//与已排序的数逐一比较，大于temp时，该数移后
		while((j>=0)&&(data[j]>temp)){
			data[j+1]=data[j];
			j--;
		}
		//存在大于temp的数
		if(j!=i-1){
			data[j+1]=temp;
		}
	}
}
void swapInt(int * a,int*b)
{
	int c=*a;
	*a=*b;
	*b=c;
}
void ShellSort(int*data,unsigned int len){
	if(len<=1||data==NULL)return;
	for(int div=len/2;div>=1;div=div/2){//定增量div，并不断减小
		for(int i=0;i<=div;++i){//分组成div组
			for(int j=i;j<len-div;j+=div)//对每组进行插入排序
				for(int k=j;k<len;k+=div)
					if(data[j]>data[k])
						swapInt(data+j,data+k);//交换两个数的值
		}
	}
}
void BubbleSort(int data[]){
	for(int i=19999;i>0;i--){
		for(int j=i;j>=0;j--){
			if(data[i]>data[j]){
				int t=data[i];
				data[i]=data[j];
				data[j]=t;
			}
		}
	}
}
void QuickSort(int a[], int low, int high)
{
    if(low >= high)
    {
        return;
    }
    int first = low;
    int last = high;
    int key = a[first];/*用字表的第一个记录作为枢轴*/
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
        a[first] = a[last];/*将比第一个小的移到低端*/
        while(first < last && a[first] <= key)
        {
            ++first;
        }
        a[last] = a[first];/*将比第一个大的移到高端*/
    }
    a[first] = key;/*枢轴记录到位*/
    QuickSort(a, low, first-1);
    QuickSort(a, first+1, high);
}
void SelectSort(int data[]){
	int temp,b;
	for(int i=0;i<19999;i++)
    {
        temp=i;
        for(int j=i+1;j<20000;j++)
        {
            if(data[temp]>data[j])
                temp=j;
        }
        if(i!=temp)
        {
            b=data[temp];
            data[temp]=data[i];
            data[i]=b;}
    }
}
void HeapAdjust(int array[],int i,int nLength)
{
    int nChild;
    int nTemp;
    for(;2*i+1<nLength;i=nChild)
    {
        //子结点的位置=2*（父结点位置）+1
        nChild=2*i+1;
        //得到子结点中较大的结点
        if(nChild<nLength-1&&array[nChild+1]>array[nChild])++nChild;
        //如果较大的子结点大于父结点那么把较大的子结点往上移动，替换它的父结点
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp; 
        }
        else break; //否则退出循环
    }
}
//堆排序算法
void HeapSort(int array[],int length)
{
    int i;
    //调整序列的前半部分元素，调整完之后第一个元素是序列的最大的元素
    //length/2-1是最后一个非叶节点，此处"/"为整除
    for(i=length/2-1;i>=0;--i)
    HeapAdjust(array,i,length);
    //从最后一个元素开始对序列进行调整，不断的缩小调整的范围直到第一个元素
    for(i=length-1;i>0;--i)
    {
        //把第一个元素和当前的最后一个元素交换，
        //保证当前的最后一个位置的元素都是在现在的这个序列之中最大的
        array[i]=array[0]^array[i];
        array[0]=array[0]^array[i];
        array[i]=array[0]^array[i];
        //不断缩小调整heap的范围，每一次调整完毕保证第一个元素是当前序列的最大值
        HeapAdjust(array,0,i);
    }
}
void merge(int *data, int start, int mid, int end, int *result)
{
    int i, j, k;
    i = start;
    j = mid + 1;                        //避免重复比较data[mid]
    k = 0;
    while (i <= mid && j <= end)        //数组data[start,mid]与数组(mid,end]均没有全部归入数组result中去
    {
        if (data[i] <= data[j])         //如果data[i]小于等于data[j]
            result[k++] = data[i++];    //则将data[i]的值赋给result[k]，之后i,k各加一，表示后移一位
        else
            result[k++] = data[j++];    //否则，将data[j]的值赋给result[k]，j,k各加一
    }
    while (i <= mid)                    //表示数组data(mid,end]已经全部归入result数组中去了，而数组data[start,mid]还有剩余
        result[k++] = data[i++];        //将数组data[start,mid]剩下的值，逐一归入数组result
    while (j <= end)                    //表示数组data[start,mid]已经全部归入到result数组中去了，而数组(mid,high]还有剩余
        result[k++] = data[j++];        //将数组a[mid,high]剩下的值，逐一归入数组result

    for (i = 0; i < k; i++)             //将归并后的数组的值逐一赋给数组data[start,end]
        data[start + i] = result[i];    //注意，应从data[start+i]开始赋值
}
void MergeSort(int *data, int start, int end, int *result)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(data, start, mid, result);                    //对左边进行排序
        MergeSort(data, mid + 1, end, result);                  //对右边进行排序
        merge(data, start, mid, end, result);                    //把排序好的数据合并
    }
}
int maxbit(int data[], int n) //辅助函数，求数据的最大位数
{
    int d = 1; //保存最大的位数
    int p = 10;
    for(int i = 0; i < n; ++i)
    {
        while(data[i] >= p)
        {
            p *= 10;
            ++d;
        }
    }
    return d;
}
void RadixSort(int data[], int n) //基数排序
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //计数器
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //进行d次排序
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //每次分配前清空计数器
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //统计每个桶中的记录数
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //将tmp中的位置依次分配给每个桶
        for(j = n - 1; j >= 0; j--) //将所有桶中记录依次收集到tmp中
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //将临时数组的内容复制到data中
            data[j] = tmp[j];
        radix = radix * 10;
    }
    delete[]tmp;
    delete[]count;
}

int main(){
	int start=0,end=0,dom=0;
	int data[20000];
	int average[8]; 
	char filename[]="data_1.dat";
//	cout<<filename;
	fstream infile;
	//直接插入排序 
	cout<<"--------直接插入排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		InsertionSort(data);
		end=clock();
		dom=end-start;
		average[0]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//希尔排序 
	cout<<"--------希尔排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		ShellSort(data,20000);
		end=clock();
		dom=end-start;
		average[1]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//冒泡排序 
	cout<<"--------冒泡排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		BubbleSort(data);
		end=clock();
		dom=end-start;
		average[2]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//快速排序 
	cout<<"--------快速排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		QuickSort(data, 0, sizeof(data) / sizeof(data[0]) - 1);
		end=clock();
		dom=end-start;
		average[3]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//选择排序 
	cout<<"--------选择排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		SelectSort(data);
		end=clock();
		dom=end-start;
		average[4]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//堆排序 
	cout<<"--------堆排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		HeapSort(data,20000);
		end=clock();
		dom=end-start;
		average[5]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//归并排序 
	cout<<"--------归并排序"<<endl;
	int result[20000];
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		MergeSort(data,0,19999,result);
		end=clock();
		dom=end-start;
		average[6]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//基数排序 
	cout<<"--------基数排序"<<endl;
	for(int i=0;i<10;i++){
		filename[5]=i+48;
		infile.open(filename,ios::in|ios::binary);
		if(!infile){
			cout<<filename<<" with error"<<endl;
			exit(0);
		}
		for(int j=0;j<20000;j++){
			infile.read((char*)&data[j],sizeof(int));
		}
		start=clock();
		dom=0;
		RadixSort(data,20000);
		end=clock();
		dom=end-start;
		average[7]+=dom;
		cout<<"样本"<<i<<"用时："<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	cout<<"平均用时："<<endl;
	cout<<"直接插入排序："<<average[0]/10<<"\t";
	cout<<"希尔排序："<<average[1]/10<<"\t";
	cout<<"冒泡排序："<<average[2]/10<<"\t";
	cout<<"快速排序："<<average[3]/10<<"\t";
	cout<<"选择排序："<<average[4]/10<<"\t";
	cout<<"堆排序："<<average[5]/10<<"\t";
	cout<<"归并排序："<<average[6]/10<<"\t";
	cout<<"基数排序："<<average[7]/10<<"\t";
}
