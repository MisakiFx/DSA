#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "DataElement.h"
#define TRUE 1
#define FALSE 0
/**
初始化顺序表
所初始化的线性表指针，初始化要添加的元素内容数组，要添加的元素个数
将数组中的值赋到线性表的数据元素中
*/
void InitList(SeqList* seqList, ElementType* elemarray, int length);
/**
向顺序表中index下标处插入某个元素
要插入的链表，要插入的下标，要插入的元素
*/
void InsertElemrnt(SeqList* seqlist, int  index, ElementType element);
/**
打印顺序表
*/
void PrintList(SeqList* seqlist);
/**
删除元素
删除的顺序表， 下标
返回删除的元素,如果删除失败返回NULL
*/
ElementType* DeletElement(SeqList* seqlist, int index);
/**
查找元素
查找的顺序表， 下标
返回删除的元素,如果查找失败返回NULL
*/
ElementType* GetElement(SeqList* seqlist, int index);
/**
获得顺序表长度
操作的顺序表
*/
int GetLength(SeqList* seqlist);

/**
返回顺序表是否为空
*/
int isEmpty(SeqList* seqlist);

/**
清空顺序表
*/
void ClearList(SeqList * seqlist);