#include <iostream>
#include <vector>

void SelectSort(std::vector<int>& arr)
{
    int n = arr.size();
    for(int i = 0; i < n - 1; i++)
    {
        int min = i;
        for(int j = i + 1; j < n; j++)
        {
            if(arr[j] < arr[min])
            {
                min = j;
            }
        }
        if(min != i)
        {
            std::swap(arr[i], arr[min]);
        }
    }   
}
int main()
{
    std::vector<int> arr = {1, 2, 3, 19, 10, 5, 2, 5, 7};
    SelectSort(arr);
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}