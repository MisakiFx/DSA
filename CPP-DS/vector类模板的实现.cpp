#include <iostream>
#include <cassert>
//#include <fibonacci>
#define DEFAULT_CAPACITY 3//����Ĭ��������С 
using namespace std;
typedef int Rank;//��
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
		Rank _size;//��ģ 
		int _capacity;//���� 
		T* _elem;//��С 
	public:
		Vector(int c = DEFAULT_CAPACITY)//���캯�� 
		{
			_elem = new T[_capacity = c];//�������ݿռ�,��ַ��_elem 
			_size = 0;//��СΪ0 
		}
		Vector(T const * A, Rank lo, Rank hi)//���ƹ��캯�������临��
		{
			copyFrom(A, lo, hi);
		}
		Vector(Vector<T> const &V, Rank lo, Rank hi)//��ֵ���캯����������ͬ����Ķ�������� 
		{
			copyFrom(V._elem, lo, hi);
		}
		Vector(Vector<T> const &V)
		{
			copyFrom(V._elem, 0, V._size);
		}
		~Vector()
		{
			delete[] _elem;//�ͷ��ڲ��ռ� 
		}
		void copyFrom(T* const A, Rank lo, Rank hi); //���临�ƺ��� 
		void expand();//���ݺ��� 
		T & operator [] (Rank r) const;//ѭ�ȷ��ʺ���
		Rank insert(Rank r, T const & e);//�����㷨
		int remove(Rank lo, Rank hi);//ɾ������[lo,hi) 
		T remove(Rank r);//��Ԫ��ɾ�� 
		Rank find(T const & e, Rank lo, Rank hi) const;//����
		int deduplicate();//Ψһ��
		void traverse(void (*visit)(T&));//����1������ָ�룩
		template <class VST> 
		void traverse(VST &visit);//����2����������
		int disordered() const;//�ж�����̶ȣ��ж�������ԣ�
		void sort(Rank lo, Rank hi);//����
		void selectionSort(Rank lo, Rank hi);//ѡ������
		void bubbleSortA(Rank lo, Rank hi);//ð�������ⲿ�ӿ�(���Ӱ�)O(n^1.5)
		bool bubbleA(Rank lo, Rank hi);//ð��������ɨ�裨���Ӱ棩O(n^1.5)
		void bubbleSortB(Rank lo, Rank hi);//ð�������ⲿ�ӿڣ��Ľ��棩O(n)
		Rank bubbleB(Rank lo, Rank hi);//ð��������ɨ�裨�Ľ��棩O(n)
		void mergeSort(Rank lo, Rank hi);//�鲢�����ⲿ�ӿ�
		void merge(Rank lo, Rank mi, Rank hi);//��·�鲢����ʵ�� 
		int uniquify1();//Ψһ������������������Ч�汾�� O(n^2)
		int uniquify2();//Ψһ������������������Ч�汾�� O(n)
		Rank search(T const &e, Rank lo, Rank hi) const;//�����㷨ͳһ�ӿ�
		int size()//����Ԫ�ظ��� 
		{
			return _size;
		} 
}; 
/*�����������Ҫ��
	1��������e�����һ��Ԫ�ص���
	2����eС������Ԫ���򷵻�����ڱ�
	3����e��������Ԫ���򷵻��Ҳ��ڱ�������
*/
template <class T>
static Rank binSearchA(T* A, T const &e, Rank lo, Rank hi)//���ֲ��Ұ汾һ 
{//ʱ�临�Ӷ�ΪO(1.5*logn)ϵ��Ϊ1.5���пռ�Ľ� 
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
	return -1;//����ʧ�� 
}
template <class T>
static Rank binSearchB(T* A, T const &e, Rank lo, Rank hi)//���ֲ��Ұ汾��
//�������е���жϣ�ʹ�ñȽϸ��٣��Ӷ��Ľ�ʱ�䣬���ǲ��������ж��Ƿ���ҵ��� 
{
	while(1 < hi - lo)//ֻ�е����䳤��������1ʱ���Ż�ֹͣ�㷨
	{
		Rank mi = (lo + hi) >> 1;
		(e < A[mi]) ? hi = mi : lo = mi;//�õ��������� 
	}
	return (e == A[lo]) ? A[lo] : -1;//��������Ԫ�ػ���-1 
}
 template <class T>//�ڰ汾B�Ļ����ϸĽ�ʹ��������� �������Ķ��ֲ��ң� 
 static Rank binSearchC(T *A, T const &e, Rank lo, Rank hi)
 {
 	while(lo < hi)
 	{
 		Rank mi = (lo + hi) >> 1;
 		(e < A[mi]) ? hi = mi : lo = mi + 1;
	}//����ʱ��A[lo == hi]Ϊ����e����СԪ��
	return --lo;//�������˲�����e��Ԫ�ص������ 
 }
