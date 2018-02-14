#include "String.h"


/*
* function			Ĭ�ϳ��ȣ����ַ���
* return   String	String��
*/
String::String()
{
	m_head = new Node();
	m_tail = new Node();
	m_count = 0;
}

/*
* function			�������ַ�����ʼ��String
* param    s		�ַ���
* return   String   String��
*/
String::String(char* s)
{
	cout << setlocale(LC_ALL, "chs") << endl;
	m_head = new Node();
	m_tail = new Node();
	m_count = 0;
	int len = _cbytes(s);							//�����ַ����ֽ���
	for (int i = 0; i < len; i++)					//���ַ����洢��������
	{
		if ((int)s[i] < 0)				//����������ַ�������һ��
		{
			PushRear(CToW(s[i], s[i + 1]));//խ�ַ�תΪ���ַ�
			i++;
		}
		else
			PushRear(s[i]);
	}
}

String::~String()
{
	if (m_head)
		delete m_head;
	if (m_tail)
		delete m_tail;
	m_head = nullptr;
	m_tail = nullptr;
}

/***************private function start*****************/

/*
* function			�������
* param    ch		�ַ�
* return   Node*	����һ�����
*/
String::Node* String::CreateNode(int ch)
{
	Node* node = new Node(ch);         //����һ���ڵ�
	return node;
}

/*
* function			�����ַ����ֽ���(խ�ַ�)
* param    s		�ַ���
* return		    ���س���
*/
int String::_cbytes(char* s)
{
	if (!s) return 0;
	int len = 0;
	while (*s++)
		++len;
	return len;
}

/*
* function			�����ַ�������(խ�ַ�)
* param    s		�ַ���
* return		    ���س���
*/
int String::_csize(char* s)
{
	if (!s) return 0;
	int len = 0;
	while (*s)
	{
		if ((int)*s < 0)  //���ĵ�һ���ֽ�Ϊ����
			s += 2;
		else
			++s;
		++len;
	}
	return len;
}

/*
* function			�ͷŽڵ�
* param    start    �ͷŵĽڵ����ʼλ��
* param    num      �ͷŽڵ�ĸ���
* return		    ��
*/
void String::FreeNode(int start, int num)
{
	start = start < 0 ? 0 : start >m_count - 1 ? (start = m_count - 1) : start;  //��ֹԽ��
	num = start + num > m_count ? m_count - start : num;

	Node* cur = GetNode(start);   //��������ʼλ�õ�ǰһ��λ��
	Node* pre = cur->pre;

	//��ʼ�ͷ�num���ڵ�
	for (int i = 0; i < num; i++)
	{
		Node* temp = cur->next;
		delete cur;
		pre->next = temp;   //ǰָ���
		if (temp)
			temp->pre = pre;    //��ָ��ǰ
		cur = temp;         //��ǰ�ƶ�
	}
	if (start + num == m_count)  //������һ���ڵ㱻�ͷ��ˣ�����Ҫ�޸�β�ڵ�
	{
		m_tail->next = pre;
		m_tail->pre = pre->pre;
	}

	m_count -= num;
}

/*
* function			��ȡ�ڵ�
* param    start    ��ȡ�ڵ����ʼλ��
* param    num      ��ȡ�ڵ�ĸ���
* return		    ���ػ�ȡ���Ľڵ�
*/
String::Node* String::GetNodes(int start, int num)
{
	Node* cur = nullptr;
	Node* nodes = CreateNode();
	Node* node = nodes;

	//���startƫ���棬��Ӻ������
	cur = GetNode(start);

	for (int i = 0; i < num; i++)
	{
		node->next = new Node(cur->c ? cur->c : cur->w, cur->next, cur->pre);
		node = node->next;
		cur = cur->next;
	}
	node->next = nullptr;
	return nodes->next;
}

/*
* function			��ʼ��������
* param    buf		�ַ���������
* param    value    ��ʼ����ֵ
* param    len      ��������С
* return		    ��
*/
void String::InitBuf(char* buf, int value, int len)
{
	if (!buf) return;
	for (int i = 0; i < len; i++)
		buf[i] = value;
}

