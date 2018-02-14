// StackFrom2Queue.cpp : �������̨Ӧ�ó������ڵ㡣
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
	//һֱ��֤q1��q2��һ��Ϊ�գ�����q1��ջ 1 2 3 4 ������Ҫ��ջ4����ô��1 2 3 ������q1�������q2��4��ջ
	//֮�󣬴�ʱ����м���һ��Ԫ�أ���ô���ӵ�q2�С�
	
	if (q1.size()==0 && q2.size() ==0)//���q1��q2��Ϊ�գ���ô��q1�в���Ԫ��
	{
		q1.push(data);
	}
	else if (q1.size()>0)//���q1��Ϊ�գ���ô��q1�в���Ԫ��
	{
		q1.push(data);
	}
	else if(q2.size()>0)//���q2��Ϊ�գ���ô��q1�в���Ԫ��
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
	cout<<"Ԫ�صĸ�����"<<stack.GetNum()<<endl;

	cout<<"��ջ������ȳ�����99��"<<endl;
	stack.deleteTail();
	cout<<"Ԫ�صĸ�����"<<stack.GetNum()<<endl;
	stack.appendTail(777);
	cout<<"Ԫ�صĸ�����"<<stack.GetNum()<<endl;

	cout<<"��ջ������ȳ�����777��"<<endl;
	stack.deleteTail();
	cout<<"Ԫ�صĸ�����"<<stack.GetNum()<<endl;



	getchar();
	return 0;
}
