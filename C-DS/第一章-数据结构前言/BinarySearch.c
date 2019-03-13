#include <stdio.h>
int BinarySearch1(int array[], int size, int v)
{
  //左闭右闭的情况
  int l = 0;//左侧区间的坐标
  int h = size - 1;//右侧区间的坐标
  while(l <= h)//区间为左闭右闭的情况，如果区间内还有数就要继续比较
  {
    int mid = (l + h) / 2;
    if(array[mid] == v)
    {
      return mid;
    }
    else if(array[mid] < v)
    {
      l = mid + 1;
    }
    else if(array[mid] > v)
    {
      h = mid - 1;
    }
  }
}
int BinarySearch2(int array[], int size, int v)
{
  //左闭右开的情况
  int l = 0;//左侧区间的坐标
  int h = size;//右侧区间的坐标
  while(l < h)//区间为左闭右开的情况，区间内没有数了
  {
    int mid = (l + h) / 2;
    if(array[mid] == v)
    {
      return mid;
    }
    else if(array[mid] < v)
    {
      l = mid + 1;
    }
    else if(array[mid] > v)
    {
      h = mid;
    }
  }
}
int main()
{
  int array[] = {1, 3, 4, 5, 6, 7, 8};
  printf("查找3的下标%d\n", BinarySearch1(array, sizeof(array) / sizeof(array[0]), 3));
}