/*
* function			�ӽڵ��л�ȡ���ַ���
* param    nodes	�ַ��ڵ�
* param    num		�ڵ����
* return		    ����char* �ַ���
*/
char* String::GetStringFromNodes(Node* nodes, int num)
{
	if (!nodes)return nullptr;
	char* buf = new char[num * 2];  //�������������num�ռ䣬��ֹ��������ȫ����
	InitBuf(buf, 0, num * 2);
	char* ch = nullptr;                             //��Ŵӿ��ֽ�ת���������ַ�
	int j = 0;                                   //buf������±�
	for (int i = 0; i < num; i++, j++, nodes = nodes->next)
	{
		if (nodes->c != 0)
			buf[j] = nodes->c;
		else
		{
			ch = WToC(nodes->w);
			buf[j] = ch[0];
			buf[++j] = ch[1];
		}
	}
	buf[j] = '\0';  //���Ҫ�ǵü��Ͻ������
	return buf;
}

/*
* function			խ�ַ�ת��Ϊ���ַ�
* param    ch1		��һ���ֽ�
* param    ch2		�ڶ����ֽ�
* return		    ����һ�����ַ�
*/
wchar_t String::CToW(char ch1, char ch2)
{
	char buf[3] = "";
	sprintf_s(buf, "%c%c", ch1, ch2);
	wchar_t wh[1] = L"";
	mbstowcs(wh, buf, 1);
	return wh[0];
}

/*
* function			���ַ�ת��Ϊխ�ַ�
* param    ch		���ַ�
* return		    ����һ��char ch[3]�����飬һ�����ַ�ռ�����ֽ�
*/
char* String::WToC(wchar_t ch)
{
	char buf[3] = "";
	wcstombs(buf, &ch, 2);   //���ֽ�ת��Ϊխ�ֽ�
	return buf;
}

/*
* function			��ȡ��ʼλ�õ��Ǹ��ڵ�
* param    start	��ʼλ��
* return		    ������ʼ�ڵ�
*/
String::Node* String::GetNode(int start)
{
	//���startƫ���棬��Ӻ������
	Node* cur = nullptr;
	if (start > m_count / 2)
	{
		cur = m_tail->next;
		for (int i = m_count - 1; i > start; i--, cur = cur->pre);  //������start���λ��
	}
	else
	{
		cur = m_head->next;
		for (int i = 0; i < start; i++, cur = cur->next);  //������start���λ��
	}
	return cur;
}

/***************private function end*****************/

/*
* function			��ȡ�ַ�����С
* return   int      �����ַ�����С
*/
int String::Size()
{
	return m_count;
}

/*
* function			��ȡ�ַ����ֽ���
* return   int      �����ַ����ֽ���
*/
int String::Bytes()
{
	return _cbytes(GetStringFromNodes(GetNodes(0, m_count), m_count));
}

/*
* function			�Ƿ�Ϊ��
* return   bool     �շ���true
*/
bool String::IsEmpty()
{
	return m_count ? false : true;
}

/*
* function			���һ���ַ���ǰ��
* param    ch		�ַ�
* return		    ��
*/
void String::PushFront(int ch)
{
	Node* node = CreateNode(ch);			//����һ���ڵ�
	if (IsEmpty())					//�������Ϊ�գ���һ����ӵ�ʱ�򣬾���βָ��ָ���һ����ӵĽڵ�
	{
		m_tail->next = node;        //���� head->NULL,��������˸�node1,��node1->NULL,head->node1,�Ȱ�����������
		node->next = m_head->next;  //Ȼ��node1->head
		m_head->next = node;
		node->pre = m_head;
	}
	else
	{
		node->next = m_head->next;     //���� head->node1,��������˸�node2,��node2->node1,head->node2,�Ȱ�����������
		m_head->next = node;           //Ȼ��node1 -> node2,node2->head
		node->next->pre = node;
		node->pre = m_head;
	}
	m_count++;
}

/*
* function			���һ���ַ������
* param    ch		�ַ�
* return		    ��
*/
void String::PushRear(int ch)
{
	Node* node = CreateNode(ch);
	if (IsEmpty())
		PushFront(ch);
	else
	{
		m_tail->next->next = node;  //tail.next��ʾ���һ���ڵ㣬���������˼�ǣ������һ���ڵ�ָ����������Ľڵ�
		node->pre = m_tail->next;   //��������Ľڵ��ǰ��ָ��ԭ�������һ���ڵ�
		m_tail->next = node;        //�޸�tail��ָ��
		m_count++;
	}
}

