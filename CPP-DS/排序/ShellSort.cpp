#include <iostream>
#include <vector>

void InsertSort(int gap, std::vector<int>& arr)
{
    int n = arr.size();
    for(int i = gap; i < n; i++)
    {
        for(int j = i - gap; j >= 0; j -= gap)
        {
            if(arr[j + gap] >= arr[j])
            {
                break;
            }
            else 
            {
                std::swap(arr[j + gap], arr[j]);
            }
        }
    }
}
void ShellSort(std::vector<int>& arr)
{
    for(int i = arr.size() / 2; i >= 1; i /= 2)
    {
        InsertSort(i, arr);
    }
}
int main()
{
    std::vector<int> arr = {1, 2, 10, 3, 4, 7, 2, 9, 3, 4, 99, 5};
    ShellSort(arr);
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}