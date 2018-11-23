/*!
 * \文件名 LinkList.cpp
 * \日期 2018/11/23 15:33
 *
 * \作者 Misaki
 * 联系方式  1761607418@qq.com
 *
 * 文件描述: 单链表功能的具体实现
 *
*/
#include "LinkList.h"

void InitLinkList(LinkList* linkList, ElementType* dataArray, int length)
{
	for (int i = 0; i < length; i++)
	{
		InsertLinkList(linkList, i + 1, dataArray[i]);
	}
}

void InsertLinkList(LinkList* linkList, int pos, ElementType element)
{
	//1、创建空节点并为数据域赋值
	Node* node = (Node*)malloc(sizeof(Node));
	node->data = element;
	node->next = NULL;
	//2、找到要插入位置的前一个节点
	if (pos == 1)//特殊处理
	{
		node->next = linkList->next;
		linkList->next = node;
		linkList->length++;
		return;
	}
	Node* t = linkList->next;
	for (int i = 1; t && i < pos - 1; i++)
	{
		t = t->next;
	}
	if (t)
	{
		node->next = t->next;
		t->next = node;
		linkList->length++;
	}
	//3、将节点插入并对接前面的节点
}

void PrintLinkList(LinkList* linkList)
{
	Node* node = linkList->next;
	if (!node)
	{
		printf("链表为空！");
		linkList->length = 0;
		return;
	}
	for (int i = 0; i < linkList->length; i++)
	{
		printf("%d\t%s\n", node->data.id, node->data.name);
		node = node->next;
	}
}

int IsLinkListEmpty(LinkList* linkList)
{
	return linkList->length == 0 ? 1 : 0;
}

ElementType GetLinkListElementType(LinkList* linkList, int pos)
{
	Node* node = linkList->next;
	for (int i = 1; node && i < pos; i++)
	{
		node = node->next;
	}
	if (node)
	{
		return node->data;
	}
}

ElementType DeleteLinkListElement(LinkList* linkList, int pos)
{
	ElementType element;//被删除的元素的信息
	element.id = -1;//如果删除失败id为1
	Node* node = NULL;
	if (pos == 1)
	{
		node = linkList->next;
		if (node)
		{
			element = node->data;
			linkList->next = node->next;
			free(node);//释放被删除的节点的内存
			node = NULL;
			linkList->length--;
		}
		return element;
	}
	//寻找前置节点
	Node* preNode = NULL;
	node = linkList->next;
	for (int i = 1; node && i < pos; i++)
	{
		preNode = node;
		node = node->next;
	}
	if (node)
	{
		element = node->data;
		preNode->next = node->next;
		free(node);
		node = NULL;
		linkList->length--;
	}
	return element;
}

void CleanLinkList(LinkList* linkList, int length)
{
	for (int i = 0; i < length; i++)
	{
		DeleteLinkListElement(linkList, 1);
	}
}
