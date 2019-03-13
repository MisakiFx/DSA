#include <stdio.h>
/* 冒泡排序
 * 默认升序排序
 * 参数：array 数组 size数组大小
 * 复杂度为n^2
 * */
void BubbleSort(int array[], int size)
{
  int sorted;//判断是否发生交换的“眼”
  for(int i = 0; i < size; i++)
  {
    sorted = 1;
    for(int j = 0; j < size - i - 1; j++)
    {
      if(array[j] > array[j + 1])
      {
        int temp = array[j];
        array[j] = array[j + 1];
        array[j + 1] = temp;
        sorted = 0;//发生交换，将“眼”置为0
      }
    }
    if(sorted == 1)
    {
      //未发生交换，数组已经有序
      break;
    }
  }
}
int main()
{
  int array[] = {1, 99, 87, 7, 100};
  int size = sizeof(array) / sizeof(array[0]);
  BubbleSort(array, size);
  for(int i = 0; i < size; i++)
  {
    printf("%d\t", array[i]);
  }
  printf("\n");
}
