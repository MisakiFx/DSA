#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "DataElement.h"
#define TRUE 1
#define FALSE 0
/**
��ʼ��˳���
����ʼ�������Ա�ָ�룬��ʼ��Ҫ��ӵ�Ԫ���������飬Ҫ��ӵ�Ԫ�ظ���
�������е�ֵ�������Ա������Ԫ����
*/
void InitList(SeqList* seqList, ElementType* elemarray, int length);
/**
��˳�����index�±괦����ĳ��Ԫ��
Ҫ���������Ҫ������±꣬Ҫ�����Ԫ��
*/
void InsertElemrnt(SeqList* seqlist, int  index, ElementType element);
/**
��ӡ˳���
*/
void PrintList(SeqList* seqlist);
/**
ɾ��Ԫ��
ɾ����˳��� �±�
����ɾ����Ԫ��,���ɾ��ʧ�ܷ���NULL
*/
ElementType* DeletElement(SeqList* seqlist, int index);
/**
����Ԫ��
���ҵ�˳��� �±�
����ɾ����Ԫ��,�������ʧ�ܷ���NULL
*/
ElementType* GetElement(SeqList* seqlist, int index);
/**
���˳�����
������˳���
*/
int GetLength(SeqList* seqlist);

/**
����˳����Ƿ�Ϊ��
*/
int isEmpty(SeqList* seqlist);

/**
���˳���
*/
void ClearList(SeqList * seqlist);