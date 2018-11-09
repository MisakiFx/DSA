#include <iostream>
#include <cassert>
//#include <fibonacci>
#define DEFAULT_CAPACITY 3//定义默认容量大小 
using namespace std;
typedef int Rank;//秩
template <class T>
struct Increase
{
	virtual void operator () (T & e) 
	{
		e++;
	}
};
template <class T>
class Vector
{
	private:
		Rank _size;//规模 
		int _capacity;//容量 
		T* _elem;//大小 
	public:
		Vector(int c = DEFAULT_CAPACITY)//构造函数 
		{
			_elem = new T[_capacity = c];//构造数据空间,地址给_elem 
			_size = 0;//大小为0 
		}
		Vector(T const * A, Rank lo, Rank hi)//复制构造函数，区间复制
		{
			copyFrom(A, lo, hi);
		}
		Vector(Vector<T> const &V, Rank lo, Rank hi)//赋值构造函数，复制相同的类的对象的区间 
		{
			copyFrom(V._elem, lo, hi);
		}
		Vector(Vector<T> const &V)
		{
			copyFrom(V._elem, 0, V._size);
		}
		~Vector()
		{
			delete[] _elem;//释放内部空间 
		}
		void copyFrom(T* const A, Rank lo, Rank hi); //区间复制函数 
		void expand();//扩容函数 
		T & operator [] (Rank r) const;//循秩访问函数
		Rank insert(Rank r, T const & e);//插入算法
		int remove(Rank lo, Rank hi);//删除区间[lo,hi) 
		T remove(Rank r);//单元素删除 
		Rank find(T const & e, Rank lo, Rank hi) const;//查找
		int deduplicate();//唯一化
		void traverse(void (*visit)(T&));//遍历1（函数指针）
		template <class VST> 
		void traverse(VST &visit);//遍历2（函数对象）
		int disordered() const;//判断逆序程度（有多少逆序对）
		void sort(Rank lo, Rank hi);//排序
		void selectionSort(Rank lo, Rank hi);//选择排序
		void bubbleSortA(Rank lo, Rank hi);//冒泡排序外部接口(复杂版)O(n^1.5)
		bool bubbleA(Rank lo, Rank hi);//冒泡排序单趟扫描（复杂版）O(n^1.5)
		void bubbleSortB(Rank lo, Rank hi);//冒泡排序外部接口（改进版）O(n)
		Rank bubbleB(Rank lo, Rank hi);//冒泡排序单趟扫描（改进版）O(n)
		void mergeSort(Rank lo, Rank hi);//归并排序外部接口
		void merge(Rank lo, Rank mi, Rank hi);//二路归并基本实现 
		int uniquify1();//唯一化（有序向量）（低效版本） O(n^2)
		int uniquify2();//唯一化（有序向量）（高效版本） O(n)
		Rank search(T const &e, Rank lo, Rank hi) const;//查找算法统一接口
		int size()//返回元素个数 
		{
			return _size;
		} 
}; 
/*有序查找语义要求：
	1、不大于e的最后一个元素的秩
	2、若e小于所有元素则返回左侧哨兵
	3、若e大于所有元素则返回右侧哨兵的左邻
*/
template <class T>
static Rank binSearchA(T* A, T const &e, Rank lo, Rank hi)//二分查找版本一 
{//时间复杂度为O(1.5*logn)系数为1.5还有空间改进 
	while(lo < hi)
	{
		Rank mi = (lo + hi) >> 1;
		if(e < A[mi])
		{
			hi = mi;
		}
		else if(A[mi] < e)
		{
			lo = mi + 1;
		}
		else 
		{
			return mi;
		}
	}
	return -1;//查找失败 
}
template <class T>
static Rank binSearchB(T* A, T const &e, Rank lo, Rank hi)//二分查找版本二
//舍弃对中点的判断，使得比较更少，从而改进时间，但是不能立刻判断是否查找到了 
{
	while(1 < hi - lo)//只有到区间长度缩减到1时，才会停止算法
	{
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;//得到深入区间 
	}
	return (e == A[lo]) ? A[lo] : -1;//返回命中元素或者-1 
}
 template <class T>//在版本B的基础上改进使其符合语义 （完美的二分查找） 
 static Rank binSearchC(T *A, T const &e, Rank lo, Rank hi)
 {
 	while(lo < hi)
 	{
 		Rank mi = (lo + hi) >> 1;
 		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}//出口时，A[lo == hi]为大于e的最小元素
	return --lo;//即返回了不大于e的元素的最大秩 
 }
