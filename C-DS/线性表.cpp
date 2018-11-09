#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERR 0
typedef int ElemType;
typedef int Status;
typedef struct _LNode//链表节点结构体 
{
	ElemType data;//数据区 
	struct _LNode* next;//指针区 
}LNode, *LinkList;
typedef struct _sqList
{
	ElemType* elem;//顺序表数据区 
	int length;//长度 
	int listSize;//顺序表的大小 
}SqList;
Status ListDelete_L(LinkList L, int i, ElemType* e)
{
	LinkList p = L;
	int j = 0;
	while(p->next && j < i - 1)
	{
		p = p->next;
		j++;
	}
	if(!(p->next) || (j > i - 1))
	{
		return ERR;
	}
	else
	{
		LinkList q = p->next;
		p->next = q->next;
		*e = q->data;
		free(q);
		return OK;
	}
}
Status PrintList_L(LinkList L)//打印链表 
{
	LinkList p = L->next;
	if(!p)
	{
		return ERR;
	}
	while(p)
	{
		printf("%d\t",p->data);
		p = p->next;
	}
	return OK;
} 
LinkList InitList_L()//链表的初始化 
{
	LinkList pHead = (LinkList)malloc(sizeof(LNode));//构建链表的头节点 
	pHead->next = NULL;
	return pHead;//返回带头节点链表的头指针 
}
Status GetElem_L(LinkList L, int i, ElemType* e)//读取链表中第i个节点的值，并且通过e返回 
{
	LinkList p = L->next;
	int j;
	for(j = 1; (j < i) && p; j++)//计数器 
	{
		p = p->next;
	}
	if(!p || (j > i))//查找失败 
	{
		return ERR;
	}
	else//查找成功 
	{
		*e = p->data;
		return OK;
	}
}
Status ListInsert_L(LinkList L, int i, ElemType e)//在链表中第i个位置前插入元素e 
{
	LinkList p = L;
	int j;
	for(j = 0; (j < i - 1) && p; j++)//找到第i-1个节点 
	{
		p = p->next;
	}
	if(!p || (j > i - 1))//i值不合法 
	{
		return ERR;	
	}
	else
	{
		LinkList s = (LinkList)malloc(sizeof(LNode));
		s->data = e;
		s->next = p->next;
		p->next = s;
		return OK;
	} 
}
Status InitList_Sq(SqList* L)//初始化 
{
	L->elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);//初始化顺序表 
	if(!L->elem)//分配空间失败 
	{
		return ERR;
	}
	L->length = 0;//初始化长度 
	L->listSize = LIST_INIT_SIZE;//初始化大小 
	return OK;
}
Status PrintList_Sq(SqList* L)//打印顺序表 
{
	for(int i = 0; i < L->length; i++)
	{
		printf("%d\t", L->elem[i]);
	} 
	return OK;
}
Status ListDelete_Sq(SqList* L, int i, ElemType* e)//删除操作（删除第i个数并且把它的值放在e中） 
{
	if((i < 1) || (i > L->length)) return 0;//i值不合法
	*e = L->elem[i - 1];//将e值返回出去
	for(int j = i - 1; j < L->length - 1; j++)//目标元素之后元素元素依次前移 
	{
		L->elem[j] = L->elem[j + 1];
	}
	L->length--;//长度-1 
	return OK; 
}
Status ListInsert_Sq(SqList* L, int i, ElemType e)//插入操作（在顺序表第i个位置前插入元素e） 
{
	if((i < 1) || (i > L->length + 1)) return ERR;//i值不合法
	if(L->length >= L->listSize)//空间不够重新分配空间 
	{
		ElemType* newbase = (ElemType*)realloc(L->elem, (L->listSize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)//分配失败 
		{
			return ERR;
		}
		else//分配成功 
		{
			L->elem = newbase;
			L->listSize = L->listSize + LISTINCREMENT;
		}
	}
	for(int j = L->length; j > i - 1; j--)//目标位置元素依次后移 
	{
		L->elem[j] = L->elem[j - 1];
	}
	L->elem[i - 1] = e;
	L->length++; 
} 
int main()
{
//	double dur;
//    clock_t start,end;
	SqList List;
	InitList_Sq(&List);//初始化线性表
	for(int i = 0; i < 10; i++)//构造线性表 
	{
		List.elem[i] = i;
		List.length++;
	}
	PrintList_Sq(&List);//打印 
	printf("\n");
	/**********************************/
	printf("删除第1个元素！\n");
	ElemType e;
	ListDelete_Sq(&List, 1, &e);
	PrintList_Sq(&List);//打印
	printf("\n");
	printf("删除元素为：%d\n",e);
	/***********************************/
	printf("在第一个位置插入0！\n");
	ListInsert_Sq(&List, 1, 0);
	PrintList_Sq(&List);//打印
	/************************************/ 
//	LinkList List = InitList_L();
//	ListInsert_L(List, 1, 1);
//	ListInsert_L(List, 2, 2);
//	ListInsert_L(List, 1, 0);
//	PrintList_L(List);
//	printf("\n");
//	ElemType e;
//	GetElem_L(List, 1, &e);
//	printf("第一个元素为：%d\n",e);
//	ListDelete_L(List, 1, &e);
//	printf("删除元素为：%d\n", e);
//	PrintList_L(List);
//	int e;
//	for(int i = 0; i < 10000; i++)
//	{
//		ListInsert_L(List, 1, i);
//	}
//	start = clock();
//	for(int i = 0; i < 10000; i++)
//	{
//		ListDelete_L(List, 1, &e);
//	}
//	end = clock();
//    dur = (double)(end - start);
//    printf("Use Time:%f\n",(dur/CLOCKS_PER_SEC));
} 
