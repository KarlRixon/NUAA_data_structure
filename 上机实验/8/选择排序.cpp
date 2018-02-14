#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
using namespace std;
const int N=10;
int main()
{
    int a[N],i,j,temp,b;
    srand(time(NULL));
    for(i=0;i<N;i++)
        a[i]=rand()%100;
    for(i=0;i<N;i++)
        cout<<setw(3)<<a[i];
    cout<<endl;
    for(i=0;i<N-1;i++)
    {
        temp=i;
        for(j=i+1;j<N;j++)
        {
            if(a[temp]>a[j])
                temp=j;
        }
        if(i!=temp)
        {
            b=a[temp];
            a[temp]=a[i];
            a[i]=b;}
    }
    for(i=0;i<N;i++)
        cout<<setw(3)<<a[i];
    cout<<endl;
}
