#include <iostream>
#include <cassert>
#define Posi(T) ListNode<T>*
using namespace std;
typedef int Rank;
template <class T>
struct ListNode//简介起见完全开放而不再封装 
{
	//列表节点模版类（以双向链表实现）
	T data;
	Posi(T) pred;//前驱
	Posi(T) succ;//后继
	ListNode()//构造函数 
	{
		
	}
	ListNode(T e, Posi(T) p = NULL, Posi(T) s = NULL) : data(e), pred(p), succ(s)//默认构造器 
	{
		
	}
	Posi(T) insertAsPred(T const &e);//前插入
	Posi(T) insertAsSucc(T const &e);//后插入 
};
template <class T>
class List
{
	private:
		int _size;//规模
		Posi(T) header;//头 
		Posi(T) trailer;//尾
	protected:/*内部函数*/
		void init();//初始化
		void copyNodes(Posi(T) p, int n);//复制列表 
	public:/*外部接口*/
		List()//默认构造 
		{
			init();
		}
		~List();//析构 
		T operator [] (Rank r) const;//循秩访问 
		Posi(T) first() const;//返回首节点
		Posi(T) find(T const &e, int n, Posi(T) p) const;//无序链表顺序查找
		Posi(T) insertBefore(Posi(T) p, T const &e);//e当做p的前驱插入
		Posi(T) insertAfter(Posi(T) p, T const &e);//e作为p的后继插入
		Posi(T) insertAsLast(T const &e);//e在列表末尾插入
		Posi(T) insertAsFirst(T const &e);//e在列表首端插入 
		T remove(Posi(T) p);//删除节点
		int clear();//清空列表
		int deduplicate();//无序列表唯一化
		int uniquify();//有序列表唯一化
		Posi(T) search(T const &e, int n, Posi(T) p) const;//有序列表查找
		void selectionSort(Posi(T) p, int n); //选择排序 
		Posi(T) selectMax(Posi(T), int n);//从起始于位置p的n个元素中挑出最大者
		void insertionSort(Posi(T) p, int n);//插入排序 
};
template <class T>
void List<T>::insertionSort(Posi(T) p, int n)
{
	for(int r = 0; r < n; r++)
	{
		insertAfter(search(p->data, r, p), p->data);//查找+插入
		p = p->succ;//转向下一节点 
		remove(p->pred);
	}
} 
template <class T>
Posi(T) List<T>::selectMax(Posi(T) p, int n)
{
	Posi(T) max = p;//最大者暂定为p
	for(Posi(T) cur = p; 1 < n; n--)//后续逐一与max比较 
	{
		if(!lt((cur = cur->succ)->data, max->data))//若>=max
		{
			max = cur;//更新最大元素位置 
		} 
	}
	return max; 
}
template <class T>
void List<T>::selectionSort(Posi(T) p, int n)
{
	Posi(T) head = p->pred;
	Posi(T) tail = p;//待排序区间(head, tail)
	for(int i = 0; i < n; i++)
	{
		tail = tail->succ;
	}
	while(1 < n)
	{
		//反复从待排序区间找出最大者，并移动至有序区间前端
		insertBefore(tail, remove(selectMax(head->succ, n))); 
	}
	tail = tail->pred;
	n--; 
}
template <class T>
Posi(T) List<T>::search(T const &e, int n, Posi(T) p) const
{
	while(0 <= n--)//多一次查找是为了在没有找到时返回头节点 
	{
		if(((p = p->pred) -> data) <= e)
		{
			break;
		}
	}
	return p;//直至命中、数值越界或范围越界后，返回查找终止的位置 
}
template <class T>
int List<T>::uniquify()
{
	if(_size < 2) return 0;
	int oldSize = _size;//记录原规模
	Posi(T) p = first();//p为各区段起点 
	Posi(T) q; //q为各区段后继
	while(trailer != (q = p->succ))
	{
		if(p->data != q->data)
		{
			p = q;//互异转向下一阶段 
		}
		else
		{
			remove(q);//否则删除后者q 
		}
	}
	return oldSize - _size;//返回规模变化量 
}
template <class T>
int List<T>::deduplicate()
{
	if(_size < 2) return 0;
	int oldSize = _size;
	Posi(T) p = first();
	Rank r = 1;//从首节点开始 
	while(trailer != (p = p->succ))//直到末节点 
	{
		Posi(T) q = find(p->data, r, p);//在p的r个前驱中，查找与之雷同者
		q ? remove(q) : r++;//存在则删除它，不存在则前驱+1，不能删除p 
	}
	return oldSize - _size;//返回删除元素个数 
}
template <class T>
int List<T>::clear()
{
	int oldSize = _size;
	while(0 < _size)//_size在remove中减少 
	{
		remove(header->succ);//删除元素 
	}
	return oldSize;//返回原来的大小，也是删除的元素个数 
}
template <class T>
List<T>::~List()
{
	clear();//清空列表
	delete header;//释放列表头 
	delete trailer; //释放列表尾 
}
template <class T>
T List<T>::remove(Posi(T) p)
{
	T e = p->data;//备份待删除节点数值
	p->pred->succ = p->succ;
	p->succ->pred = p->pred;//重构前后连接 
	delete p;
	_size--;
	return e;//返回备份数值 
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
	init();//创建头尾哨兵并且初始化
	while(n--)//将p的n项依次作为末节点插入 
	{
		insertAsLast(p->data);
		p = p->succ;
	} 
}
template <class T>
void List<T>::init()
{
	header = new ListNode<T>;//创建头哨兵节点 
	trailer = new ListNode<T>;//创建尾哨兵节点
	header->succ = trailer;
	header->pred = NULL;//互联
	trailer->pred = header;
	trailer->succ = NULL;//互联
	_size = 0; 
}
template <class T>
T List<T>::operator [] (Rank r) const//不能常用 
{
	assert(_size > 0 && r > 0 && r < _size);
	Posi(T) p = first();
	while (0 < r--)
	{
		p = p->succ;
	}
	return p->data;//目标节点 
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
		if(e == (p = p->pred)->data)//在p的n个前驱中进行查找 
		{
			return p;//直接命中 
		}
	}
	return NULL;//越界没找到 
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
	Posi(T) x = new ListNode(e, pred, this);//创建新节点并且建立前后连接 
	pred->succ = x;//更新上一节点的最新下一节点 
	pred = x;//更新上一节点建立链接 
	return x;//返回新节点 
}
template <class T>
Posi(T) ListNode<T>::insertAsSucc(T const &e)
{
	Posi(T) x = new ListNode(e, this, succ);
	succ->pred = x;//更新下一节点的前一节点 
	succ = x;//更新下一节点 
	return x;//返回新节点 
}
int main()
{
	
}
