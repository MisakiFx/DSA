#include <iostream>
#include <assert.h>

template<class T>
class CircleQueue
{
public:
    CircleQueue(size_t capacity)
        :_arr(nullptr)
        ,_head(0)
        ,_rear(0)
        ,_capacity(capacity)
    {
        assert(capacity >= 2);
        _arr = new T[_capacity];
    }
    ~CircleQueue()
    {
        delete _arr;
        _arr = nullptr;
    }
    //判断满
    bool IsFull()
    {
        if((_rear + 1) % _capacity == _head)
        {
            return true;
        }
        return false;
    }
    ///判断空
    bool IsEmpty()
    {
        if(_head == _rear)
        {
            return true;
        }
        return false;
    }
    bool Push(const T& data)
    {
        if(IsFull())
        {
            return false;
        }
        _arr[_rear] = data;
        _rear = (_rear + 1) % _capacity; 
        return true;
    }
    bool Pop()
    {
        if(IsEmpty())
        {
            return false;
        }
        _head = (_head + 1) % _capacity;
        return true;
    }
    const T& Front()
    {
        assert(!IsEmpty());
        return _arr[_head];
    }
    const T& Back()
    {
        assert(!IsEmpty());
        size_t temp = (_rear + _capacity - 1) % _capacity;
        return _arr[temp];
    }
    size_t Capacity()
    {
        return _capacity;
    }
    size_t Size()
    {
        return (_rear + _capacity - _head) % _capacity;
    }
private:
    T* _arr;            //存储环形队列的数组
    size_t _head;       //指向队头
    size_t _rear;       //指向队尾
    size_t _capacity;   //环形队列的总容量，一旦确定不可再改变
};

int main()
{
    CircleQueue<int> circleQueue(5);
    circleQueue.Push(1);
    circleQueue.Push(2);
    circleQueue.Push(3);
    circleQueue.Push(4);
    circleQueue.Push(5);
    while(!circleQueue.IsEmpty())
    {
        std::cout << "size = " << circleQueue.Size() << std::endl;
        std::cout << circleQueue.Front() << std::endl;
        circleQueue.Pop();
    }
    //std::cout << circleQueue.Front() << std::endl;
}