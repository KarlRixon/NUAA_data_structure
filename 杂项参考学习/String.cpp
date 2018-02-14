#include "String.h"


/*
* function			Ĭ�ϳ��ȣ����ַ���
*/
String::String()
{
	m_string = new char[MAX_LEN];			//Ϊ����������ռ�
	InitStr(m_string, 0, MAX_LEN);			//��ʼ���ַ���	
	m_curLen = 0;							//��ǰ������Ϊ0
	m_maxLen = MAX_LEN;						//������󳤶�Ĭ��ΪMAX_LEN
}

/*
* function			����ָ���ַ�����󳤶�
* param    len		����
*/
String::String(int maxLen)
{
	m_string = new char[maxLen];			//Ϊ����������ռ�
	InitStr(m_string, 0, maxLen);			//��ʼ���ַ���	
	m_curLen = 0;                           //��ǰ������Ϊ0
	m_maxLen = maxLen;						//������󳤶�Ϊ�û�ָ����maxLen
}

/*
* function			����ָ���ַ�����ʼ��
* param    s		�ַ���
*/
String::String(char* s)
{
	m_string = new char[MAX_LEN];			//Ϊ����������ռ�
	InitStr(m_string, 0, MAX_LEN);			//��ʼ���ַ���
	m_curLen = _csize(s);					//��ǰ������Ϊstr�ĳ���
	m_maxLen = MAX_LEN;						//������󳤶�Ĭ��ΪMAX_LEN
	for (int i = 0; i < m_curLen; i++)
		m_string[i] = s[i];
}

String::~String()
{
	if (m_string)
		delete[] m_string;
	m_string = NULL;
}

/*
* function			��ȡ�ַ�����С
* return   int      �����ַ�����С
*/
int String::Size()
{
	return m_curLen;
}

/*
* function			���·���ռ�
* return   int      ���ط���ռ�Ĵ�С��ʧ�ܷ���-1
*/
int String::ReAlloc()
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	int len = m_maxLen;
	char* temp = new char[len];
	for (int i = 0; i < len; i++)						//�������ݴ�����
		temp[i] = m_string[i];
	m_maxLen *= 2;									//����Ϊԭ��������
	m_string = new char[m_maxLen];
	InitStr(m_string, 0, m_maxLen);					//��ʼ��
	for (int i = 0; i < len; i++)						//�������ݴ�����
		m_string[i] = temp[i];						//�ָ����� 
	delete[] temp;
	return m_maxLen;
}

/*
* function			��ʼ���ַ���
* param    str		�ַ���
* parma    value    ��ʼֵ
* param    len      ����
* return		    ��
*/
void String::InitStr(char* str, int value, int len)
{
	for (int i = 0; i < len; i++)
		str[i] = value;
}

/*
* function			�����ַ�������(խ�ַ�)
* param    str		�ַ���
* return		    ���س���
*/
int String::_csize(const char* str)
{
	if (!str) return 0;
	int len = 0;
	while (*str)
	{
		if ((int)*str < 0)  //���ĵ�һ���ֽ�Ϊ����
			str += 2;
		else
			++str;
		++len;
	}
	return len;
}

/*
* function			�����ַ�������(���ַ�)
* param    str		�ַ���
* return		    ���س���
*/
int String::_wsize(const wchar_t* str)
{
	if (!str) return 0;
	int len = 0;
	while (*str++)
		++len;
	return len;
}

/*
* function			���һ���ַ������
* param    char		�ַ�
* return		    ��
*/
void String::PushRear(char ch)
{
	if (!m_string)				//��ֹ���ÿ�ָ��
		return;
	if (m_curLen == m_maxLen)  //����ռ����� ��Ҫ���·���
		ReAlloc();
	m_string[m_curLen++] = ch;
}

/*
* function			����ַ��������
* param    sub		�ַ���
* return		    ��
*/
void String::PushRear(char* sub)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	int len = _csize(sub);
	while (m_curLen + len >= m_maxLen)  //����ռ����� ��Ҫ���·���
		ReAlloc();
	for (int i = 0; i < len; i++)
		m_string[m_curLen + i] = sub[i];
}

/*
* function			���һ���ַ���ǰ��
* param    char		�ַ�
* return		    ��
*/

