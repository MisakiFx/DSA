#include <iostream>
#include <assert.h>
template<class T>
class Stack
{
public:
    //构造函数
    Stack()
        :_stack(nullptr)  
        ,_size(0)
        ,_capacity(0)
    {
    }
    //析构函数
    ~Stack()
    {
        if(_stack != nullptr)
        {
            delete[] _stack;
        }
    }
    //入栈
    void Push(const T& temp)
    {
        //尾插
        //容量检查
        if(_size == _capacity)//满了
        {
            size_t newCapacity = (_capacity == 0 ? 5 : 2 * _capacity);
            T* stackTemp = new T[newCapacity];
            for(int i = 0; i < _size; i++)
            {
                stackTemp[i] = _stack[i];
            }
            //delete空指针是完全安全的
            delete[] _stack;
            _stack = stackTemp;
            _capacity = newCapacity;
            std::cout << "Expend new capacity:" << _capacity << std::endl;
        }
        _stack[_size] = temp;
        _size++;
    }
    //出栈
    void Pop()
    {
        if(_size <= 0)
        {
            return;
        }
        _size--;
    }
    //栈顶元素
    const T& Top()
    {
        assert(_size > 0);
        return _stack[_size - 1];
    }
    //元素个数
    size_t Size()
    {
        return _size;
    }
    //是否为空
    bool IsEmpty()
    {
        return (_size <= 0 ? true : false);
    }
private:
    T* _stack;//顺序表
    size_t _size;//长度
    size_t _capacity;//容量
};
int main()
{
    Stack<int> sta;
    sta.Push(1);
    sta.Push(2);
    sta.Push(3);
    sta.Push(4);
    sta.Push(5);
    sta.Push(6);
    std::cout << sta.Size() << std::endl;
    while(!sta.IsEmpty())
    {
        std::cout << sta.Top() << " ";
        sta.Pop();
    }
    std::cout << std::endl;
    std::cout << sta.Size() << std::endl;
}