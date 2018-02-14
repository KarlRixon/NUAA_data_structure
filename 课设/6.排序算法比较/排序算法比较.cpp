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
		//�������������һ�Ƚϣ�����tempʱ�������ƺ�
		while((j>=0)&&(data[j]>temp)){
			data[j+1]=data[j];
			j--;
		}
		//���ڴ���temp����
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
	for(int div=len/2;div>=1;div=div/2){//������div�������ϼ�С
		for(int i=0;i<=div;++i){//�����div��
			for(int j=i;j<len-div;j+=div)//��ÿ����в�������
				for(int k=j;k<len;k+=div)
					if(data[j]>data[k])
						swapInt(data+j,data+k);//������������ֵ
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
    int key = a[first];/*���ֱ�ĵ�һ����¼��Ϊ����*/
    while(first < last)
    {
        while(first < last && a[last] >= key)
        {
            --last;
        }
        a[first] = a[last];/*���ȵ�һ��С���Ƶ��Ͷ�*/
        while(first < last && a[first] <= key)
        {
            ++first;
        }
        a[last] = a[first];/*���ȵ�һ������Ƶ��߶�*/
    }
    a[first] = key;/*�����¼��λ*/
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
        //�ӽ���λ��=2*�������λ�ã�+1
        nChild=2*i+1;
        //�õ��ӽ���нϴ�Ľ��
        if(nChild<nLength-1&&array[nChild+1]>array[nChild])++nChild;
        //����ϴ���ӽ����ڸ������ô�ѽϴ���ӽ�������ƶ����滻���ĸ����
        if(array[i]<array[nChild])
        {
            nTemp=array[i];
            array[i]=array[nChild];
            array[nChild]=nTemp; 
        }
        else break; //�����˳�ѭ��
    }
}
//�������㷨
void HeapSort(int array[],int length)
{
    int i;
    //�������е�ǰ�벿��Ԫ�أ�������֮���һ��Ԫ�������е�����Ԫ��
    //length/2-1�����һ����Ҷ�ڵ㣬�˴�"/"Ϊ����
    for(i=length/2-1;i>=0;--i)
    HeapAdjust(array,i,length);
    //�����һ��Ԫ�ؿ�ʼ�����н��е��������ϵ���С�����ķ�Χֱ����һ��Ԫ��
    for(i=length-1;i>0;--i)
    {
        //�ѵ�һ��Ԫ�غ͵�ǰ�����һ��Ԫ�ؽ�����
        //��֤��ǰ�����һ��λ�õ�Ԫ�ض��������ڵ��������֮������
        array[i]=array[0]^array[i];
        array[0]=array[0]^array[i];
        array[i]=array[0]^array[i];
        //������С����heap�ķ�Χ��ÿһ�ε�����ϱ�֤��һ��Ԫ���ǵ�ǰ���е����ֵ
        HeapAdjust(array,0,i);
    }
}
void merge(int *data, int start, int mid, int end, int *result)
{
    int i, j, k;
    i = start;
    j = mid + 1;                        //�����ظ��Ƚ�data[mid]
    k = 0;
    while (i <= mid && j <= end)        //����data[start,mid]������(mid,end]��û��ȫ����������result��ȥ
    {
        if (data[i] <= data[j])         //���data[i]С�ڵ���data[j]
            result[k++] = data[i++];    //��data[i]��ֵ����result[k]��֮��i,k����һ����ʾ����һλ
        else
            result[k++] = data[j++];    //���򣬽�data[j]��ֵ����result[k]��j,k����һ
    }
    while (i <= mid)                    //��ʾ����data(mid,end]�Ѿ�ȫ������result������ȥ�ˣ�������data[start,mid]����ʣ��
        result[k++] = data[i++];        //������data[start,mid]ʣ�µ�ֵ����һ��������result
    while (j <= end)                    //��ʾ����data[start,mid]�Ѿ�ȫ�����뵽result������ȥ�ˣ�������(mid,high]����ʣ��
        result[k++] = data[j++];        //������a[mid,high]ʣ�µ�ֵ����һ��������result

    for (i = 0; i < k; i++)             //���鲢��������ֵ��һ��������data[start,end]
        data[start + i] = result[i];    //ע�⣬Ӧ��data[start+i]��ʼ��ֵ
}
void MergeSort(int *data, int start, int end, int *result)
{
    if (start < end)
    {
        int mid = (start + end) / 2;
        MergeSort(data, start, mid, result);                    //����߽�������
        MergeSort(data, mid + 1, end, result);                  //���ұ߽�������
        merge(data, start, mid, end, result);                    //������õ����ݺϲ�
    }
}
int maxbit(int data[], int n) //���������������ݵ����λ��
{
    int d = 1; //��������λ��
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
void RadixSort(int data[], int n) //��������
{
    int d = maxbit(data, n);
    int *tmp = new int[n];
    int *count = new int[10]; //������
    int i, j, k;
    int radix = 1;
    for(i = 1; i <= d; i++) //����d������
    {
        for(j = 0; j < 10; j++)
            count[j] = 0; //ÿ�η���ǰ��ռ�����
        for(j = 0; j < n; j++)
        {
            k = (data[j] / radix) % 10; //ͳ��ÿ��Ͱ�еļ�¼��
            count[k]++;
        }
        for(j = 1; j < 10; j++)
            count[j] = count[j - 1] + count[j]; //��tmp�е�λ�����η����ÿ��Ͱ
        for(j = n - 1; j >= 0; j--) //������Ͱ�м�¼�����ռ���tmp��
        {
            k = (data[j] / radix) % 10;
            tmp[count[k] - 1] = data[j];
            count[k]--;
        }
        for(j = 0; j < n; j++) //����ʱ��������ݸ��Ƶ�data��
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
	//ֱ�Ӳ������� 
	cout<<"--------ֱ�Ӳ�������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//ϣ������ 
	cout<<"--------ϣ������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//ð������ 
	cout<<"--------ð������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//�������� 
	cout<<"--------��������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	
	//ѡ������ 
	cout<<"--------ѡ������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//������ 
	cout<<"--------������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//�鲢���� 
	cout<<"--------�鲢����"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;

	//�������� 
	cout<<"--------��������"<<endl;
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
		cout<<"����"<<i<<"��ʱ��"<<dom<<"\t";
		infile.close();
//		if(i==9){
//			for(int m=0;m<20000;m++)cout<<data[m]<<"\t";
//		} 
	}
	cout<<endl;
	cout<<"ƽ����ʱ��"<<endl;
	cout<<"ֱ�Ӳ�������"<<average[0]/10<<"\t";
	cout<<"ϣ������"<<average[1]/10<<"\t";
	cout<<"ð������"<<average[2]/10<<"\t";
	cout<<"��������"<<average[3]/10<<"\t";
	cout<<"ѡ������"<<average[4]/10<<"\t";
	cout<<"������"<<average[5]/10<<"\t";
	cout<<"�鲢����"<<average[6]/10<<"\t";
	cout<<"��������"<<average[7]/10<<"\t";
}
