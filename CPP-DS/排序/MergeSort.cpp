#include <iostream>
#include <vector>
using namespace std;
template<class T>
void Merge(vector<T>& arr, size_t first, size_t mid, size_t last)
{
    cout << "first: " << first << ", mid: " << mid << ", last: " << last << endl;
    int len1 = mid - first;
    int len2 = last - mid;
    vector<T> arr1(len1);
    vector<T> arr2(len2);
    for(int i = 0; i < len1; i++)
    {
        arr1[i] = arr[first + i];
    }
    for(int i = 0; i < len2; i++)
    {
        arr2[i] = arr[mid + i];
    }
    int i = 0, j = 0, k = first;
    while(i < len1 && j < len2)
    {
        if(arr1[i] < arr2[j])
        {
            arr[k] = arr1[i];
            i++;
        }
        else
        {
            arr[k] = arr2[j];
            j++;
        }
        k++;
    }
    while(i < len1)
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    while(j < len2)
    {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}
template<class T>
void MergeSort(vector<T>& arr, size_t first, size_t last)
{
    //这里统一按照左闭右开区间进行规范
    if((last - first) > 1)
    {
        int mid = (first + last) / 2;
        MergeSort(arr, first, mid);
        MergeSort(arr, mid, last);
        Merge(arr, first, mid, last);
        for (int i = 0; i < arr.size(); i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}
int main()
{
    vector<int> arr = {9, 10, 3, 4, 5, 1, 2};
    MergeSort(arr, 0, arr.size());
    for(int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
}