void String::PushFront(char ch)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	if (m_curLen == m_maxLen)  //����ռ����� ��Ҫ���·���
		ReAlloc();
	for (int i = m_curLen; i > 0; i--)
		m_string[i] = m_string[i - 1];
	m_string[0] = ch;
	m_curLen++;
}

/*
* function			����ַ�����ǰ��
* param    sub		�ַ���
* return		    ��
*/

void String::PushFront(char* sub)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	int len = _csize(sub);
	while (m_curLen + len >= m_maxLen)  //����ռ����� ��Ҫ���·���
		ReAlloc();
	for (int i = m_curLen + len - 1; i >= 0; i--)
		m_string[i] = m_string[i - len];
	for (int i = 0; i < len; i++)
		m_string[i] = sub[i];
	m_curLen += len;
}

/*
* function			ɾ�����n���ַ�
* return		    ��
*/
void String::PopRear(int n)
{
	m_curLen = m_curLen - n > 0 ? (m_curLen -= n) : 0;
}

/*
* function			ɾ��ǰn���ַ�
* return		    ��
*/
void String::PopFront(int n)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	if (m_curLen - n > 0)
	{
		for (int i = 0; i < m_curLen - n; i++)
			m_string[i] = m_string[i + n];
		m_curLen -= n;
	}
	else
		m_curLen = 0;

}

/*
* function			ɾ���Ӵ�
* param    start	ɾ������ʼλ��
* param    end		ɾ�����յ�λ��
* return		    ɾ��ʧ�ܷ���-1
*/
int String::DeleteSub(int start, int end)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	if (start < 0 || start > m_curLen - 1 || end < 0 ||
		end >  m_curLen - 1 || end < start)
		return -1;
	int len = end - start;
	m_curLen -= len;
	for (int i = start; i <= m_curLen; i++)
		m_string[i] = m_string[i + len + 1];
	return len + 1;
}

/*
* function			ɾ���Ӵ�
* param    start	ɾ������ʼλ��
* param    len		Ҫɾ���ĳ���
* return		    ɾ��ʧ�ܷ���-1
*/
int String::DeleteSubLen(int start, int len)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	if (start < 0 || start > m_curLen - 1)
		return -1;
	if (start + len > m_curLen)
		len = m_curLen - start;
	m_curLen -= len;
	for (int i = start; i <= m_curLen; i++)
		m_string[i] = m_string[i + len];
	return len;
}

/*
* function			��ȡ�Ӵ�
* param    start	��ȡ����ʼλ��
* param    end		��ȡ���յ�λ��
* return		    ��ȡʧ�ܷ���NULL
*/
char* String::SubString(int start, int end)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return NULL;
	if (start < 0 || start > m_curLen - 1 || end < 0 ||
		end >  m_curLen - 1 || end < start)
		return NULL;
	char* sub = new char[end - start];
	for (int i = start; i <= end; i++)
		sub[i] = m_string[i];
	sub[end - start + 1] = '\0';   //���Ҫ�ǵü��ϡ�\0������������Ȼ�����ʱ������������
	return sub;
}

/*
* function			��ȡ�Ӵ�
* param    start	��ȡ����ʼλ��
* param    len		��ȡ�ĳ���
* return		    ��ȡʧ�ܷ���NULL
*/
char* String::SubStringLen(int start, int len)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return NULL;
	if (start < 0 || start > m_curLen - 1)
		return NULL;
	if (start + len > m_curLen)
		len = m_curLen;
	char* sub = new char[len];
	for (int i = start; i <= start + len; i++)
		sub[i] = m_string[i];
	sub[len] = '\0';   //���Ҫ�ǵü��ϡ�\0������������Ȼ�����ʱ������������
	return sub;
}

/*
* function			�滻�ַ�
* param    s		�滻��Դ�ַ�
* param    d		�滻����ַ�
* return		    �滻ʧ�ܷ���-1
*/
int String::Replace(char s, char d)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	int pos = 0;
	int count = 0;
	if ((pos = FindFirst(s)) == -1)      //������ַ������ڣ����滻ʧ��
		return -1;
	do
	{
		m_string[pos] = d;
		++count;
	} while ((pos = Find(s, pos + 1)) != -1);
	return count;                              //���سɹ��滻���ַ���
}

/*
* function			�滻�ַ�
* param    local	�滻��λ��
* param    d		�滻����ַ�
* return		    �滻ʧ�ܷ���-1
*/
int String::Replace(int local, char d)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	if (local < 0 || local > m_curLen - 1)
		return -1;
	m_string[local] = d;
	return local;
}

