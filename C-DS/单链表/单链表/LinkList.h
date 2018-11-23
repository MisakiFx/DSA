#pragma once
/*!
 * \文件名 LinkList.h
 * \日期 2018/11/23 15:32
 *
 * \作者 Misaki
 * 联系方式  1761607418@qq.com
 *
 * 文件描述: 单链表的定义
 *
*/
#include <stdlib.h>
#include <stdio.h>
#include "DataElement.h"
/*
定义链表头节点
一遍对链表的插入和删除操作达成统一，也称为首元节点
*/
typedef struct _linkList
{
	Node* next;//链表头节点
	int length;//链表的长度
}LinkList;
/*初始化链表*/
void InitLinkList(LinkList* linkList, ElementType* dataArray, int length);
/*在指定的位置pos处插入元素element*/
void InsertLinkList(LinkList* linkList, int pos, ElementType element);
/*打印链表*/
void PrintLinkList(LinkList* linkList);
/*是否为空*/
int IsLinkListEmpty(LinkList* linkList);
/*得到pos位置的元素*/
ElementType GetLinkListElementType(LinkList* linkList, int pos);
/*删除节点并返回指定位置的节点*/
ElementType DeleteLinkListElement(LinkList* linkList, int pos);
/*清空链表*/
void CleanLinkList(LinkList* linkList, int length);
