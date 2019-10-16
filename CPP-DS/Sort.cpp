#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
template<class T>
class Sort
{
public:
    //冒泡排序
    void BubbleSort(std::vector<T>& arr);
    //选择排序
    void SelectionSort(std::vector<T>& arr);
    //插入排序
    void InsertSort(std::vector<T>& arr);
    //归并排序(左闭右开区间)
    void MergeSort(std::vector<T>& arr, int beg, int end);
    //希尔排序
    void ShellSort(std::vector<T>& arr);
    //快速排序(左闭右开区间)
    void QuickSort(std::vector<T>& arr, int beg, int end);
    //堆排序
    void HeapSort(std::vector<T>& arr);
private:
    void Merge(std::vector<T>& arr, int beg, int mid, int end);
    void Insert(std::vector<T>& arr, int gap);
    void AdjustDown(std::vector<T>& arr, int beg, int end);
};
template<class T>
void Sort<T>::HeapSort(std::vector<T> &arr)
{
    int n = arr.size();
    for(int i = n / 2 - 1; i >= 0; i--)
    {
        AdjustDown(arr, i, n);
    }
    for(int i = n - 1; i > 0; i--)
    {
        std::swap(arr[0], arr[i]);
        AdjustDown(arr, 0, i);
    }
}
template<class T>
void Sort<T>::AdjustDown(std::vector<T> &arr, int parent, int end)
{
    int son = 2 * parent + 1;
    while(son < end)
    {
        if((son + 1) < end && arr[son + 1] > arr[son])
        {
            son += 1;
        }
        if(arr[parent] < arr[son])
        {
            std::swap(arr[parent], arr[son]);
            parent = son;
            son = son * 2 + 1;
        }
        else
        {
            break;
        }
    }
}
std::vector<double> ConstructNum()
{
    srand(time(NULL));
    std::vector<double> arr;
    for (int i = 0; i < 20; i++)
    {
        double num = (rand() % 10000) + ((double)(rand() % 100) / 100);
        arr.push_back(num);
    }
    return arr;
}
template<class T>
void Sort<T>::QuickSort(std::vector<T> &arr, int beg, int end)
{
    //左闭右开区间
    if((end - beg) <= 1)
    {
        return;
    }
    int b = beg, e = end - 1;
    T temp = arr[b];
    while(b < e)
    {
        while(b < e && arr[e] > temp)
        {
            e--;
        }
        if(b < e)
        {
            arr[b] = arr[e];
        }
        while(b < e && arr[b] < temp)
        {
            b++;
        }
        if(b < e)
        {
            arr[e] = arr[b];
        }
    }
    arr[b] = temp;
    QuickSort(arr, beg, b);
    QuickSort(arr, b + 1, end);
}
template<class T>
void Sort<T>::ShellSort(std::vector<T>& arr)
{
    for(int gap = arr.size() / 2; gap > 0; gap /= 2)
    {
        Insert(arr, gap);
    }
}
template<class T>
void Sort<T>::Insert(std::vector<T>& arr, int gap)
{
    for(int i = gap; i < arr.size(); i++)
    {
        for(int j = i - gap; j >= 0; j -= gap)
        {
            if(arr[j] > arr[j + gap])
            {
                std::swap(arr[j], arr[j + gap]);
            }
            else
            {
                break;
            }
        }
    }
}
template<class T>
void Sort<T>::MergeSort(std::vector<T> &arr, int beg, int end)
{
    //左闭右开区间
    if(end - beg > 1)
    {
        int mid = (beg + end) / 2;
        MergeSort(arr, beg, mid);
        MergeSort(arr, mid, end);
        Merge(arr, beg, mid, end);
    }
}
template<class T>
void Sort<T>::Merge(std::vector<T> &arr, int beg, int mid, int end)
{
    std::vector<T> arr1, arr2;
    for(int i = 0; i < mid - beg; i++)
    {
        arr1.push_back(arr[beg + i]);
    }
    for(int i = 0; i < end - mid; i++)
    {
        arr2.push_back(arr[mid + i]);
    }
    int i = 0, j = 0, k = beg;
    while(i < arr1.size() && j < arr2.size())
    {
        if(arr1[i] < arr2[j])
        {
            arr[k] = arr1[i];
            i++;
            k++;
        }
        else
        {
            arr[k] = arr2[j];
            j++;
            k++;
        }
    }
    while (i < arr1.size())
    {
        arr[k] = arr1[i];
        i++;
        k++;
    }
    while (j < arr2.size())
    {
        arr[k] = arr2[j];
        j++;
        k++;
    }
}
template<class T>
void Sort<T>::SelectionSort(std::vector<T>& arr)
{
    for(int i = 0; i < arr.size() - 1; i++)
    {
        size_t minIndex = i;
        for(int j = i + 1; j < arr.size(); j++)
        {
            if(arr[j] < arr[minIndex])
            {
                minIndex = j;
            }
        }
        if(minIndex != i)
        {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}
template<class T>
void Sort<T>::BubbleSort(std::vector<T>& arr)
{
    for(int i = 0; i < arr.size() - 1; i++)
    {
        bool flag = false;
        for(int j = 0; j < arr.size() - i - 1; j++)
        {
            if(arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                flag = true;
            }
        }
        if(flag == false)
        {
            break;
        }
    }
}
template<class T>
void Sort<T>::InsertSort(std::vector<T>& arr)
{
    //for(int i = 1; i < arr.size(); i++)
    //{
    //    for(int j = i - 1; j >= 0; j--)
    //    {
    //        if(arr[j + 1] < arr[j])
    //        {
    //            std::swap(arr[j + 1], arr[j]);
    //        }
    //        else
    //        {
    //            break;
    //        }
    //    }
    //}
    Insert(arr, 1);
}
int main()
{
    //std::vector<int> arr = {10 ,5 , 6, 2, 1, 3, 4};
    //Sort<int> sort;
    //sort.BubbleSort(arr);
    //for(auto i : arr)
    //{
    //    std::cout << i << " ";
    //}
    system("chcp 65001");
    Sort<double> sort;
    std::vector<double> arr = ConstructNum();
    std::vector<double> arr2 = arr;
    std::vector<double> arr3 = arr;
    std::vector<double> arr4 = arr;
    std::vector<double> arr5 = arr;
    std::vector<double> arr6 = arr;
    std::vector<double> arr7 = arr;
    std::cout << "原数组："; 
    for(auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    sort.BubbleSort(arr);
    std::cout << "冒泡排序：";
    for(auto i : arr)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "选择排序：";
    sort.SelectionSort(arr2);
    for(auto i : arr2)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "插入排序：";
    sort.InsertSort(arr3);
    for(auto i : arr3)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "归并排序：";
    sort.MergeSort(arr4, 0, arr4.size());
    for(auto i : arr4)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "希尔排序：" ;
    sort.ShellSort(arr5);
    for(auto i : arr5)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "快速排序：" ;
    sort.QuickSort(arr6, 0, arr6.size());
    for(auto i : arr6)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    std::cout << "堆排序：" ;
    sort.HeapSort(arr7);
    for(auto i : arr7)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
}