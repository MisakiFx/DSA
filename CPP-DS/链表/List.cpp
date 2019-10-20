#include <iostream>
using std::cout;
using std::endl;
template<class T>
struct ListNode
{
    //构造函数
    ListNode(const T& value = T())
        :data(value)
        ,next(nullptr)
    {

    }
    T data;//数据域
    ListNode* next;//指针域，指向下一个节点
};
template<class T>
class List
{
public:
    //构造函数
    List()
        :_head(new ListNode<T>)
        ,_size(0)
    {
    }
    ~List()
    {
        //依次删除所有节点以释放所有空间
        while(_size > 0)
        {
            Pop_Front();
        }
        delete _head;
    }
    //头插
    void Push_Front(const T& value)
    {
        InsertPos(0, value);
    }
    //尾插
    void Push_Back(const T& value)
    {
        InsertPos(_size, value);
    }
    //打印所有数据
    void PrintAll()
    {
        ListNode<T>* temp = _head->next;
        while(temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }
    //在下标为pos的元素前进行插入
    void InsertPos(size_t pos, const T& value)
    {
        if(pos < 0 || pos > _size)
        {
            cout << "InsertPos: pos error" << endl;
            return;
        }
        //这里的插入时间复杂度本应是O1，但是由于链表不便于寻址因此又需要线性的时间进行寻址
        ListNode<T>* node = FindForPos(pos);
        if(node == nullptr)
        {
            return;
        }
        ListNode<T>* newNode = new ListNode<T>(value);
        newNode->next = node->next;
        node->next = newNode;
        _size++;
    }
    //删除下标为pos的元素
    void ErasePos(size_t pos)
    {
        if(pos < 0 || pos >= _size)
        {
            cout << "ErasePos: pos error" << endl;
            return;
        }
        ListNode<T>* node = FindForPos(pos);
        if(node == nullptr)
        {
            return;
        }
        ListNode<T>* temp = node->next;
        node->next = temp->next;
        delete temp;
        _size--;
    }
    //尾删
    void Pop_Back()
    {
        ErasePos(_size - 1);
    }
    //头删
    void Pop_Front()
    {
        ErasePos(0);
    }
    //返回链表长度
    size_t Size()
    {
        return _size;
    }
private:
    //返回下标为pos的元素的前一个元素，下标为0的元素则返回头节点
    ListNode<T>* FindForPos(size_t pos)
    {
        ListNode<T> *temp = _head;
        for(int i = 0; i < pos; i++)
        {
            //不存在，长度不够
            if(temp == nullptr)
            {
                cout << "FindForPos: pos error" << endl;
                return nullptr;
            }
            temp = temp->next;
        }
        return temp;
    }
private:
    ListNode<T>* _head;
    size_t _size;
};
int main()
{
    List<int> list;
    list.Push_Front(1);
    list.Push_Front(2);
    list.Push_Front(2);
    list.Push_Front(4);
    list.Push_Front(2);
    list.Push_Front(3);
    list.Push_Back(10);
    list.PrintAll();
    list.Pop_Back();
    list.PrintAll();
    list.Pop_Front();
    list.PrintAll();
    cout << list.Size() << endl;
}
