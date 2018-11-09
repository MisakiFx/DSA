#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
#define OK 1
#define ERR 0
typedef int ElemType;
typedef int Status;
typedef struct _LNode//����ڵ�ṹ�� 
{
	ElemType data;//������ 
	struct _LNode* next;//ָ���� 
}LNode, *LinkList;
typedef struct _sqList
{
	ElemType* elem;//˳��������� 
	int length;//���� 
	int listSize;//˳���Ĵ�С 
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
Status PrintList_L(LinkList L)//��ӡ���� 
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
LinkList InitList_L()//����ĳ�ʼ�� 
{
	LinkList pHead = (LinkList)malloc(sizeof(LNode));//���������ͷ�ڵ� 
	pHead->next = NULL;
	return pHead;//���ش�ͷ�ڵ������ͷָ�� 
}
Status GetElem_L(LinkList L, int i, ElemType* e)//��ȡ�����е�i���ڵ��ֵ������ͨ��e���� 
{
	LinkList p = L->next;
	int j;
	for(j = 1; (j < i) && p; j++)//������ 
	{
		p = p->next;
	}
	if(!p || (j > i))//����ʧ�� 
	{
		return ERR;
	}
	else//���ҳɹ� 
	{
		*e = p->data;
		return OK;
	}
}
Status ListInsert_L(LinkList L, int i, ElemType e)//�������е�i��λ��ǰ����Ԫ��e 
{
	LinkList p = L;
	int j;
	for(j = 0; (j < i - 1) && p; j++)//�ҵ���i-1���ڵ� 
	{
		p = p->next;
	}
	if(!p || (j > i - 1))//iֵ���Ϸ� 
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
Status InitList_Sq(SqList* L)//��ʼ�� 
{
	L->elem = (ElemType*)malloc(sizeof(ElemType) * LIST_INIT_SIZE);//��ʼ��˳��� 
	if(!L->elem)//����ռ�ʧ�� 
	{
		return ERR;
	}
	L->length = 0;//��ʼ������ 
	L->listSize = LIST_INIT_SIZE;//��ʼ����С 
	return OK;
}
Status PrintList_Sq(SqList* L)//��ӡ˳��� 
{
	for(int i = 0; i < L->length; i++)
	{
		printf("%d\t", L->elem[i]);
	} 
	return OK;
}
Status ListDelete_Sq(SqList* L, int i, ElemType* e)//ɾ��������ɾ����i�������Ұ�����ֵ����e�У� 
{
	if((i < 1) || (i > L->length)) return 0;//iֵ���Ϸ�
	*e = L->elem[i - 1];//��eֵ���س�ȥ
	for(int j = i - 1; j < L->length - 1; j++)//Ŀ��Ԫ��֮��Ԫ��Ԫ������ǰ�� 
	{
		L->elem[j] = L->elem[j + 1];
	}
	L->length--;//����-1 
	return OK; 
}
Status ListInsert_Sq(SqList* L, int i, ElemType e)//�����������˳����i��λ��ǰ����Ԫ��e�� 
{
	if((i < 1) || (i > L->length + 1)) return ERR;//iֵ���Ϸ�
	if(L->length >= L->listSize)//�ռ䲻�����·���ռ� 
	{
		ElemType* newbase = (ElemType*)realloc(L->elem, (L->listSize + LISTINCREMENT) * sizeof(ElemType));
		if(!newbase)//����ʧ�� 
		{
			return ERR;
		}
		else//����ɹ� 
		{
			L->elem = newbase;
			L->listSize = L->listSize + LISTINCREMENT;
		}
	}
	for(int j = L->length; j > i - 1; j--)//Ŀ��λ��Ԫ�����κ��� 
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
	InitList_Sq(&List);//��ʼ�����Ա�
	for(int i = 0; i < 10; i++)//�������Ա� 
	{
		List.elem[i] = i;
		List.length++;
	}
	PrintList_Sq(&List);//��ӡ 
	printf("\n");
	/**********************************/
	printf("ɾ����1��Ԫ�أ�\n");
	ElemType e;
	ListDelete_Sq(&List, 1, &e);
	PrintList_Sq(&List);//��ӡ
	printf("\n");
	printf("ɾ��Ԫ��Ϊ��%d\n",e);
	/***********************************/
	printf("�ڵ�һ��λ�ò���0��\n");
	ListInsert_Sq(&List, 1, 0);
	PrintList_Sq(&List);//��ӡ
	/************************************/ 
//	LinkList List = InitList_L();
//	ListInsert_L(List, 1, 1);
//	ListInsert_L(List, 2, 2);
//	ListInsert_L(List, 1, 0);
//	PrintList_L(List);
//	printf("\n");
//	ElemType e;
//	GetElem_L(List, 1, &e);
//	printf("��һ��Ԫ��Ϊ��%d\n",e);
//	ListDelete_L(List, 1, &e);
//	printf("ɾ��Ԫ��Ϊ��%d\n", e);
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
