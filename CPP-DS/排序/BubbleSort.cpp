#include <iostream>
#include <vector>
void BubbleSort(std::vector<int>& arr)
{
    int n = arr.size();
    bool flag = true;
    for(int i = 0; i < n - 1; i++)
    {
        if(flag == false)
        {
            break;
        }
        flag = false;
        for(int j = 0; j < n - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                flag = true;
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main()
{
    std::vector<int> arr = {1, 1, 2, 2, 99, 3, 3, 4, 5, 88, 2};
    BubbleSort(arr);
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}