/*
* function			�滻�Ӵ�
* param    s		�滻��Դ��
* param    d		�滻��Ŀ�괮
* return		    �滻ʧ�ܷ���-1
*/
int String::Replace(char* s, char* d)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	int pos = 0;
	int count = 0;
	int lens = _csize(s);
	int lend = _csize(d);
	if ((pos = FindFirst(s)) == -1)      //������ַ������ڣ����滻ʧ��
		return -1;
	do
	{
		//���s����d��������ȣ���ֱ�Ӹ��Ǽ���
		if (lens == lend)
		{
			for (int i = 0; i < lens; i++)
				m_string[i + pos] = d[i];
		}
		else if (lens > lend)  //���s������d��������Ҫ���Ǻ���ǰ�ƣ����λ�ã�
		{
			for (int i = 0; i < lend; i++)    //����
				m_string[i + pos] = d[i];
			int p = lens - lend;            //��ǰ�ƶ��ľ���
			for (int i = pos + lend; i < m_curLen; i++)    //��ǰ��
				m_string[i] = m_string[i + p];
			m_curLen -= p;
		}
		else   //���s��С��d��������Ҫ����ǰ�����ƣ��ճ�λ�ã�
		{
			int p = lend - lens;            //�����ƶ��ľ���
			for (int i = m_curLen + p; i >= pos + lens; i--)    //������
				m_string[i] = m_string[i - p];
			for (int i = 0; i < lend; i++)    //����
				m_string[i + pos] = d[i];
			m_curLen += p;
		}
		++count;
	} while ((pos = Find(s, pos + lend)) != -1);
	return count;                              //���سɹ��滻���ַ���
}

/*
* function			�滻�Ӵ�
* param    local	�滻����ʼλ��
* param    d		�滻��Ŀ�괮
* return		    �滻ʧ�ܷ���-1
*/
int String::Replace(int local, char* d)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	if (local < 0 || local > m_curLen - 1)
		return -1;
	int len = _csize(d);
	if (local + len >= m_maxLen)   //�ռ䲻�� ���·���
		ReAlloc();
	for (int i = 0; i < len; i++)
		m_string[i + local] = d[i];
	m_curLen += len;
	return local;
}

/*
* function			�����ַ���һ�γ��ֵ�λ��
* param    ch		Ҫ���ҵ��ַ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindFirst(char ch)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	for (int i = 0; i < m_curLen; i++)
		if (m_string[i] == ch)
			return i;
	return -1;
}

/*
* function			�����Ӵ���һ�γ��ֵ�λ��
* param    sub		Ҫ���ҵ��Ӵ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindFirst(char* sub)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	int i = 0, j = 0;
	int len = _csize(sub);
	for (; i < m_curLen; i++)
	{
		for (j = 0; j < len; j++)
			if (m_string[i + j] != sub[j])
				break;
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			�����ַ����һ�γ��ֵ�λ��
* param    ch		Ҫ���ҵ��ַ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindLast(char ch)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	for (int i = m_curLen - 1; i >= 0; i--)
		if (m_string[i] == ch)
			return i;
	return -1;
}

/*
* function			�����Ӵ����һ�γ��ֵ�λ��
* param    ch		Ҫ���ҵ��Ӵ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindLast(char* sub)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	int i = m_curLen - 1, j = 0;
	int len = _csize(sub);
	for (; i >= 0; i--)
	{
		for (j = 0; j < len; j++)
			if (m_string[i - j] != sub[len - 1 - j])  //�Ӻ���ǰ��
				break;
		if (j == len)
			return i - len + 1;
	}
	return -1;
}

/*
* function			������ʼλ�ò����ַ����ֵ�λ��
* param    ch		Ҫ���ҵ��ַ�
* param    start	��ʼλ��
* return		    ����ʧ�ܷ���-1
*/
int String::Find(char ch, int start)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	for (int i = start; i < m_curLen; i++)
		if (m_string[i] == ch)
			return i;
	return -1;
}

