#include <iostream>
#define BinNodePosi(T) BinNode<T>*//�ڵ����� 
#define statue(p) ((p) ? (p)->height : -1);
using namespace std;
template <class T>
struct BinNode
{
	T data;//��ֵ
	BinNodePosi(T) parent;//���ڵ� 
	BinNodePosi(T) lChild;//���� 
	BinNodePosi(T) rChild;//�Һ���
	int height;
	BinNode():parent(NULL), lChild(NULL), rChild(NULL), height(0)//���캯�� 
	{
		
	}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0):parent(p), lChild(lc), rChild(rc), height(h)
	{
		
	}
	int size();//������ģ
	BinNodePosi(T) insertAsLC(T const &);//��Ϊ���Ӳ���
	BinNodePosi(T) insertAsRC(T const &);//��Ϊ�Һ��Ӳ��� 
	BinNodePosi(T) succ();//������������µ�ֱ�Ӻ��
	template <class VST> 
	void travLevel (VST&);//������α��� 
	template <class VST>
	void travPre(VST&);//�����������
	template <class VST>
	void travIn(VST&);//�����������
	template <class VST>
	void travPost(VST&);//������������ 
};
template <class T>
class BinTree
{
	protected:
		int _size;//��ģ
		BinNodePosi(T) _root;//���ڵ�
		virtual int updateHeight(BinNodePosi(T) x);//���½ڵ�x�ĸ߶�
		void updateHeightAbove(BinNodePosi(T) x);//����x�����ȵĸ߶�
	public:
		BinTree() : _size(0), _root(NULL)
		{
	
		}
		~BinTree() 
		{
			if(0 < _size)
			{
				remove(_root);
			}
		}
		int size() const//��ģ
		{
			return _size;
		}
		bool empty() const//�п� 
		{
			return !_root;
		}
		BinNodePosi(T) root() const//���� 
		{
			return _root;
		}
		BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);//����ڵ���Һ��� 
		BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);//����ڵ������  
};
template <class T>
BinNodePosi(T) BinTree<T>::insertAsLC(BinNodePosi(T) x, T const& e)
{
	_size++;
	x->insertAsLC(e);
	updateHeightAbove(x);
	return x->lChild;
}
template <class T>
BinNodePosi(T) BinTree<T>::insertAsRC(BinNodePosi(T) x, T const& e)
{ 
	_size++;
	x->insertAsRC(e);
	updateHeightAbove(x);
	return x->rChild;
}
template <class T>//���Ӳ��� 
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e)
{
	return lChild = new BinNode(e, this);
}
template <class T>//�Һ��Ӳ��� 
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
{
	return rChild = new BinNode(e, this);
}
template <class T>//��ģ(�ݹ�Ƕ��) 
int BinNode<T>::size()
{
	int s = 1;
	if(lChild)
	{
		s += lChild->size();
	}
	if(rChild)
	{
		s += rChild->size();
	}
	return s;
}
template <class T>
int BinTree<T>::updateHeight(BinNodePosi(T) x)
{
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));//�����ĸ߶ȵ���������ĸ��ڵ���������Һ��ӵĸ߶��е����ֵ + 1 
}//�˴������ö��������� 
template <class T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x)//���Ż�������߶Ȳ��伴����ֹ 
	{
		updateHeight(x);
		x = x->parent;
	}
}
template <class T, class VST>
void traverse(BinNodePosi(T) x, VST & visit)
{
	if(!x) return;//����һ�����
	visit(x->data);
	traverse(x->lChild, visit);
	traverse(x->rChild, visit); 
}
int main()
{
	
} 
