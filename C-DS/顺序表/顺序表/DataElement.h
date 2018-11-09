#pragma once
#define MAX_SIZE 255
/**
定义数据元素
*/
//1、定义数据元素
//typedef int Element;
typedef struct
{
	int id;
	const char* name;
}ElementType;
//2、定义顺序表结构（类）
typedef struct
{
	ElementType datas[MAX_SIZE];    //顺序表中的元素结合
	int length;                                       //当前顺序表中的元素个数
}SeqList;
