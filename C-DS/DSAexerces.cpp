#include <stdio.h>
#include <stdlib.h>
typedef int ElemType;
typedef struct LNode
{
     ElemType  stu;
     struct LNode * pNext;
}LNode, * LinkedList;
/*
单链表的尾插
**/
int TailInsert(LinkedList list)
{
    int stu = 0;
    while(scanf("%d",&stu) != EOF)
    {
        LNode *node = (LNode *)malloc(sizeof(LNode));
        node->stu = stu;
        node->pNext = NULL;
        LinkedList p = list;
        if (p == NULL)
        {
            return 0;
        }
        while (p->pNext != NULL)
        {
            p = p->pNext;
        }
        p->pNext = node;
    }
    return 1;
}
/*
单链表的长度计算
**/
int LenOfList(LinkedList list)
{
    LinkedList p = list->pNext;
    int sum = 0;
    if(p == NULL)
    {
        return -1;
    }
    while(p != NULL)
    {
        sum++;
        p = p->pNext;
    }
    return sum;
}
LinkedList reverse(LinkedList list)
{
    //新建链表
    LinkedList newlist = (LNode *)malloc(sizeof(LNode));
    newlist->pNext = NULL;
    //将旧表以头插法重新插入新表中
    LinkedList p = list->pNext;
    while(p != NULL)
    {
        LNode* node = (LNode*)malloc(sizeof(LNode));
        node->pNext = newlist->pNext;
        newlist->pNext = node;
        node->stu = p->stu;
        p = p->pNext;
    }
    return newlist;
}

int main()
{
//    LinkedList list = NULL;//创建表头
//    LNode* node = (LNode*)malloc(sizeof(LNode));//创建表头结点
//    node->pNext = NULL;
//    list = node;
//    //建表
//    TailInsert(list);
//    //逆置
//    LinkedList list1 =  reverse(list);
//    //打印表
//    LinkedList p = list1->pNext;
//    while(p != NULL)
//    {
//        printf("%d\n",p->stu);
//        p = p->pNext;
//    }
//    printf("长度是：%d\n",LenOfList(list));//长度计算
    char arr[9][19][9][19] = {0};
    printf("%d\n",&arr[1][2][3][4] - &arr[0][0][0][0]);
    printf("%d\n",&arr[4][3][2][1] - &arr[0][0][0][0]);
}