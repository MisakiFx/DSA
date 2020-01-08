#include <iostream>
#include <vector>

void InsertSort(std::vector<int>& arr)
{
    if(arr.size() <= 1)
    {
        return;
    }
    int n = arr.size();
    for(int i = 1; i < n; i++)
    {
        int j = i - 1;
        while(arr[j] > arr[j + 1] && j >= 0)
        {
            std::swap(arr[j], arr[j + 1]);
            j--;
        }
    }
}
int main()
{
    std::vector<int> arr = {1, 1, 99, 23, 32, 2, 2, 4, 5};
    InsertSort(arr);
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}