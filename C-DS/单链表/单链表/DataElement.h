#pragma once
/*!
 * \文件名 DataElement.h
 * \日期 2018/11/23 15:32
 *
 * \作者 Misaki
 * 联系方式  1761607418@qq.com
 *
 * 文件描述: 数据元素以及链表节点的定义
 *
*/
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
