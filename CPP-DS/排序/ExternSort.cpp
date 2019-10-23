#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include <string>
#define NUMS_COUNT 2000000 //数据总数
#define BLOCK_SIZE 100000 //块大小
#define NUMS_FILE "nums.txt"
void CreateNum(std::vector<double>& arr, size_t num)
{
    srand(time(NULL));
    for(size_t i = 0; i < num; i++)
    {
        double num = rand() % 10000 + (double)(rand() % 100) / 100;
        arr.push_back(num);
    }
}
//将vector<double>中的数据写入文件，从beg位置开始写，写len长度个double型数据
bool WriteArrToFile(std::string filename, std::vector<double>& arr, size_t beg, size_t len)
{
    std::ofstream file(filename.c_str(), std::ios::binary | std::ios::trunc);
    if(!file.is_open())
    {
        std::cerr << "open file error" << std::endl;
        return false;
    }
    file.seekp(beg, std::ios::beg);
    file.write((char*)&arr[0], (len * sizeof(double)));
    if(!file.good())
    {
        std::cerr << "write file error" << std::endl;
        file.close();
        return false;
    }
    file.close();
    return true;
}
//将文件中的数据读入arr，从beg位置开始读，读len长度个double型数据
bool ReadFileToArr(std::vector<double>& arr, size_t beg, size_t len)
{
    std::ifstream file(NUMS_FILE, std::ios::binary);
    if(!file.is_open())
    {
        std::cerr << "open file error" << std::endl;
        return false;
    }
    file.seekg(beg, std::ios::beg);
    file.read((char*)&arr[0], len * sizeof(double));
    if(!file.good())
    {
        std::cerr << "read file error" << std::endl;
        file.close();
        return false;
    }
    return true;
}
void QuickSort(std::vector<double>& arr, size_t beg, size_t end)
{
    //左闭右开区间
    if((end - beg) <= 1)
    {
        return;
    }
    int b = beg, e = end - 1;
    double temp = arr[b];
    while(b < e)
    {
        while(b < e && arr[e] >= temp)
        {
            e--;
        }
        if(b < e)
        {
            arr[b] = arr[e];
        }
        while(b < e && arr[b] <= temp)
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
int main()
{
    std::vector<double> arr;
    CreateNum(arr, NUMS_COUNT);
    //先写2000000个数到文件中
    if(!WriteArrToFile(NUMS_FILE, arr, 0, NUMS_COUNT))
    {
        std::cout << "__LINE__: error" << std::endl;;
        return -1;
    }
    int count = NUMS_COUNT / BLOCK_SIZE;
    //每次从中读取100000个数
    //排序再写入新文件
    for(int i = 0; i < count; i++)
    {
        arr.clear();
        arr.resize(BLOCK_SIZE);
        if(!ReadFileToArr(arr, (i * BLOCK_SIZE), BLOCK_SIZE))
        {
            std::cerr << "__LINE__:error" << std::endl;
            return -1;
        }
        std::cout << "open" << i << "file" << std::endl;;
        QuickSort(arr, 0, arr.size());
        std::cout << "sort" << i << "file" << std::endl;;
        std::stringstream ss;
        ss << "nums" << i << ".txt";
        if(!WriteArrToFile(ss.str(), arr, 0, BLOCK_SIZE))
        {
            std::cerr << "__LINE__:error" << std::endl;
            return -1;
        }
        std::cout << "write" << i << "file" << std::endl;;
    }
}