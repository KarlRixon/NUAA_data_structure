/*
* author: acme
*   date: 2017-3-6
*  blogs: http://blog.csdn.net/qq_18297675
*/
#pragma once
#include <iostream>
#include <locale.h>
using namespace std;

class String
{
private:  //�ڵ���
	class Node
	{
	public:
		Node(int ch = 0, Node* next = nullptr, Node* pre = nullptr)
			:c(0), w(0), next(next), pre(pre)
		{
			if (ch > 255)
				w = (wchar_t)ch;
			else
				c = (char)ch;
		}
	private:
		Node* next;   //��̽ڵ�
		Node* pre;    //ǰ���ڵ�
		char c;
		wchar_t w;
		friend class String;
	};
public:
	String();											//Ĭ�Ͽմ�
	String(char* s);									//����ָ���ַ�����ʼ��
	template<typename T>
	String(T a[], int arraySize, int separator);		//������������ʼ��String

	~String();
public:
	int Size();											//��ȡ�ַ�����С
	int Bytes();										//��ȡ�ַ����ֽ���
	bool IsEmpty();                                     //�Ƿ�Ϊ��
	void PushFront(int ch);							    //���һ���ַ���ǰ��
	void PushRear(int ch);								//���һ���ַ������
	void PushFront(char* s);							//����ַ�����ǰ��
	void PushRear(char* s);								//����ַ���������
	void PopRear(int n = 1);							//ɾ������n���ַ�
	void PopFront(int n = 1);                           //ɾ��ǰ��n���ַ�
	int Delete(int local);								//ɾ��ָ��λ���ַ�
	int DeleteSub(int start, int end);					//����ָ����Χɾ���Ӵ�
	int DeleteSubLen(int start, int len);				//����ָ������ɾ���Ӵ�
	char* SubString(int start, int end);				//����ָ����Χ��ȡ�Ӵ�
	char* SubStringLen(int start, int len);				//����ָ�����Ƚ�ȡ�Ӵ�
	int Replace(int s, int d);							//���ݸ����ַ��滻�ַ�
	int ReplaceLocal(int local, int d);                 //����ָ��λ���滻�ַ�
	int Replace(char* s, char* d);                      //���ݸ��ַ����滻�ַ���
	Node* Replace(int local, char* d);                  //���ݸ���λ���滻�ַ���
	int FindFirst(int ch);                              //�����ַ���һ�γ��ֵ�λ��
	int FindLast(int ch);                               //�����ַ����һ�γ��ֵ�λ�� 
	int Find(int ch, int start);						//���ݸ�����ʼλ�ò����ַ����ֵ�λ��
	int FindFirst(char* s);                             //�����ַ�����һ�γ��ֵ�λ��
	int FindLast(char* s);                              //�����ַ������һ�γ��ֵ�λ�� 
	int Find(char* s, int start);						//���ݸ�����ʼλ�ò����ַ������ֵ�λ��
	void Insert(int local, int ch, int n = 1);			//��ָ��λ�ò���n���ַ�
	void Insert(int local, char* sub, int n = 1);        //��ָ��λ�ò���n���ַ���
	int AppearTimes(int ch);							//ͳ���ַ����ֵĴ���							
	int AppearTimes(char* s);							//ͳ���ַ������ֵĴ���
	bool Equal(String& s);								//�Ƚ�����String�Ƿ����
	bool Equal(const char* s);							//�Ƚ�����String�Ƿ����
	char* GetString();									//��ȡ�ַ���
	void Print(int start, int end);						//��ӡ�ַ���
	void Clear();										//����ַ���
	void Reverse();										//��ת�ַ���
	void ConCat(char* s);								//�����ַ���
	void ConCat(String& s);								//�����ַ���
	void Assign(char* s);                               //��ֵ
	void Assign(String& s);                             //��ֵ
	int GetAt(int iPos);                                //��ȡָ��λ�õ�ֵ 
	String& operator +(String& s);                      //����+�������      
	String& operator +(char* s);						//����+�������     
	String& operator =(String& s);                      //����=������� 
	String& operator =(char* s);						//����=�������
	String& operator +=(String& s);                     //����+=������� 
	String& operator +=(char* s);						//����+=�������
	int operator [](int iPos);							//����[]�����   
private:
	Node* CreateNode(int ch = 0);                        //�����ڵ�
	int _cbytes(char* str);                              //�����ַ����ֽ���(խ�ַ�)
	int _csize(char* str);								 //�����ַ�������(խ�ַ�)
	void FreeNode(int start, int num);					 //�ͷŽڵ�
	Node* GetNodes(int start, int num);					 //��ȡ�ڵ�
	void InitBuf(char* buf, int value, int len);		 //��ʼ��������
	char* GetStringFromNodes(Node* nodes, int num);		 //�ӽڵ��л�ȡ���ַ���
	wchar_t CToW(char ch1, char ch2);					 //խ�ַ�ת��Ϊ���ַ�
	char* WToC(wchar_t ch);								 //���ַ�ת��Ϊխ�ַ�
	Node* GetNode(int start);                            //��ȡ��ʼλ�õ��Ǹ��ڵ�
private:
	Node* m_head;
	Node* m_tail;
	int m_count;
};

/*
* function			�����������ʼ��String
* param    array	int����
* param    arraySize�����С
* param    separator�ָ���
* return   String	�ַ�����
*/
template<typename T>
String::String(T a[], int arraySize, int separator)
{
	m_head = new Node();    //����ͷ�ڵ�
	m_tail = new Node();    //����β�ڵ�
	m_count = 0;
	String s;
	for (int i = 0; i < arraySize; i++)
	{
		char buf[64] = "";
		if (s.Equal(typeid(T).name(), "int"))
			sprintf(buf, "%d", a[i]);
		else if (s.Equal(typeid(T).name(), "double"))
			sprintf(buf, "%lf", a[i]);
		int len = _csize(buf);
		for (int j = 0; j < len; j++)
			PushRear(buf[j]);
		if (i != arraySize - 1)
			PushRear(separator);   //����ָ���
	}

	return *pstr;
}
#pragma once