/*
* function			�����Ӵ����һ�γ��ֵ�λ��
* param    sub		Ҫ���ҵ��Ӵ�
* param    start	��ʼλ��
* return		    ����ʧ�ܷ���-1
*/
int String::Find(char* sub, int start)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return -1;
	int i = start, j = 0;
	int len = _csize(sub);
	for (; i < m_curLen; i++)
	{
		for (j = 0; j < len; j++)
			if (m_string[i + j] != sub[j])
				break;
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			�����ַ�
* param    ch		Ҫ������ַ�
* param    local    Ҫ�����λ��
* return		    ��
*/
void String::Insert(char ch, int local)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	local = local < 0 ? 0 : local >= m_curLen ? m_curLen : local;
	if (m_curLen + 1 >= m_maxLen)  //����ռ䲻�� ���·���
		ReAlloc();
	for (int i = m_curLen; i > local; i--)
		m_string[i] = m_string[i - 1];
	m_string[local] = ch;
	m_curLen++;
}

/*
* function			�����ַ���
* param    sub		Ҫ������ַ���
* param    local    Ҫ�����λ��
* return		    ��
*/
void String::Insert(char* sub, int local)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	local = local < 0 ? 0 : local >= m_curLen ? m_curLen : local;
	int len = _csize(sub);
	while (m_curLen + len >= m_maxLen)//����ռ䲻�� ���·���
		ReAlloc();
	for (int i = m_curLen + len - 1; i >= local; i--)
		m_string[i] = m_string[i - len];
	for (int i = 0; i < len; i++)
		m_string[i + local] = sub[i];
	m_curLen += len;
}

/*
* function			ͳ���ַ����ֹ��Ĵ���
* param    ch		Ҫ���ҵ��ַ�
* return		    �����ַ����ֵĴ���
*/
int String::AppearTimes(char ch)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return 0;
	int count = 0;
	for (int i = 0; i < m_curLen; i++)
		if (m_string[i] == ch)
			++count;
	return count;
}

/*
* function			ͳ���Ӵ����ֹ��Ĵ���
* param    sub		Ҫ���ҵ��Ӵ�
* return		    �����ַ����ֵĴ���
*/
int String::AppearTimes(char* sub)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return 0;
	int len = _csize(sub);
	int pos = 0;
	if ((pos = FindFirst(sub)) == -1)
		return 0;
	int count = 1;
	while ((pos = Find(sub, pos + len)) != -1)
		++count;
	return count;
}

/*
* function			�Ƚ�����String�Ƿ����
* param    s1		�ַ���1
* param    s2		�ַ���2
* return		    ��ȷ���true
*/
bool String::Equal(String& s1, String& s2)
{
	if (!s1.m_string || !s2.m_string)  //��ֹ���ÿ�ָ��
		return false;
	int len1 = s1.Size();
	int len2 = s2.Size();
	if (len1 != len2)
		return false;
	for (int i = 0; i < len1; i++)
		if (s1.m_string[i] != s2.m_string[i])
			return false;
	return true;
}

/*
* function			�Ƚ�����String�Ƿ����
* param    s1		�ַ���1
* param    s2		�ַ���2
* return		    ��ȷ���true
*/
bool String::Equal(const char* s1, const char* s2)
{
	if (!s1 || !s2)  //��ֹ���ÿ�ָ��
		return false;
	int len1 = _csize(s1);
	int len2 = _csize(s2);
	if (len1 != len2)
		return false;
	for (int i = 0; i < len1; i++)
		if (s1[i] != s2[i])
			return false;
	return true;
}

/*
* function			����ַ���
* return		    ��
*/
void String::Clear()
{
	m_curLen = 0;
}

/*
* function			�����ַ���
* return		    ��
*/
void String::Destroy()
{
	if (m_string)
		delete[] m_string;
	m_string = NULL;
	m_curLen = 0;
}

/*
* function			��ȡ�ַ���
* param    str		�ַ���
* return		    ����data
*/
char* String::GetString()
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return NULL;
	return m_string;
}

/*
* function			��ӡ�ַ���
* param    start    ��ʼλ��
* param    end      �յ�λ��
* return		    ��
*/
void String::Print(int start, int end)
{
	if (!m_string)  //��ֹ���ÿ�ָ��
		return;
	start = start<0 || start > m_curLen - 1 ? 0 : start;	//��ֹԽ��
	end = end<0 || end > m_curLen - 1 ? m_curLen : end;	//��ֹԽ��
	if (end < start)											//��ֹ����
	{
		int temp = 0;
		temp = start;
		start = end;
		end = start;
	}
	for (int i = start; i < end; i++)
		cout << m_string[i];
	cout << endl;
}