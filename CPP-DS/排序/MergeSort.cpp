#include <iostream>
#include <vector>

//左闭右开区间
void Merge(std::vector<int>& arr, int start, int mid, int end)
{
    std::vector<int> arr1, arr2;
    for(int i = start; i < mid; i++)
    {
        arr1.push_back(arr[i]);
    }
    //for(int i = mid; i < end; i++)
    //{
    //    arr2.push_back(arr[i]);
    //}
    int i = 0, j = mid, k = start;
    while(i < arr1.size() && j < end)
    {
        if(arr1[i] <= arr[j])
        {
            arr[k] = arr1[i];
            i++;
            k++;
        }
        else 
        {
            arr[k] = arr[j];
            j++;
            k++;
        }
    }
    while(i < arr1.size())
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    //while(j < arr2.size())
    //{
    //    arr[k] = arr2[j];
    //    j++;
    //    k++;
    //}
}
void MergeSort(std::vector<int>& arr, int start, int end)
{
    if(end - start > 1)
    {
        int mid = (start + end) >> 1;
        MergeSort(arr, start, mid);
        MergeSort(arr, mid, end);
        Merge(arr, start, mid, end);
    }
}
int main()
{
    std::vector<int> arr = {1, 2, 22, 1, 5, 4, 55, 44, 3};
    MergeSort(arr, 0, arr.size());
    for(const auto& e : arr)
    {
        std::cout << e << " ";
    }
}