/*
* function			����ַ�����ǰ��
* param    s		�ַ���
* return		    ��
*/
void String::PushFront(char* s)
{
	if (s)
		Insert(0, s);
}

/*
* function			����ַ��������
* param    s		�ַ���
* return		    ��
*/
void String::PushRear(char* s)
{
	if (s)
		Insert(m_count, s);
}

/*
* function			ɾ�����n���ַ�
* param    n		ɾ���ַ��ĸ���
* return		    ��
*/
void String::PopRear(int n)
{
	DeleteSub(m_count - n, m_count - 1);
}

/*
* function			ɾ��ǰ��n���ַ�
* param    n		ɾ���ַ��ĸ���
* return		    ��
*/
void String::PopFront(int n)
{
	DeleteSub(0, n - 1);
}

/*
* function			ɾ��ָ��λ���ַ�
* param    local	ɾ����λ��
* return		    ɾ��ʧ�ܷ���-1
*/
int String::Delete(int local)
{
	if (IsEmpty())
		return -1;
	if (local < 0 || local > m_count - 1)
		return -1;
	FreeNode(local, 1);  //ֻҪ�ͷ�Ҫɾ���Ľڵ㼴�ɣ����ӹ����Ѿ���װ����
	return 1;
}

/*
* function			ɾ���Ӵ�
* param    start	ɾ������ʼλ��
* param    end		ɾ�����յ�λ��
* return		    ɾ��ʧ�ܷ���-1
*/
int String::DeleteSub(int start, int end)
{
	if (IsEmpty())
		return -1;
	if (start < 0 || start > m_count - 1 || end < 0 ||
		end >  m_count - 1 || end < start)
		return -1;
	int len = end - start + 1;
	FreeNode(start, len);  //ֻҪ�ͷ�Ҫɾ���Ľڵ㼴�ɣ����ӹ����Ѿ���װ����
	return len;
}

/*
* function			ɾ���Ӵ�
* param    start	ɾ������ʼλ��
* param    len		Ҫɾ���ĳ���
* return		    ɾ��ʧ�ܷ���-1
*/
int String::DeleteSubLen(int start, int len)
{
	if (IsEmpty())
		return -1;
	if (start < 0 || start > m_count - 1 || start + len > m_count)
		return -1;
	FreeNode(start, len);
	return len;
}

/*
* function			��ȡ�Ӵ�
* param    start	��ȡ����ʼλ��
* param    end		��ȡ���յ�λ��
* return		    ��ȡʧ�ܷ���nullptr
*/
char* String::SubString(int start, int end)
{
	if (IsEmpty())
		return NULL;
	if (start < 0 || start > m_count - 1 || end < 0 ||
		end >  m_count - 1 || end < start)
		return NULL;
	int len = end - start + 1;
	Node* nodes = GetNodes(start, len);		//��ȡҪ��ȡ�Ľڵ�
	return GetStringFromNodes(nodes, len);
}

/*
* function			��ȡ�Ӵ�
* param    start	��ȡ����ʼλ��
* param    len		��ȡ�ĳ���
* return		    ��ȡʧ�ܷ���nullptr
*/
char* String::SubStringLen(int start, int len)
{
	if (IsEmpty())
		return NULL;
	if (start < 0 || start > m_count - 1 || start + len > m_count)
		return NULL;
	Node* nodes = GetNodes(start, len);    //��ȡҪ��ȡ�Ľڵ�
	return GetStringFromNodes(nodes, len);
}

