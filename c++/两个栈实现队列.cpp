// StackFrom2Queue.cpp : 定义控制台应用程序的入口点。
//

//#include "stdafx.h"
#include <iostream>
#include <queue>
using namespace std;

template<typename T>
class CStack
{
private:
	queue<T> q1;
	queue<T> q2;
	int nCount;
	

public:
	void appendTail(const T& data);
	T deleteTail();
	int GetNum() const;
	CStack()
	{
		nCount = 0;
	}
};

template<typename T>
int CStack<T>::GetNum() const
{
	return nCount;
}

template<typename T>
void CStack<T>::appendTail(const T& data)
{
	//一直保证q1与q2有一个为空，比如q1如栈 1 2 3 4 ，现在要出栈4，那么把1 2 3 出队列q1让如队列q2，4出栈
	//之后，此时如果有加入一个元素，那么最后加到q2中。
	
	if (q1.size()==0 && q2.size() ==0)//如果q1与q2都为空，那么往q1中插入元素
	{
		q1.push(data);
	}
	else if (q1.size()>0)//如果q1不为空，那么往q1中插入元素
	{
		q1.push(data);
	}
	else if(q2.size()>0)//如果q2不为空，那么往q1中插入元素
	{
		q2.push(data);
	}
	++nCount;
}

template<typename T>
T CStack<T>::deleteTail()
{
	T ret;
	if (q2.size() == 0)
	{

		while(q1.size() != 1)
		{
			T& data = q1.front();
			q1.pop();
			q2.push(data);
		}
		ret = q1.front();
		q1.pop();
		cout<<ret<<endl;
	}
	else
	{
		while(q2.size() != 1)
		{
			T& data = q2.front();
			q2.pop();
			q1.push(data);
		}
		ret = q2.front();
		q2.pop();
		cout<<ret<<endl;
	}
	--nCount;
	return ret;
}

int main(int argc)
{

	CStack<int> stack;
	stack.appendTail(88);
	stack.appendTail(44);
	stack.appendTail(99);
	cout<<"元素的个数："<<stack.GetNum()<<endl;

	cout<<"出栈，后进先出：出99："<<endl;
	stack.deleteTail();
	cout<<"元素的个数："<<stack.GetNum()<<endl;
	stack.appendTail(777);
	cout<<"元素的个数："<<stack.GetNum()<<endl;

	cout<<"出栈，后进先出：出777："<<endl;
	stack.deleteTail();
	cout<<"元素的个数："<<stack.GetNum()<<endl;



	getchar();
	return 0;
}
