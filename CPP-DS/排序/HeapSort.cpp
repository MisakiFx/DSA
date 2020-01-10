#include <iostream>
#include <vector>

//堆排序最简单的实现方法就是使用STL中的优先级队列
//优先级队列内部自动维护了一个堆，可用很轻松的帮助我们完成堆排序
//但是为了更好的了解算法思想这里我们手动维护这个堆
void AdjustDown(int start, int end, std::vector<int>& arr)
{
    int parent = start;
    int child = parent * 2 + 1;
    while(child < end)
    {
        if(child + 1 < end && arr[child + 1] > arr[child])
        {
            child += 1;
        }
        if(arr[child] <= arr[parent])
        {
            break;
        }
        else 
        {
            std::swap(arr[child], arr[parent]);
            parent = child;
            child = parent * 2 + 1;
        }
    }
}
void HeapSort(std::vector<int>& arr)
{
    //建堆
    int n = arr.size();
    for(int i = (n / 2 - 1); i >= 0; i--)
    {
        AdjustDown(i, n, arr);
    }
    //排序
    while(n > 0)
    {
        std::swap(arr[0], arr[n - 1]);
        n--;
        AdjustDown(0, n, arr);
    }
}
int main()
{
    std::vector<int> arr = {1, 4, 5, 3, 4, 22, 33, 5, 2};
    HeapSort(arr);
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}