/*
* function			�滻�ַ�  (խ�ַ��滻խ�ַ�)
* param    s		�滻��Դ�ַ�
* param    d		�滻����ַ�
* return		    �滻ʧ�ܷ���-1
*/
int String::Replace(int s, int d)
{
	if (IsEmpty()) return -1;
	Node* cur = m_head->next;
	int count = 0;
	for (int i = 0; i <m_count; i++, cur = cur->next)
	{
		if (s > 255)  //�����ַ�
		{
			if (cur->w == s)
			{
				if (d > 255)  //Ҫ�滻��Ҳ�������ַ�
					cur->w = d, ++count;
				else
					cur->c = d, cur->w = 0, ++count;
			}
		}
		else
		{
			if (cur->c == s)
			{
				if (d > 255)  //Ҫ�滻���������ַ�
					cur->w = d, cur->c = 0, ++count;
				else
					cur->c = d, ++count;
			}
		}
	}
	return count;
}

/*
* function			�滻�ַ�(խ�ַ�)
* param    local	�滻��λ��
* param    d		�滻����ַ�
* return		    �滻ʧ�ܷ���-1
*/
int String::ReplaceLocal(int local, int d)
{
	if (IsEmpty()) return -1;
	if (local <0 || local > m_count - 1)return -1;
	Node* cur = GetNode(local);
	if (d > 255)
		cur->w = d;
	else
		cur->c = d;
	return 1;
}

/*
* function			�滻�Ӵ�
* param    s		�滻��Դ��
* param    d		�滻��Ŀ�괮
* return		    �滻ʧ�ܷ���-1
*/
int String::Replace(char* s, char* d)
{
	Node* cur = m_head->next;
	int lens = _csize(s);
	int lend = _csize(d);
	int lensBytes = _cbytes(s);
	int j = 0;
	int count = 0;
	for (int i = 0; i < m_count; i++, cur = cur->next)
	{
		Node* temp = cur;
		for (j = 0; j < lensBytes; j++, temp = temp->next)
		{
			if (i + lens > m_count)
				break;
			if ((int)s[j] < 0)  //���������ַ�
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == lensBytes)  //����ҵ��˾��滻
		{
			//  ����Ҳ���������
			//1.lens  == lend ֱ�Ӹ��Ǽ���
			if (lens == lend)
			{
				cur = Replace(i, d);
				i += lens - 1;  // - 1�ǵ���i++
			}

			//2.lens < lend �ȸ���lens�����ȣ�֮��ʣ�µĲ����ȥ 
			if (lens < lend)
			{
				int lendBytes = _cbytes(d);
				int cb = 0;
				char* buf = new char[lendBytes];
				InitBuf(buf, 0, lendBytes);
				int j = 0;
				for (int k = 0; k < lens; k++, j++)  //��lend��ǰlens���ַ���ȡ����
				{
					if ((int)d[j] < 0)
						sprintf(buf, "%s%c%c", buf, d[j], d[j + 1]), j++;
					else
						buf[j] = d[j];
				}
				cur = Replace(i, buf);
				InitBuf(buf, 0, lendBytes);
				for (int k = j; k < lendBytes; k++)  //��lend��ʣ�µ��ַ���ȡ����
				{
					if ((int)d[k] < 0)
						sprintf(buf, "%s%c%c", buf, d[k], d[k + 1]), k++;
					else
						sprintf(buf, "%s%c", buf, d[k]);
				}
				Insert(i + lens, buf);  //��ʣ�µ��ַ�����
				for (int k = 0; k < lend - lens; k++, cur = cur->next);  //�ǵ������ƶ�
				i += lend - 1;
			}

			//3.lens > lend �ȸ���lend�����ȣ�֮��ɾ��ʣ�µĳ���
			if (lens > lend)
			{
				cur = Replace(i, d);        //�ȸ��ǣ���ɾ��
				DeleteSubLen(i + lend, lens - lend);
				i += lend - 1;
			}
			count++;
		}
	}
	return count;
}

