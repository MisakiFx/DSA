#include <iostream>
#include <vector>

//左闭右开区间
void QuickSort(std::vector<int>& arr, int start, int end)
{
    if(end - start <= 1)
    {
        return;
    }
    int temp = arr[start];
    int ptr1 = start;
    int ptr2 = end - 1;
    while(ptr1 < ptr2)
    {
        while(arr[ptr2] >= temp && ptr1 < ptr2)
        {
            ptr2--;
        }
        if(ptr1 >= ptr2)
        {
            break;
        }
        arr[ptr1] = arr[ptr2];
        while(arr[ptr1] <= temp && ptr1 < ptr2)
        {
            ptr1++;
        }
        if(ptr1 >= ptr2)
        {
            break;
        }
        arr[ptr2] = arr[ptr1];
    }
    arr[ptr1] = temp;
    QuickSort(arr, start, ptr1);
    QuickSort(arr, ptr1 + 1, end);
}

int main()
{
    std::vector<int> arr = {3, 1, 2, 55, 2, 4, 88, 22, 1, 3};
    QuickSort(arr, 0, arr.size());
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}