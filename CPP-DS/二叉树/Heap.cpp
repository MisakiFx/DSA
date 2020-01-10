#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>
//T为数据类型，Compare为比较方法，less创建大根堆，greater创建大根堆
template<class T, class Compare>
class Heap
{
public:
    Heap()
        :_arr()
        ,_size(0)
    {}
    Heap(const std::vector<T>& arr)
        :_arr(arr)
        ,_size(arr.size())
    {
        //根据已有数组建堆
        //建堆思路即从最后一个开始进行向下调整，一直向下调整到根
        for(int i = (_size - 2) / 2; i >= 0; i--)
        {
            AdjustDown(i);
        }
    }
    void Pop()
    {
        //弹出根节点
        //思路是将根与最后一个元素交换，然后向下调整，之后弹出最后一个结点    
        std::swap(_arr[0], _arr[_size - 1]);
        _arr.pop_back();
        _size--;
        AdjustDown(0);
    }
    void Push(const T& data)
    {
        _arr.push_back(data);
        //新插入元素要向上调整保证依然是一个堆
        _size++;
        AdjustUp(_size - 1);
    }
    void Print()
    {
        for(const auto& e : _arr)
        {
            std::cout << e << " ";
        }
        std::cout << std::endl;
    }
    const T& Top()
    {
        assert(_size > 0);
        return _arr[0];
    }
    bool Empty()
    {
        assert(_size > 0);
        return _size == 0;
    }
    size_t Size()
    {
        return _size;
    }
    void HeapSort(std::vector<int>& arr)
    {
        //堆排序的思想即建堆将根持续弹出放到尾部
        //升序建大根堆
        //降序建小根堆
        Heap<T, Compare> tempHeap(_arr);
        int tempSize = tempHeap.Size();
        arr.resize(tempSize);
        while(!tempHeap.Empty())
        {
            T top = tempHeap.Top();
            arr[tempSize - 1] = top;
            tempSize--;
            tempHeap.Pop();
        }
    }
private:
    //向下调整
    //向下调整是堆操作中十分常用的基础操作
    //即我们从一个指定结点开始向下调整直到不需要调整为止，
    //保证调整过的路径满足堆的要求
    void AdjustDown(size_t pos)
    {
        Compare cmp;
        //孩子节点下标为 根节点下标 * 2 + 1 和 根结点下标 * 2 + 2
        size_t child = pos * 2 + 1;
        while(child < _size)
        {
            if((child + 1) < _size && cmp(_arr[child], _arr[child + 1]))
            {
                child += 1;
            }
            //如果调整了还需要继续向下调整
            if(cmp(_arr[pos], _arr[child]))
            {
                std::swap(_arr[pos], _arr[child]);
            }
            else 
            {
                break;
            }
            pos = child;
            child = pos * 2 + 1;
        }
    }
    //向上调整与向下调整类似
    void AdjustUp(size_t pos)
    {
        Compare cmp;
        //父结点下标为 (孩子结点下表 - 1) / 2
        size_t parent = (pos - 1) / 2;
        while(pos > 0)
        {
            //如果调整了需要继续向上迭代调整
            if(cmp(_arr[parent], _arr[pos]))
            {
                std::swap(_arr[parent], _arr[pos]);
            }
            else 
            {
                break;
            }
            pos = parent;
            parent = (pos - 1) / 2;
        }
    }
private:
    std::vector<T> _arr;
    size_t _size;
};

int main()
{
    std::vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    Heap<int, std::less<int>> heap(arr);
    heap.Print();
    heap.Pop();
    heap.Print();
    std::vector<int> arr2;
    heap.HeapSort(arr2);
    for(const auto& e : arr2)
    {
        std::cout << e << " ";
    }
    std::cout << std::endl;
    std::cout << heap.Size() << std::endl;
    heap.Push(7);
    heap.Print();
}