/*
* function			�滻�Ӵ�
* param    local	�滻����ʼλ��
* param    d		�滻��Ŀ�괮
* return		    �滻ʧ�ܷ���nullptr
*/
String::Node* String::Replace(int local, char* d)
{
	if (IsEmpty())
		return NULL;
	Node* cur = GetNode(local);
	int len = _cbytes(d);
	for (int i = 0; i < len; i++, cur = cur->next)
	{
		if ((int)d[i] < 0)  //���������ַ�
		{
			if (!cur)                   //����滻���ַ��������˵�ǰ�ķ�Χ����ֱ�Ӳ��뵽����
			{
				PushRear(CToW(d[i], d[i + 1]));
				cur = m_tail->next;   //����Ҫ��cur��ָ���޸�Ϊ���һ���ڵ㣬�����ٴ�ѭ����curΪNULL�������
			}
			else
			{
				cur->w = CToW(d[i], d[i + 1]);
				cur->c = 0;
			}
			i++;
		}
		else
		{
			if (!cur)                   //����滻���ַ��������˵�ǰ�ķ�Χ����ֱ�Ӳ��뵽����
			{
				PushRear(d[i]);
				cur = m_tail->next;
			}
			else
				cur->c = d[i], cur->w = 0;
		}
	}
	return cur->pre;
}

/*
* function			�����ַ���һ�γ��ֵ�λ��
* param    ch		Ҫ���ҵ��ַ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindFirst(int ch)
{
	Node* cur = m_head->next;
	for (int i = 0; i < m_count; i++, cur = cur->next)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				return i;
		}
		else
		{
			if (cur->c == (char)ch)
				return i;
		}
	}
	return -1;
}

/*
* function			�����ַ����һ�γ��ֵ�λ��
* param    ch		Ҫ���ҵ��ַ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindLast(int ch)
{
	Node* cur = m_tail->next;
	for (int i = m_count - 1; i >= 0; i--, cur = cur->pre)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				return i;
		}
		else
		{
			if (cur->c == (char)ch)
				return i;
		}
	}
	return -1;
}

/*
* function			������ʼλ�ò����ַ����ֵ�λ��
* param    ch		Ҫ���ҵ��ַ�
* param    start	��ʼλ��
* return		    ����ʧ�ܷ���-1
*/
int String::Find(int ch, int start)
{
	if (start < 0 || start > m_count - 1)
		return -1;
	Node* cur = GetNode(start);
	for (int i = start; i < m_count; i++, cur = cur->next)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				return i;
		}
		else
		{
			if (cur->c == (char)ch)
				return i;
		}
	}
	return -1;
}

/*
* function			�����Ӵ���һ�γ��ֵ�λ��
* param    s		Ҫ���ҵ��Ӵ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindFirst(char* s)
{
	Node* cur = m_head->next;
	int j = 0;
	int len = _cbytes(s);
	for (int i = 0; i < m_count; i++, cur = cur->next)
	{
		Node* temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)s[j] < 0)  //���������ַ�
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			�����Ӵ����һ�γ��ֵ�λ��
* param    s		Ҫ���ҵ��Ӵ�
* return		    ����ʧ�ܷ���-1
*/
int String::FindLast(char* s)
{
	int j = 0;
	int len = _cbytes(s);
	Node* cur = GetNode(m_count - _csize(s));   //������m_count - �ַ������ȵ�λ�ã����������ٱȼ���
	for (int i = 0; i < m_count; i++, cur = cur->pre)
	{
		Node* temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)s[j] < 0)  //���������ַ�
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			�����Ӵ����ֵ�λ��
* param    s		Ҫ���ҵ��Ӵ�
* param    start	��ʼλ��
* return		    ����ʧ�ܷ���-1
*/
int String::Find(char* s, int start)
{
	Node* cur = GetNode(start);
	int j = 0;
	int len = _cbytes(s);
	int lens = _csize(s);
	for (int i = start; i < m_count - lens + 1; i++, cur = cur->next)
	{
		Node* temp = cur;
		for (j = 0; j < len; j++, temp = temp->next)
		{
			if ((int)s[j] < 0)  //���������ַ�
			{
				if (temp->w != CToW(s[j], s[j + 1]))
					break;
				j++;
			}
			else
			{
				if (temp->c != s[j])
					break;
			}
		}
		if (j == len)
			return i;
	}
	return -1;
}

