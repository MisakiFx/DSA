#pragma once
#define MAX_SIZE 255
/**
��������Ԫ��
*/
//1����������Ԫ��
//typedef int Element;
typedef struct
{
	int id;
	const char* name;
}ElementType;
//2������˳���ṹ���ࣩ
typedef struct
{
	ElementType datas[MAX_SIZE];    //˳����е�Ԫ�ؽ��
	int length;                                       //��ǰ˳����е�Ԫ�ظ���
}SeqList;
