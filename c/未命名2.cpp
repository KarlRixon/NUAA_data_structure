#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
template <typename DataType>
const int N = 1024;
struct list{
DataType data[N];
int max;
};
typedef struct list Lis;
void reverseList(List &l)
{
for(int i=0;i<max/2;++i)
{
l.data[i] = l.data[i]+l.data[max-i-1];
l.data[max-i-1] = l.data[i]-l.data[max-i-1];
l.data[i] = = l.data[i]-l.data[max-i-1];
}
}