/*
* function			�����ַ�
* param    local    Ҫ�����λ��
* param    ch		Ҫ������ַ�
* param    n		Ҫ����ĸ���
* return		    ��
*/
void String::Insert(int local, int ch, int n)
{
	local = local < 0 ? 0 : local > m_count ? m_count : local;
	if (IsEmpty() || local == m_count)    //����ǿյģ���ֱ��ȫ��β��Ӽ���,���߲����λ�������һ��
	{
		for (int i = 0; i < n; i++)
			PushRear(ch);
	}
	else
	{
		Node* cur = GetNode(local)->pre;
		for (int i = 0; i < n; i++)
		{
			Node* node = CreateNode(ch);  //����ԭ�� A->C
			node->next = cur->next;     //���������� A->B->C
			cur->next = node;
			node->next->pre = node;     //����������A<-B<-C
			node->pre = cur;
		}
		m_count += n;
	}
}

/*
* function			�����ַ���
* param    local    Ҫ�����λ��
* param    s		Ҫ������ַ���
* param    n		Ҫ����ĸ���
* return		    ��
*/
void String::Insert(int local, char* s, int n)
{
	local = local < 0 ? 0 : local > m_count ? m_count : local;
	if (IsEmpty() || local == m_count)    //����ǿյģ���ֱ��ȫ��β��Ӽ���,���߲����λ�������һ��
	{
		int len = _cbytes(s);
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < len; j++)
			{
				if ((int)s[j] < 0)  //���������ַ�
					PushRear(CToW(s[j], s[j + 1])), j++;
				else
					PushRear(s[j]);
			}
		}
	}
	else
	{
		Node* cur = GetNode(local);
		for (int i = 0; i < n; i++)
		{
			int len = _cbytes(s);
			for (int j = 0; j < len; j++)   //ѭ������
			{
				Node* node = NULL;
				if ((int)s[j] < 0)  //���������ַ�
					node = CreateNode(CToW(s[j], s[j + 1])), j++;
				else
					node = CreateNode(s[j]);
				node->next = cur->next;
				cur->next = node;
				node->next->pre = node;
				node->pre = cur;
				cur = node;
			}
		}
		m_count += _csize(s) * n;
	}
}

/*
* function			ͳ���ַ����ֹ��Ĵ���
* param    ch		Ҫ���ҵ��ַ�
* return		    �����ַ����ֵĴ���
*/
int String::AppearTimes(int ch)
{
	Node* cur = m_head->next;
	int count = 0;
	while (cur)
	{
		if (ch > 255)
		{
			if (cur->w == (wchar_t)ch)
				++count;
		}
		else
		{
			if (cur->c == (char)ch)
				++count;
		}
		cur = cur->next;
	}
	return count;
}

/*
* function			ͳ���Ӵ����ֹ��Ĵ���
* param    s		Ҫ���ҵ��Ӵ�
* return		    �����ַ����ֵĴ���
*/
int String::AppearTimes(char* s)
{
	Node* cur = m_head;
	int count = 0;
	int len = _cbytes(s);
	int i = 0;
	while (cur->next)
	{
		Node* temp = cur;
		for (i = 0; i < len; i++, temp = temp->next)
		{
			if ((int)s[i] < 0)   //���������ַ�
			{
				if (temp->w != CToW(s[i], s[i + 1]))
					break;
				i++;   //�����i++����Ϊ�����ַ�ռ�����ֽڣ�����������һ���ֽ�
			}
			else
			{
				if (temp->c != s[i])
					break;
			}
		}
		if (i == len)
			count++;
		cur = cur->next;
	}
	return count;
}

/*
* function			�Ƚ�����String�Ƿ����
* param   s1		�ַ���1
* param   s2		�ַ���2
* return		    ��ȷ���true
*/
bool String::Equal(String& s)
{
	if (Size() != s.Size())
		return false;
	Node* cur1 = m_head->next;
	Node* cur2 = s.m_head->next;
	int i = 0;
	for (; i < m_count; i++, cur1 = cur1->next, cur2 = cur2->next)
	{
		if (cur1->c != cur2->c  && cur1->c != 0)
			break;
		else if (cur1->w != cur2->w  && cur1->w != 0)
			break;
	}
	if (i == m_count)
		return true;
	else
		return false;
}

/*
* function			�Ƚ�����char*�Ƿ����
* param   s1		�ַ���1
* param   s2		�ַ���2
* return		    ��ȷ���true
*/
bool String::Equal(const char* s)
{
	char* s1 = GetString();
	int len1 = _cbytes(s1);
	int len2 = _cbytes((char*)s);
	if (len1 != len2)
		return false;
	else
	{
		for (int i = 0; i < len1; i++)
		{
			if (s1[i] != s[i])
				return false;
		}
	}
	return true;
}

