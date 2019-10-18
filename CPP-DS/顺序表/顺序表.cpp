#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include <stdlib.h>
#include <Windows.h>
using namespace std;
#define N 100
//顺序表的实现
//十分类似于我们实现过的vector类，毕竟vector就是顺序表
template<class T>
class SeqList
{
public:
    //构造函数
    SeqList()
    :_array(nullptr)
    ,_size(0)
    ,_capacity(0)
    {}
    //析构函数
    ~SeqList()
    {
        if(_array != nullptr)
        {
            delete _array;
        }
    }
    //pos前插入
    void Insert(size_t pos, const T& value)
    {
        //判断pos是否合法
        if(pos > _size || pos < 0)
        {
            return;
        }
        //扩容
        Expend();
        for(size_t i = _size; i > pos; i--)
        {
            _array[i] = _array[i - 1];
        }
        _array[pos] = value;
        _size++;
    }
    //尾插
    void Push_back(const T& value)
    {
        //扩容
        Expend();
        _array[_size] = value;
        _size++;
    }
    //头插
    void Push_front(const T& value)
    {
        //扩容
        Expend();
        //所有元素向后挪一个位置
        for(size_t i = _size; i > 0; i--)
        {
            _array[i] = _array[i - 1];
        }
        _array[0] = value;
        _size++;
    }
    //尾删
    void Pop_back()
    {
        //删除前要先判断，有元素才能删
        if(_size > 0)
        {
            _size--;
        }
    }
    //头删
    void Pop_front()
    {
        //有元素才能删
        if(_size > 0)
        {
            for (size_t i = 1; i < _size; i++)
            {
                _array[i - 1] = _array[i];
            }
            _size--;
        }
    }
    //删除pos当前位置数据
    void Erase(size_t pos)
    {
        //pos不合法
        if(pos >= _size || pos < 0)
        {
            return;
        }
        for(size_t i = pos; i < _size - 1; i++)
        {
            _array[pos] = _array[pos + 1];
        }
        _size--;
    }
    //查找
    size_t Find(const T& value)
    {
        for(size_t i = 0; i < _size; i++)
        {
            if(_array[i] == value)
            {
                return i;
            }
        }
        return -1;
    }
    //二分查找
    size_t BinaryFind(const T& value)
    {
        //左闭右开区间
        size_t high = _size, low = 0;
        while(high > low)
        {
            size_t mid = (high + low) / 2;
            if(_array[mid] == value)
            {
                return mid;
            }
            else if(_array[mid] > value)
            {
                high = mid;    
            }
            else
            {
                low = mid + 1;
            }
        }
    }
    //修改
    void Modify(size_t pos, const T& value)
    {
        if(pos < 0 || pos >= _size)
        {
            return;
        }
        _array[pos] = value;
    }
    //打印
    void Print()
    {
        for(size_t i = 0; i < _size; i++)
        {
            cout << _array[i] << " ";
        }
        cout << endl;
        //cout << _size << endl;
    }
    //当前元素个数
    size_t Size()
    {
        return _size;
    }
    //某个位置的值
    T& operator[](size_t pos)
    {
        assert(pos >=0 && pos < _size);
        return _array[pos];
    }
    //冒泡排序
    void BubbleSort()
    {
        for(int i = 0; i < _size - 1; i++)
        {
            bool flag = false;
            for(int j = 0; j < _size - i - 1; j++)
            {
                if(_array[j] > _array[j + 1])
                {
                    swap(_array[j], _array[j + 1]);
                    flag = true;
                }
            }
            if(flag == false)
            {
                break;
            }
        }
    }
private:
    //T _array[N];//静态顺序表，利用数组，不可变，十分不灵活
    T* _array;//动态顺序表，利用指针动态开辟
    size_t _size;//长度
    size_t _capacity;//容量
    //扩容
    void Expend()
    {
        if(_size == _capacity)//满了
        {
            size_t newCapacity = (_capacity == 0 ? 5 : 2 * _capacity);
            //创建更大空间，拷贝，释放原有空间
            _array = (T*)realloc(_array, newCapacity * sizeof(T));
            //申请失败
            assert(_array);
            //更新容量
            _capacity = newCapacity;
        }
    }
};
int main()
{
    SeqList<int> list;
    list.Push_back(9);
    list.Push_back(1);
    list.Push_back(10);
    list.Push_back(11);
    list.Push_back(20);
    list.Push_back(0);
    list.Push_back(-1);
    list.Push_front(1);
    list.Print();
    list.BubbleSort();
    list.Print();
    int pos = list.BinaryFind(1);
    std::cout << pos << std::endl;
}