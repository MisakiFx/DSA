#include <iostream>
#include <assert.h>
template<class T>
struct QueueNode
{
    QueueNode()
        :_data(T())
        ,_next(nullptr)
    {}
    QueueNode(const T& data, QueueNode* next)
        :_data(data)
        ,_next(next)
    {}
    T _data;
    QueueNode* _next;
};

//用单向带头不循环链表实现队列
template<class T>
class Queue
{
public:
    Queue()
        :_head(nullptr)
        ,_rear(nullptr)
        ,_size(0)
    {
        _head = new QueueNode<T>;
        _rear = _head;
    }
    ~Queue()
    {
        while(!Empty())
        {
            Pop();
        }
        delete _head;
        _head = nullptr;
        _rear = nullptr;
    }
    void Push(const T& data)
    {
        QueueNode<T>* newNode = new QueueNode<T>(data, nullptr);
        _rear->_next = newNode;
        _rear = newNode;
        _size++;
    }
    bool Empty()
    {
        return _rear == _head;
    }
    void Pop()
    {
        QueueNode<T>* temp = _head->_next;
        _head->_next = _head->_next->_next;
        //队列中只有一个元素
        if(temp == _rear)
        {
            _rear = _head;
        }
        delete temp;
        temp = nullptr;
        _size--;
    }
    const T& Front()
    {
        assert(_head->_next != nullptr);
        return _head->_next->_data;
    }
    const T& Back()
    {
        assert(_rear != _head);
        return _rear->_data;
    }
    size_t Size()
    {
        return _size;
    }
private:
    QueueNode<T>* _head;    //指向头部结点
    QueueNode<T>* _rear;    //指向最后一个元素
    size_t _size;
};

int main()
{
    Queue<int> que;
    que.Push(1);
    que.Push(2);
    que.Push(3);
    que.Push(4);
    while(!que.Empty())
    {
        std::cout << "size = " << que.Size() << std::endl;
        std::cout << que.Front() << std::endl;
        que.Pop();
    }
}