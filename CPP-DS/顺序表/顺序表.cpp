#include <iostream>
#include <stdlib.h>
#include <assert.h>
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

    }
    //尾删
    void Pop_back()
    {
        if(_size > 0)
        {
            _size--;
        }
    }
    //头删
    void Pop_front()
    {

    }
    //删除pos当前位置数据
    void Erase()
    {

    }
    //查找
    size_t Find(const T& value)
    {

    }
    //修改
    void Modify(size_t pos, const T& value)
    {

    }
    //打印
    void Print()
    {
        for(size_t i = 0; i < _size; i++)
        {
            cout << _array[i] << endl;
        }
    }
    //当前元素个数
    size_t Size()
    {

    }
    //某个位置的值
    T& operator[](size_t pos)
    {

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
    list.Push_back(2);
    list.Pop_back();
    list.Pop_back();
    list.Print();
}