/*我没有现成的斐波那契类，这个我就看看，操啊，没有啊 
//改进为斐波那契查找能稍微改进系数，但还是不够 
template <class T>
static Rank fibSearch(T* A, T const &e, Rank lo, Rank hi)
{
	Fib fib(hi - lo);
	while(lo < hi)
	{
		while(hi - lo < fib.get())
		{
			fib.prev();
		}
		Rank mi = lo + fib.get() - 1;//按黄金比例分割
		if(e < A[mi])
		{
			hi = mi;//深入前半段 
		}
		else if(A[mi] < e)
		{
			lo = mi + 1;//深入后半段 
		}
		else
		{
			return mi;//命中 
		} 
	}
	return -1;//失败 
}
*/
template <class T>
void Vector<T>::copyFrom(T* const A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];//分配空间
	_size = 0;//规模清零
	while(lo < hi)
	{
		_elem[_size++] = A[lo++];//复制至_elem[0,hi-lo) 
	} 
} 
template <class T>
void Vector<T>::expand()
{
	if(_size < _capacity)
	{
		return;
	}
	_capacity = max(_capacity, DEFAULT_CAPACITY);//不低于最小容量
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//容量加倍
	for(int i = 0; i > _size; i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;//释放原空间 
}
template <class T>//0 <= r < _size
T & Vector<T>::operator [] (Rank r) const
{
	assert(r >=0 && r < _size);
	return _elem[r];
}
template <class T>
Rank Vector<T>::insert(Rank r, T const & e)
{
	expand();//有必要时扩容 
	for(int i = _size; i > r; i--)//自后向前 
	{
		_elem[i] = _elem[i - 1];//后继元素前移 
	}
	_elem[r] = e;//置入新元素 
	_size++;//更新容量 
	return r;//返回秩 
}
template <class T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	assert(lo >= 0 && lo <= hi && hi <= _size);
	if(lo == hi)
	{
		return 0;//处于效率考虑单独处理退化情况 
	}
	while(hi < _size)
	{
		_elem[lo++] = _elem[hi++];//[hi, _size)一次前移hi - lo位 
	}
	_size = lo;//更新规模 
	//shrink();//有必要时缩容
	return hi - lo;//返回被删除元素的数目 
}
template <class T>
T Vector<T>::remove(Rank r)
{
	assert(r >= 0 && r < _size);
	T e = _elem[r];//备份 
	remove(r, r + 1);//调用区间删除算法
	return e;//返回被删除元素 
}
template <class T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
	while((lo < hi--) && (e != _elem[hi]))//逆序是为了在命中多个元素时返回秩最大者 
	{
		
	}
	return hi;//如果失败返回lo - 1这个秩 
}
template <class T>
int Vector<T>::deduplicate()
{
	int oldSize = _size;//记录原规模
	Rank i = 1;
	while(i < _size)
	{
		(find(_elem, 0, i) < 0) ? i++ : remove(i);//若无雷同则考虑后继，若有雷同删除雷同 
	} 
	return oldSize - _size;//返回向量规模变化 
}
template <class T>
void Vector<T>::traverse(void (*visit)(T&))
{
	for(int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}
template <class T> 
template <class VST>
void Vector<T>::traverse(VST &visit)
{
	for(int i = 0; i < _size; i++)
	{
		visit(_elem[i]);
	}
}
template <class T>
void increase(Vector<T> & v)//通过构建外部函数模版达到遍历某个对象实现对应函数功能的目的 
{
	v.traverse(Increase<T>());//构建临时无名对象传入，用于函数对象 
}
template <class T>
int Vector<T>::disordered() const
{
	int n = 0; //计数器
	for(int i = 1; i < _size; i++)//从第二号元素开始 
	{
		n += (_elem[i - 1] > _elem[i]);//逆序则计数 
	}
	return n; //返回多少逆序对 
} 
template <class T>
int Vector<T>::uniquify1()
{
	int oldSize = _size;//记录原始大小
	int i = 0;//从首元素开始
	while(i < _size - 1)
	{
		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;//相同移除后者，不同转至后一元素 
	}
	return oldSize - _size;//向量规模变化量返回 
}//_size的缩小由remove()完成 
template <class T>
int Vector<T>::uniquify2()
{
	Rank i = 0, j = 0;//各对互异“相邻”元素的秩 
	while(++j < _size)//逐一扫描，直至末元素 
	{
		//跳过雷同者；发现不同元素时。向前移至紧邻于前者右侧
		if(_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		} 
	}
	_size = ++i;
	//shrink();//截除尾部多余元素
	return j - i;//返回删除的元素个数 
}//批量删除仍然不能达到高效 
template <class T>
Rank Vector<T>::search(T const & e, Rank lo, Rank hi) const
{
	//随机使用二分查找或Fibonacci算法 
	return (rand() % 2) ? binSearchC(_elem, e, lo, hi) : fibSearch(_elem, e, lo , hi); 
}
template <class T>
void Vector<T>::selectionSort(Rank lo, Rank hi)//选择排序复杂版 
{
	int i = 0;
	while(i < _size - 1)
	{
		int minIndex = i;
		int j = i + 1;
		while(j < _size)
		{
			if(_elem[j] < _elem[minIndex])
			{
				minIndex = j;
			}
		}
		if(minIndex != i)
		{
			int temp = _elem[i];
			_elem[i] = _elem[minIndex];
			_elem[minIndex] = temp;
		}
	}
} 
template <class T>
void Vector<T>::bubbleSortA(Rank lo, Rank hi)
{
	while(!bubbleA(lo, hi--));//逐躺扫描交换，直至全序 
}
template <class T>
bool Vector<T>::bubbleA(Rank lo, Rank hi)
{
	bool sorted = true;//整体有序标志
	while(++lo < hi)
	{
		if(_elem[lo - 1] > _elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);//交换 
		}
	}
	return sorted; //判断当前轮扫描是否已经不需要交换，则已经有序 
}
template <class T>
void Vector<T>::bubbleSortB(Rank lo, Rank hi)
{
	while(lo < (hi = bubbleB(lo, hi)));//逐躺扫描交换，直至全序 
}
template <class T>
Rank Vector<T>::bubbleB(Rank lo, Rank hi)
{
	Rank last = lo;
	while(++lo < hi)
	{
		if(_elem[lo - 1] > _elem[lo])
		{
			last = lo;//更新最右侧逆序对位置记录 
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return last;//返回最右侧逆序对位置 
}
template <class T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if(hi - lo < 2) return;//单元素区间自然有序 
	int mi = (lo + hi) >> 1;//以中点为界
	mergeSort(lo, mi);//对前半段排序
	mergeSort(mi, hi);//对后半段排序
	merge(lo, mi, hi);//归并 
} 
template <class T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;//合并后的向量A[0, hi - lo) = _elem[lo, mi)
	int lb = mi - lo;//前子向量元素个数 
	T* B = new T[lb];//前子向量B[0,lb) = _elem[lo, mi)
	for(Rank i = 0; i < lb; B[i] = A[i++]);//复制前子向量B
	int lc = hi - mi;//后子向量元素个数 
	T* C = _elem + mi;//后子向量C[0, lc) = _elem[mi, hi)
	for(Rank i = 0, j = 0, k = 0;j < lb;)//B[j]和C[k]中小者转至A中 
	{//B一旦提前耗尽循环直接终止 
		if((k < lc) && (C[k] < B[j]))
		{
			A[i++] = C[k++];//B[k]已无或更大 
		}
		if(lc <= k || (B[j] <= C[k]))
		{
			A[i++] = B[j++];//C[k]已无或不小 
		}
	}
	delete[] B;//释放空间 
	 
}
template <class T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch(rand() % 5)
	{
		case 1:
			bubbleSortB(lo, hi);//冒泡 
			break;
		case 2:
			selectionSort(lo, hi);//选择 
			break;
		case 3:
			mergeSort(lo, hi);//归并 
			break;
	}
}
int main()
{
	
}
