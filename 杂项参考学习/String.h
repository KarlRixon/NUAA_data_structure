#pragma once
/*
* author: acme
*   date: 2017-2-28
*  blogs: http://blog.csdn.net/qq_18297675
*/
#include <iostream>
using namespace std;
#define MAX_LEN 256    //Ĭ����󳤶���256

class String
{
public:
	String();													//Ĭ�Ϲ���
	String(int maxLen);											//ָ���ַ�����󳤶�
	String(char* s);											//ָ���ַ���
	template<typename T>
	String(T a[], int arraySize, char separator = ' ');         //���ݸ��������ʼ���ַ���
	~String();

public:
	int Size();										//��ȡ�ַ�����С
	void PushRear(char ch);							//���һ���ַ������
	void PushRear(char* sub);						//����ַ��������
	void PushFront(char ch);						//���һ���ַ���ǰ��
	void PushFront(char* sub);						//����ַ�����ǰ��
	void PopRear(int n = 1);						//ɾ�����n���ַ�
	void PopFront(int n = 1);						//ɾ��ǰ��n���ַ�
	int DeleteSub(int start, int end);				//���ݷ�Χɾ���Ӵ�
	int DeleteSubLen(int start, int len);           //������ʼλ�úͳ���ɾ���Ӵ�
	char* SubString(int start, int end);            //���ݷ�Χ��ȡ�Ӵ�
	char* SubStringLen(int start, int len);         //������ʼλ�úͳ��Ƚ�ȡ�Ӵ�
	int Replace(char s, char d);					//�滻�ַ�(���ϵĶ����滻)
	int Replace(int local, char d);					//�滻ָ��λ���ַ�
	int Replace(char* s, char* d);					//�滻�Ӵ�(���ϵĶ����滻)
	int Replace(int local, char* d);				//�滻ָ��λ���Ӵ�
	int FindFirst(char ch);                         //�����ַ���һ�γ��ֵ�λ��
	int FindFirst(char* sub);                       //�����Ӵ���һ�γ��ֵ�λ��
	int FindLast(char ch);                          //�����ַ����һ�γ��ֵ�λ��
	int FindLast(char* sub);                        //�����Ӵ����һ�γ��ֵ�λ��
	int Find(char ch, int start);                   //������ʼλ�ò����ַ����ֵ�λ��
	int Find(char* sub, int start);                 //������ʼλ�ò����Ӵ����ֵ�λ��
	void Insert(char ch, int local);                //�����ַ�
	void Insert(char* sub, int local);              //�����Ӵ�
	int AppearTimes(char ch);                       //ͳ���ַ����ֹ��Ĵ���
	int AppearTimes(char* sub);                     //ͳ���Ӵ����ֹ��Ĵ���
	bool Equal(String& s1, String& s2);            //�Ƚ�����String�Ƿ����
	bool Equal(const char* s1, const char* s2);   //�Ƚ�����String�Ƿ����
	char* GetString();                              //��ȡ�ַ���
	void Print(int start, int end);					//��ӡ�ַ���
	void Clear();                                   //����ַ���
	void Destroy();                                 //�����ַ���
private:
	int ReAlloc();									//���·���ռ�
	void InitStr(char* str, int value, int len);	//��ʼ���ַ���
	int _csize(const char* str);					//�����ַ�������(խ�ַ�)
	int _wsize(const wchar_t* str);					//�����ַ�������(���ַ�)
private:
	char* m_string;
	int m_curLen;
	int m_maxLen;
};

/*
*  ģ�庯��Ҫ��������д��ͬһ���ļ���
*/
template<typename T>
String::String(T a[], int arraySize, char separator)
{
	m_string = new char[MAX_LEN + arraySize];		//Ϊ����������ռ�
	InitStr(m_string, 0, MAX_LEN);					//��ʼ���ַ���
	m_curLen = 0;
	m_maxLen = MAX_LEN + arraySize;					//������󳤶�Ĭ��ΪMAX_LEN
	String s;
	for (int i = 0; i < arraySize; i++)
	{
		char buf[64] = "";
		if (s.Compare(typeid(T).name(), "int"))
			sprintf_s(buf, "%d", a[i]);
		else if (s.Compare(typeid(T).name(), "double"))
			sprintf_s(buf, "%lf", a[i]);
		else
			sprintf_s(buf, "%s", a[i]);
		int len = _csize(buf);
		for (int j = 0; j < len; j++)
			m_string[m_curLen + j] = buf[j];
		if (i != arraySize - 1)
			m_string[m_curLen + len] = separator;   //����ָ���
		m_curLen += len + 1;
	}
}
#pragma once
