#pragma once
#include <stdlib.h>
#include <stdio.h>
/*1、定义数据元素*/
//typedef int ElementType;
typedef struct _elementType
{
	int id;
	const char* name;
}ElementType;
/*定义链表的结点*/
typedef struct _node
{
	ElementType data;//数据域
	struct _node* next;//指针域，指向下个节点
}Node;
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
