#include <iostream>
#define BinNodePosi(T) BinNode<T>*//节点设置 
#define statue(p) ((p) ? (p)->height : -1);
using namespace std;
template <class T>
struct BinNode
{
	T data;//数值
	BinNodePosi(T) parent;//父节点 
	BinNodePosi(T) lChild;//左孩子 
	BinNodePosi(T) rChild;//右孩子
	int height;
	BinNode():parent(NULL), lChild(NULL), rChild(NULL), height(0)//构造函数 
	{
		
	}
	BinNode(T e, BinNodePosi(T) p = NULL, BinNodePosi(T) lc = NULL, BinNodePosi(T) rc = NULL, int h = 0):parent(p), lChild(lc), rChild(rc), height(h)
	{
		
	}
	int size();//子树规模
	BinNodePosi(T) insertAsLC(T const &);//作为左孩子插入
	BinNodePosi(T) insertAsRC(T const &);//作为右孩子插入 
	BinNodePosi(T) succ();//中序遍历意义下的直接后继
	template <class VST> 
	void travLevel (VST&);//子树层次遍历 
	template <class VST>
	void travPre(VST&);//子树先序遍历
	template <class VST>
	void travIn(VST&);//子树中序遍历
	template <class VST>
	void travPost(VST&);//子树后续遍历 
};
template <class T>
class BinTree
{
	protected:
		int _size;//规模
		BinNodePosi(T) _root;//根节点
		virtual int updateHeight(BinNodePosi(T) x);//更新节点x的高度
		void updateHeightAbove(BinNodePosi(T) x);//更新x及祖先的高度
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
		int size() const//规模
		{
			return _size;
		}
		bool empty() const//判空 
		{
			return !_root;
		}
		BinNodePosi(T) root() const//树根 
		{
			return _root;
		}
		BinNodePosi(T) insertAsRC(BinNodePosi(T) x, T const& e);//插入节点的右孩子 
		BinNodePosi(T) insertAsLC(BinNodePosi(T) x, T const& e);//插入节点的左孩子  
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
template <class T>//左孩子插入 
BinNodePosi(T) BinNode<T>::insertAsLC(T const & e)
{
	return lChild = new BinNode(e, this);
}
template <class T>//右孩子插入 
BinNodePosi(T) BinNode<T>::insertAsRC(T const & e)
{
	return rChild = new BinNode(e, this);
}
template <class T>//规模(递归嵌套) 
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
	return x->height = 1 + max(stature(x->lChild), stature(x->rChild));//子树的高度等于这棵树的根节点的左孩子与右孩子的高度中的最大值 + 1 
}//此处常采用二叉树规则 
template <class T>
void BinTree<T>::updateHeightAbove(BinNodePosi(T) x)
{
	while(x)//可优化，如果高度不变即可终止 
	{
		updateHeight(x);
		x = x->parent;
	}
}
template <class T, class VST>
void traverse(BinNodePosi(T) x, VST & visit)
{
	if(!x) return;//处理一般情况
	visit(x->data);
	traverse(x->lChild, visit);
	traverse(x->rChild, visit); 
}
int main()
{
	
} 
