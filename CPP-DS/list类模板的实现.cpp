#include <iostream>
#include <cassert>
#define Posi(T) ListNode<T>*
using namespace std;
typedef int Rank;
template <class T>
struct ListNode//��������ȫ���Ŷ����ٷ�װ 
{
	//�б�ڵ�ģ���ࣨ��˫������ʵ�֣�
	T data;
	Posi(T) pred;//ǰ��
	Posi(T) succ;//���
	ListNode()//���캯�� 
	{
		
	}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL) : data(e), pred(p), succ(s)//Ĭ�Ϲ����� 
	{
		
	}
	Posi(T) insertAsPred(T const &e);//ǰ����
	Posi(T) insertAsSucc(T const &e);//����� 
};
template <class T>
class List
{
	private:
		int _size;//��ģ
		Posi(T) header;//ͷ 
		Posi(T) trailer;//β
	protected:/*�ڲ�����*/
		void init();//��ʼ��
		void copyNodes(Posi(T) p, int n);//�����б� 
	public:/*�ⲿ�ӿ�*/
		List()//Ĭ�Ϲ��� 
		{
			init();
		}
		~List();//���� 
		T operator [] (Rank r) const;//ѭ�ȷ��� 
		Posi(T) first() const;//�����׽ڵ�
		Posi(T) find(T const &e, int n, Posi(T) p) const;//��������˳�����
		Posi(T) insertBefore(Posi(T) p, T const &e);//e����p��ǰ������
		Posi(T) insertAfter(Posi(T) p, T const &e);//e��Ϊp�ĺ�̲���
		Posi(T) insertAsLast(T const &e);//e���б�ĩβ����
		Posi(T) insertAsFirst(T const &e);//e���б��׶˲��� 
		T remove(Posi(T) p);//ɾ���ڵ�
		int clear();//����б�
		int deduplicate();//�����б�Ψһ��
		int uniquify();//�����б�Ψһ��
		Posi(T) search(T const &e, int n, Posi(T) p) const;//�����б����
		void selectionSort(Posi(T) p, int n); //ѡ������ 
		Posi(T) selectMax(Posi(T), int n);//����ʼ��λ��p��n��Ԫ�������������
		void insertionSort(Posi(T) p, int n);//�������� 
};
template <class T>
void List<T>::insertionSort(Posi(T) p, int n)
{
	for(int r = 0; r < n; r++)
	{
		insertAfter(search(p->data, r, p), p->data);//����+����
		p = p->succ;//ת����һ�ڵ� 
		remove(p->pred);
	}
} 
template <class T>
Posi(T) List<T>::selectMax(Posi(T) p, int n)
{
	Posi(T) max = p;//������ݶ�Ϊp
	for(Posi(T) cur = p; 1 < n; n--)//������һ��max�Ƚ� 
	{
		if(!lt((cur = cur->succ)->data, max->data))//��>=max
		{
			max = cur;//�������Ԫ��λ�� 
		} 
	}
	return max; 
}
template <class T>
void List<T>::selectionSort(Posi(T) p, int n)
{
	Posi(T) head = p->pred;
	Posi(T) tail = p;//����������(head, tail)
	for(int i = 0; i < n; i++)
	{
		tail = tail->succ;
	}
	while(1 < n)
	{
		//�����Ӵ����������ҳ�����ߣ����ƶ�����������ǰ��
		insertBefore(tail, remove(selectMax(head->succ, n))); 
	}
	tail = tail->pred;
	n--; 
}
template <class T>
Posi(T) List<T>::search(T const &e, int n, Posi(T) p) const
{
	while(0 <= n--)//��һ�β�����Ϊ����û���ҵ�ʱ����ͷ�ڵ� 
	{
		if(((p = p->pred) -> data) <= e)
		{
			break;
		}
	}
	return p;//ֱ�����С���ֵԽ���ΧԽ��󣬷��ز�����ֹ��λ�� 
}
template <class T>
int List<T>::uniquify()
{
	if(_size < 2) return 0;
	int oldSize = _size;//��¼ԭ��ģ
	Posi(T) p = first();//pΪ��������� 
	Posi(T) q; //qΪ�����κ��
	while(trailer != (q = p->succ))
	{
		if(p->data != q->data)
		{
			p = q;//����ת����һ�׶� 
		}
		else
		{
			remove(q);//����ɾ������q 
		}
	}
	return oldSize - _size;//���ع�ģ�仯�� 
}
template <class T>
int List<T>::deduplicate()
{
	if(_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first();
	Rank r = 1;//���׽ڵ㿪ʼ 
	while(trailer != (p = p->succ))//ֱ��ĩ�ڵ� 
	{
		Posi(T) q = find(p->data, r, p);//��p��r��ǰ���У�������֮��ͬ��
		q ? remove(q) : r++;//������ɾ��������������ǰ��+1������ɾ��p 
	}
	return oldSize - _size;//����ɾ��Ԫ�ظ��� 
}
template <class T>
int List<T>::clear()
{
	int oldSize = _size;
	while(0 < _size)//_size��remove�м��� 
	{
		remove(header->succ);//ɾ��Ԫ�� 
	}
	return oldSize;//����ԭ���Ĵ�С��Ҳ��ɾ����Ԫ�ظ��� 
}
template <class T>
List<T>::~List()
{
	clear();//����б�
	delete header;//�ͷ��б�ͷ 
	delete trailer; //�ͷ��б�β 
}
template <class T>
T List<T>::remove(Posi(T) p)
{
	T e = p->data;//���ݴ�ɾ���ڵ���ֵ
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;//�ع�ǰ������ 
	delete p;
	_size--;
	return e;//���ر�����ֵ 
}
template <class T>
Posi(T) List<T>::insertAsFirst(T const&e)
{
	_size++;
	return header->insertAsSucc(e);
}
template <class T>
Posi(T) List<T>::insertAfter(Posi(T) p, T const &e)
{
	_size++;
	return p->insertAsSucc(e);
} 
template <class T>
Posi(T) List<T>::insertAsLast(T const &e)
{
	_size++;
	return trailer->insertAsPred(e);
}
template <class T>
void List<T>::copyNodes(Posi(T) p, int n)
{
	init();//����ͷβ�ڱ����ҳ�ʼ��
	while(n--)//��p��n��������Ϊĩ�ڵ���� 
	{
		insertAsLast(p->data);
		p = p->succ;
	} 
}
template <class T>
void List<T>::init()
{
	header = new ListNode<T>;//����ͷ�ڱ��ڵ� 
	trailer = new ListNode<T>;//����β�ڱ��ڵ�
	header->succ = trailer;
	header->pred = NULL;//����
	trailer->pred = header;
	trailer->succ = NULL;//����
	_size = 0; 
}
template <class T>
T List<T>::operator [] (Rank r) const//���ܳ��� 
{
	assert(_size > 0 && r > 0 && r < _size);
	Posi(T) p = first();
	while (0 < r--)
	{
		p = p->succ;
	}
	return p->data;//Ŀ��ڵ� 
}
template <class T>
Posi(T) List<T>::first() const
{
	if(_size == 0)
	{
		return NULL;
	}
	else
	{
		return header->succ;
	}
}
template <class T>
Posi(T) List<T>::find(T const &e, int n, Posi(T) p) const
{
	while(0 < n--)
	{
		if(e == (p = p->pred)->data)//��p��n��ǰ���н��в��� 
		{
			return p;//ֱ������ 
		}
	}
	return NULL;//Խ��û�ҵ� 
}
template <class T>
Posi(T) List<T>::insertBefore(Posi(T) p, T const &e)
{
	_size++;
	return p->insertAsPred(e);
}
template <class T>
Posi(T) ListNode<T>::insertAsPred(T const &e)
{
	Posi(T) x = new ListNode(e, pred, this);//�����½ڵ㲢�ҽ���ǰ������ 
	pred->succ = x;//������һ�ڵ��������һ�ڵ� 
	pred = x;//������һ�ڵ㽨������ 
	return x;//�����½ڵ� 
}
template <class T>
Posi(T) ListNode<T>::insertAsSucc(T const &e)
{
	Posi(T) x = new ListNode(e, this, succ);
	succ->pred = x;//������һ�ڵ��ǰһ�ڵ� 
	succ = x;//������һ�ڵ� 
	return x;//�����½ڵ� 
}
int main()
{
	
}
