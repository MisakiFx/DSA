#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
//静态顺序表
//顺序表的容量是在编译期间（静态期间）决定的
//写死在代码里的
//typedef struct SeqList
//{
//  int array[100];//容量是100
//  int size;//当前顺序表里已经有的数据个数
//           //顺便表示了顺序表，最后插入的数据下表
//}SeqList;
//初始化的时候size = 0
//size = -1 //最后一个有效数据的下标


//动态顺序表
//顺序表的容量是在运行期间决定
typedef int SLDataType;
typedef struct SeqList
{
  SLDataType* array;
  int capacity;//容量
  int size;//长度
}SeqList;



//初始化
void SeqListInit(SeqList* seqlist, int capacity);
//销毁
void SeqListDestory(SeqList* seqlist);
//头插
void SeqListPushFront(SeqList* seqlist, SLDataType v);
//尾插
void SeqListPushBack(SeqList* seqlist, SLDataType v);
//中间插入
void SeqListInsert(SeqList* seqlist, int pos,  SLDataType v);
//尾删
void SeqListPopBack(SeqList* seqlist);
//头删
void SeqListPopFront(SeqList* seqlist);
//删除
void SeqListErase(SeqList* seqlist, int pos);
//修改
void SeqListModify(SeqList* seqlist, int pos, SLDataType v);
//查找
int SeqListFind(SeqList* seqlist, SLDataType v);
//打印
void SeqListPrint(SeqList* seqlist);
//删除第一次遇到的v
void SeqListRemove(SeqList* seqlist, SLDataType v);
//删除遇到的所有v
void SeqListRemoveAll(SeqList* seqlist, SLDataType v);
