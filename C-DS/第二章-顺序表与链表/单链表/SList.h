#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
typedef int SListDataType;
typedef struct Node
{
  SListDataType value;
  struct Node* next;
}Node;
//不带头节点,直接用指针指向第一个节点
typedef struct SList
{
  Node* first;
}SList;
//初始化
void SListinit(SList* slist)
{
  slist->first = NULL;
}
//头插
void SListPushFront(SList* slist, SListDataType v)
{
  //申请新节点
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = v;
  //更改链表的关系
  node->next = slist->first;
  slist->first = node;
  //考虑完空链表是一样的情况
}
//头删
void SListPopFront(SList* slist)
{
  //链表为空的情况
  assert(slist != NULL);
  Node* c = slist->first->next;
  free(slist->first);
  slist->first = c;
}
//尾插
void SListPushBack(SList* slist, SListDataType v)
{
  //创建新结点并且赋值
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = v;
  node->next = NULL;
  //如果链表为空
  if(slist->first == NULL)
  {
    slist->first = node;
    return;
  }
  //找链表的最后一个结点
  Node* c = slist->first;
  while(c->next != NULL)
  {
    c = c->next;
  }
  c->next = node;
}
//尾删
void SListPopBack(SList* slist)
{
  //处理为空的情况
  assert(slist->first != NULL);
  //处理只有一个结点的情况
  if(slist->first->next == NULL)
  {
    free(slist->first);
    slist->first = NULL;
    return;
  }  Node* c;
  //找到倒数第二个结点
  for(c = slist->first; c->next->next != NULL; c = c->next);
  free(c->next);
  c->next = NULL;
}
//逆置
//返回新链表的头节点地址
Node* SListReverse(SList* slist)
{
  Node* result = NULL;
  Node* c = slist->first;
  //遍历逐个处理
  //逐个将链表中的所有节点头插到新的结果链表中
  while(c != NULL)
  {
    Node* next = c->next;
    //头插
    c->next = result;
    result = c;
    c = next;
  }
  return result;
}
//查找
Node* SListFind(SList* slist, SListDataType v)
{
  for(Node* c = slist->first; c != NULL; c = c->next)
  {
    if(c->value == v)
    {
      return c;
    }
  }
  return NULL;
}
//在pos后做插入
void SListInsertAfter(Node* pos, SListDataType v)
{
  Node* node = (Node*)malloc(sizeof(Node));
  node->value = v;
  node->next = pos->next;
  pos->next = node;
}
//在pos后做删除
void SListEraseAfter(Node* pos)
{

  Node* c = pos->next->next;
  free(pos->next);
  pos->next = c;
}
//删除值为x的结点
void SListRemove(SList* slist, SListDataType v)
{
  //由于我们不能直接删除v本身的结点
  //因此需要用一个指针来判断是否需要删除他的下一个结点来保证不会出错
  //处理第一个结点
  if(slist->first->value == v)
  {
    SListPopFront(slist);
    return;
  }
  Node* c = slist->first;
  //逐个遍历判断每个结点的下一个结点是否需要删除
  while(c->next != NULL)
  {
    if(c->next->value == v)
    {
      SListEraseAfter(c->next);
    }
    c = c->next;
  }
}
//合并两个有序链表
Node* SListMergeTwoLists(SList* slist1, SList* slist2)
{
  Node* c1 = slist1->first;
  Node* c2 = slist2->first;
  Node* result = NULL;
  Node* last = NULL;
  if(c1 == NULL)
  {
    return c2;
  }
  if(c2 == NULL)
  {
    return c1;
  }
  while(c1 != NULL && c2 != NULL)
  {
    if(c1->value > c2->value)
    {
      if(last == NULL)
      {
        result = last = c1;
      }
      else
      {
        last->next = c1;
        last = c1;
      }
      c1 = c1->next;
    }
    if(c1->value < c2->value)
    {
      if(last == NULL)
      {
        result = last = c2;
      }
      else
      {
        last->next = c2;
        last = c2;
      }
      c2 = c2->next;
    }
  }
  last->next = NULL;
  if(c1 == NULL)
  {
    last->next = c2;
  }
  if(c2 == NULL)
  {
    last->next = c1;
  }
  return result;
}
//删除链表中所有值为v的结点
Node* SListRemoveAll(Node* head, int v)
{
  Node* result = NULL;//结果链表的头
  Node* last = NULL;//结果链表的尾
  Node* cur = head;
  while(cur != NULL)
  {
    if(cur->value !=v)
    {
      if(last == NULL)
      {
        result = last = cur;
      }
      else
      {
        last->next = cur;
        last = cur;
      }
    }
    cur = cur->next;
  }
  last->next = NULL;
  return result;
}
//分割一个个链表，使其前面为比x小的值，后面为比x大的值
Node* SListPartition(Node* pHead, int x)
{
  //定义两个不同的结果链表
  Node* resultSmallerThanx = NULL;//比x小的链表
  Node* resultBiggerThanx = NULL;//比x大的链表
  Node* c = pHead;
  Node* lastSmallerThanx = NULL;
  Node* lastBiggerThanx = NULL;
  while(c != NULL)
  {
    if(c->value < x)
    {
      if(resultSmallerThanx == NULL)
      {
        lastSmallerThanx = resultSmallerThanx = c;
      }
      else
      {
        lastSmallerThanx->next = c;
        lastSmallerThanx = c;
      }
    }
    if(c->value > x)
    {
      if(resultSmallerThanx == NULL)
      {
        lastSmallerThanx = resultSmallerThanx = c;
      }
      else
      {
        lastSmallerThanx->next = c;
        lastSmallerThanx = c;
      }
    }
    c = c->next;
  }
  //考虑特殊情况，结果链表有可能为空
  if(lastSmallerThanx != NULL)
  {
    lastSmallerThanx->next = resultBiggerThanx;
  }
  if(lastBiggerThanx != NULL)
  {
    lastBiggerThanx->next = NULL;
  }
  if(resultSmallerThanx != NULL)
  {
    return resultSmallerThanx;
  }
  else
  {
    return resultBiggerThanx;
  }
}
//链表的双指针遍历法（快慢指针）
//找到链表的中间结点
Node* SListMiddleNode(SList* slist)
{
  Node* fast = slist->first;
  Node* slow = slist->first;
  while(fast != NULL)
  {
    fast = fast->next;
    if(fast == NULL)
    {
      break;
    }
    slow = slow->next;
    fast = fast->next;
  }
  return slow;
}
//找到链表的倒数第k个结点
Node* SListFindKthTiTail(SList* slist, unsigned int k)
{
  Node* front = slist->first;
  Node* back = slist->first;
  //一个指针先走k步
  unsigned int i;
  for( i = 0; front != NULL && i < k; i++)
  {
    front = front->next;
  }
  //特殊情况，链表长度小于k
  if(i < k)
  {
    return NULL;
  }
  while(front != NULL)
  {
    front = front->next;
    back = back->next;
  }
  return back;
}
//求长度
int SListGetLength(SList* slist)
{
  int len = 0;
  for(Node* n = slist->first; !n; n = n->next)
  {
    len++;
  }
  return len;
}
//找到两个相交链表的相交结点，并返回其地址
//先找到长链表并让遍历它的指针先走两个链表的长度差步
//之后让两个链表上的遍历指针同步往前走，相交的地方就是链表相交的点
Node* SListGetIntersectionNOde(SList* slist1, SList* slist2)
{
  int lenA = SListGetLength(slist1);
  int lenB = SListGetLength(slist2);
  Node* longer = slist1->first;
  Node* shorter = slist2->first;
  int diff = lenA - lenB;
  if(lenA < lenB)
  {
    longer = slist2->first;
    shorter = slist1->first;
    diff = lenB - lenA;
  }
  for(int i = 0; i < diff; i++)
  {
    longer = longer->next;
  }
  while(shorter != longer)
  {
    shorter = shorter->next;
    longer = longer->next;
  }
  return longer;
}
//处理链表问题的特点：
//1、处理常规情况
//2、处理特殊情况。（通过增加头节点解决特殊情况）