/*
* function			��ȡ�ַ���
* return		    ����data
*/
char* String::GetString()
{
	return  GetStringFromNodes(GetNodes(0, m_count), m_count);
}

/*
* function			��ӡ�ַ���
* param    start    ��ʼλ��
* param    end      �յ�λ��
* return		    ��
*/
void String::Print(int start, int end)
{
	if (IsEmpty())  //��ֹ���ÿ�ָ��
		return;
	start = start<0 || start > m_count - 1 ? 0 : start;		//��ֹԽ��
	end = end<0 || end > m_count - 1 ? m_count : end;	//��ֹԽ��
	if (end < start)											//��ֹ����
	{
		int temp = 0;
		temp = start;
		start = end;
		end = start;
	}
	setlocale(LC_ALL, "chs");			//����һ����ʾ����
	Node* cur = GetNode(start);
	for (int i = start; i < end; i++, cur = cur->next)
	{
		if (cur->c != 0)
			cout << cur->c;
		else
			wcout << cur->w;
	}
	cout << endl;
}

/*
* function			����ַ���
* return		    ��
*/
void String::Clear()
{
	FreeNode(0, m_count);
}

/*
* function			��ת�ַ���
* return		    ��
*/
void String::Reverse()
{
	Node* head = m_head->next;
	Node* tail = m_tail->next;
	int temp1;
	int temp2;  //���۽���ֵ
	for (int i = 0; i < m_count / 2; i++, head = head->next, tail = tail->pre)
	{
		temp1 = head->c, temp2 = head->w;
		head->c = tail->c, head->w = tail->w;
		tail->c = temp1, tail->w = temp2;
	}
}

/*
* function			�����ַ���
* return		    ��
*/
void String::ConCat(char* s)
{
	PushRear(s);
}

/*
* function			�����ַ���
* return		    ��
*/
void String::ConCat(String& s)
{
	PushRear(s.GetString());
}

/*
* function			��ֵ
* param    s        char*
* return		    ��
*/
void String::Assign(char* s)
{
	Clear();     //��ֵ�������Ǹ���ԭ����ֵ����������Ҫ������ַ���
	PushRear(s);
}

/*
* function			��ֵ
* param    s        String
* return		    ��
*/
void String::Assign(String& s)
{
	if (this != &s)   //��ֹ�Լ����Լ���ֵ��Clear���Լ�
	{
		Clear();     //��ֵ�������Ǹ���ԭ����ֵ����������Ҫ������ַ���
		PushRear(s.GetString());
	}
}

/*
* function			��ȡָ��λ�õ�ֵ
* param    s        String
* return		    ���ظ�λ�õ��ַ�
*/
int String::GetAt(int iPos)
{
	Node* node = GetNode(iPos);
	return node->c ? node->c : node->w;
}

/*
* function			����+�������
* param    s        String
* return		    String��
*/
String& String::operator +(String& s)
{
	ConCat(s);
	return *this;
}

/*
* function			����+�������
* param    s        char*
* return		    ��
*/
String& String::operator +(char* s)
{
	ConCat(s);
	return *this;
}

/*
* function			����=�������
* param    s        String
* return		    String��
*/
String& String::operator =(String& s)
{
	Assign(s);
	return *this;
}

/*
* function			����=�������
* param    s        char*
* return		    ��
*/
String& String::operator =(char* s)
{
	Assign(s);
	return *this;
}

/*
* function			����+=�������
* param    s        String
* return		    String��
*/
String& String::operator +=(String& s)
{
	ConCat(s);
	Assign(*this);
	return *this;
}

/*
* function			����+=�������
* param    s        char*
* return		    ��
*/
String& String::operator +=(char* s)
{
	ConCat(s);
	Assign(*this);
	return *this;
}

/*
* function			����[]�����
* param    iPos     Ԫ��λ��
* return		    ���ظ��ַ�
*/
int String::operator [](int iPos)
{
	return GetAt(iPos);
}#pragma once
