#include "SeqList.h"


//容量更新，static更改连接属性
static void CheckCapacity(SeqList* seqlist)
{
  if(seqlist->size < seqlist->capacity)
  {
    return;
  }
  //需要扩容的情况
  //申请新空间
  int newCapacity = 2 * seqlist->capacity;
  SLDataType* newArray = (SLDataType*)malloc(sizeof(SLDataType) * newCapacity);
  //copy老数据到新空间
  for(int i = 0; i < seqlist->size; i++)
  {
    newArray[i] = seqlist->array[i];
  }
  //释放老空间，把新的空间绑定到顺序表结构体
  free(seqlist->array);
  seqlist->array = newArray;
  //更新容量
  seqlist->capacity = newCapacity;
}
//初始化顺序表
void SeqListInit(SeqList* seqlist, int capacity)
{
  //在堆上分配顺序表的空间
  //初始化容量，size字段
  assert (seqlist != NULL);
  seqlist->array = (SLDataType*)malloc(sizeof(SLDataType) * capacity);
  seqlist->capacity = capacity;
  seqlist->size = 0;
}
//删除顺序表
void SeqListDestory(SeqList* seqlist)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  free(seqlist->array);
  //附加
  seqlist->array = NULL;
  seqlist->capacity = seqlist->size = 0;
}
//头插
void SeqListPustFront(SeqList* seqlist, SLDataType v)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  CheckCapacity(seqlist);
  for(int i = seqlist->size; i > 0; i--)
  {
    seqlist->array[i] = seqlist->array[i - 1];
  }
  seqlist->array[0] = v;
  seqlist->size++;
}
//尾插
void SeqListPushBack(SeqList* seqlist, SLDataType v)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  CheckCapacity(seqlist);
  seqlist->array[seqlist->size] = v;
  seqlist->size++;
}
//插入
void SeqListInsert(SeqList* seqlist, int pos, SLDataType v)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  assert(pos < seqlist->size && pos >= 0);
  CheckCapacity(seqlist);
  for(int i = seqlist->size; i > pos; i--)
  {
     seqlist->array[i] = seqlist->array[i - 1];
  }
  seqlist->array[pos] = v;
  seqlist->size++;
}
//尾删
void SeqListPopBack(SeqList* seqlist)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  seqlist->size--;
}
//头删
void SeqListPopFront(SeqList* seqlist)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  for(int i = 0; i < seqlist->size - 1; i++)
  {
    seqlist->array[i] = seqlist->array[i + 1];
  }
  seqlist->size--;
}
//删除
void SeqListErase(SeqList* seqlist, int pos)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  assert(pos < seqlist->size && pos >= 0);
  for(int i = pos; i < seqlist->size - 1; i++)
  {
    seqlist->array[i] = seqlist->array[i + 1];
  }
  seqlist->size--;
}
//修改
void SeqListModify(SeqList* seqlist, int pos, SLDataType v)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  assert(pos < seqlist->size && pos >= 0);
  seqlist->array[pos] = v;
}
//打印
void SeqListPrint(SeqList* seqlist)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  for(int i = 0; i < seqlist->size; i++)
  {
    printf("%d\t", seqlist->array[i]);
  }
}
//查找
int SeqListFind(SeqList* seqlist, SLDataType v)
{
  assert(seqlist != NULL);
  assert(seqlist->array != NULL);
  for(int i = 0; i < seqlist->size; i++)
  {
    if(seqlist->array[i] == v)
    {
      return i;
    }
  }
  return -1;
}
//删除第一次遇到的v
void SeqListRemove(SeqList* seqlist, SLDataType v)
{
  int pos = SeqListFind(seqlist, v);
  if(pos == -1)
  {
    return;
  }
  SeqListErase(seqlist, pos);
}
//删除遇到的所有v
void SeqListRemoveAll(SeqList* seqlist, int v)
{
  int i, j;
  for(i = 0, j = 0; i < seqlist->size; i++)
  {
    if(seqlist->array[i] != v)
    {
      seqlist->array[j] = seqlist->array[i];
    }
  }
  seqlist->size++;
}