/*��û���ֳɵ�쳲������࣬����ҾͿ������ٰ���û�а� 
//�Ľ�Ϊ쳲�������������΢�Ľ�ϵ���������ǲ��� 
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
		Rank mi = lo + fib.get() - 1;//���ƽ�����ָ�
		if(e < A[mi])
		{
			hi = mi;//����ǰ��� 
		}
		else if(A[mi] < e)
		{
			lo = mi + 1;//������� 
		}
		else
		{
			return mi;//���� 
		} 
	}
	return -1;//ʧ�� 
}
*/
template <class T>
void Vector<T>::copyFrom(T* const A, Rank lo, Rank hi)
{
	_elem = new T[_capacity = 2 * (hi - lo)];//����ռ�
	_size = 0;//��ģ����
	while(lo < hi)
	{
		_elem[_size++] = A[lo++];//������_elem[0,hi-lo) 
	} 
} 
template <class T>
void Vector<T>::expand()
{
	if(_size < _capacity)
	{
		return;
	}
	_capacity = max(_capacity, DEFAULT_CAPACITY);//��������С����
	T* oldElem = _elem;
	_elem = new T[_capacity <<= 1];//�����ӱ�
	for(int i = 0; i > _size; i++)
	{
		_elem[i] = oldElem[i];
	}
	delete[] oldElem;//�ͷ�ԭ�ռ� 
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
	expand();//�б�Ҫʱ���� 
	for(int i = _size; i > r; i--)//�Ժ���ǰ 
	{
		_elem[i] = _elem[i - 1];//���Ԫ��ǰ�� 
	}
	_elem[r] = e;//������Ԫ�� 
	_size++;//�������� 
	return r;//������ 
}
template <class T>
int Vector<T>::remove(Rank lo, Rank hi)
{
	assert(lo >= 0 && lo <= hi && hi <= _size);
	if(lo == hi)
	{
		return 0;//����Ч�ʿ��ǵ��������˻���� 
	}
	while(hi < _size)
	{
		_elem[lo++] = _elem[hi++];//[hi, _size)һ��ǰ��hi - loλ 
	}
	_size = lo;//���¹�ģ 
	//shrink();//�б�Ҫʱ����
	return hi - lo;//���ر�ɾ��Ԫ�ص���Ŀ 
}
template <class T>
T Vector<T>::remove(Rank r)
{
	assert(r >= 0 && r < _size);
	T e = _elem[r];//���� 
	remove(r, r + 1);//��������ɾ���㷨
	return e;//���ر�ɾ��Ԫ�� 
}
template <class T>
Rank Vector<T>::find(T const &e, Rank lo, Rank hi) const
{
	while((lo < hi--) && (e != _elem[hi]))//������Ϊ�������ж��Ԫ��ʱ����������� 
	{
		
	}
	return hi;//���ʧ�ܷ���lo - 1����� 
}
template <class T>
int Vector<T>::deduplicate()
{
	int oldSize = _size;//��¼ԭ��ģ
	Rank i = 1;
	while(i < _size)
	{
		(find(_elem, 0, i) < 0) ? i++ : remove(i);//������ͬ���Ǻ�̣�������ͬɾ����ͬ 
	} 
	return oldSize - _size;//����������ģ�仯 
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
void increase(Vector<T> & v)//ͨ�������ⲿ����ģ��ﵽ����ĳ������ʵ�ֶ�Ӧ�������ܵ�Ŀ�� 
{
	v.traverse(Increase<T>());//������ʱ���������룬���ں������� 
}
template <class T>
int Vector<T>::disordered() const
{
	int n = 0; //������
	for(int i = 1; i < _size; i++)//�ӵڶ���Ԫ�ؿ�ʼ 
	{
		n += (_elem[i - 1] > _elem[i]);//��������� 
	}
	return n; //���ض�������� 
} 
template <class T>
int Vector<T>::uniquify1()
{
	int oldSize = _size;//��¼ԭʼ��С
	int i = 0;//����Ԫ�ؿ�ʼ
	while(i < _size - 1)
	{
		(_elem[i] == _elem[i + 1]) ? remove(i + 1) : i++;//��ͬ�Ƴ����ߣ���ͬת����һԪ�� 
	}
	return oldSize - _size;//������ģ�仯������ 
}//_size����С��remove()��� 
template <class T>
int Vector<T>::uniquify2()
{
	Rank i = 0, j = 0;//���Ի��조���ڡ�Ԫ�ص��� 
	while(++j < _size)//��һɨ�裬ֱ��ĩԪ�� 
	{
		//������ͬ�ߣ����ֲ�ͬԪ��ʱ����ǰ����������ǰ���Ҳ�
		if(_elem[i] != _elem[j])
		{
			_elem[++i] = _elem[j];
		} 
	}
	_size = ++i;
	//shrink();//�س�β������Ԫ��
	return j - i;//����ɾ����Ԫ�ظ��� 
}//����ɾ����Ȼ���ܴﵽ��Ч 
template <class T>
Rank Vector<T>::search(T const & e, Rank lo, Rank hi) const
{
	//���ʹ�ö��ֲ��һ�Fibonacci�㷨 
	return (rand() % 2) ? binSearchC(_elem, e, lo, hi) : fibSearch(_elem, e, lo , hi); 
}
template <class T>
void Vector<T>::selectionSort(Rank lo, Rank hi)//ѡ�������Ӱ� 
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
	while(!bubbleA(lo, hi--));//����ɨ�轻����ֱ��ȫ�� 
}
template <class T>
bool Vector<T>::bubbleA(Rank lo, Rank hi)
{
	bool sorted = true;//���������־
	while(++lo < hi)
	{
		if(_elem[lo - 1] > _elem[lo])
		{
			sorted = false;
			swap(_elem[lo - 1], _elem[lo]);//���� 
		}
	}
	return sorted; //�жϵ�ǰ��ɨ���Ƿ��Ѿ�����Ҫ���������Ѿ����� 
}
template <class T>
void Vector<T>::bubbleSortB(Rank lo, Rank hi)
{
	while(lo < (hi = bubbleB(lo, hi)));//����ɨ�轻����ֱ��ȫ�� 
}
template <class T>
Rank Vector<T>::bubbleB(Rank lo, Rank hi)
{
	Rank last = lo;
	while(++lo < hi)
	{
		if(_elem[lo - 1] > _elem[lo])
		{
			last = lo;//�������Ҳ������λ�ü�¼ 
			swap(_elem[lo - 1], _elem[lo]);
		}
	}
	return last;//�������Ҳ������λ�� 
}
template <class T>
void Vector<T>::mergeSort(Rank lo, Rank hi)
{
	if(hi - lo < 2) return;//��Ԫ��������Ȼ���� 
	int mi = (lo + hi) >> 1;//���е�Ϊ��
	mergeSort(lo, mi);//��ǰ�������
	mergeSort(mi, hi);//�Ժ�������
	merge(lo, mi, hi);//�鲢 
} 
template <class T>
void Vector<T>::merge(Rank lo, Rank mi, Rank hi)
{
	T* A = _elem + lo;//�ϲ��������A[0, hi - lo) = _elem[lo, mi)
	int lb = mi - lo;//ǰ������Ԫ�ظ��� 
	T* B = new T[lb];//ǰ������B[0,lb) = _elem[lo, mi)
	for(Rank i = 0; i < lb; B[i] = A[i++]);//����ǰ������B
	int lc = hi - mi;//��������Ԫ�ظ��� 
	T* C = _elem + mi;//��������C[0, lc) = _elem[mi, hi)
	for(Rank i = 0, j = 0, k = 0;j < lb;)//B[j]��C[k]��С��ת��A�� 
	{//Bһ����ǰ�ľ�ѭ��ֱ����ֹ 
		if((k < lc) && (C[k] < B[j]))
		{
			A[i++] = C[k++];//B[k]���޻���� 
		}
		if(lc <= k || (B[j] <= C[k]))
		{
			A[i++] = B[j++];//C[k]���޻�С 
		}
	}
	delete[] B;//�ͷſռ� 
	 
}
template <class T>
void Vector<T>::sort(Rank lo, Rank hi)
{
	switch(rand() % 5)
	{
		case 1:
			bubbleSortB(lo, hi);//ð�� 
			break;
		case 2:
			selectionSort(lo, hi);//ѡ�� 
			break;
		case 3:
			mergeSort(lo, hi);//�鲢 
			break;
	}
}
int main()
{
	
}
