#include "SequenceList.h"
/**
初始化顺序表
所初始化的线性表指针，初始化要添加的元素内容数组，要添加的元素个数
将数组中的值赋到线性表的数据元素中
*/
void InitList(SeqList* seqlist, ElementType* elemarray, int length)
{
	seqlist->length = 0;
	if (length > MAX_SIZE)
	{
		printf("超出了数组的最大容量！初始化失败！");
	}
	for (int i = 0; i < length; i++)
	{
		//每个循环都插入一个元素
		InsertElemrnt(seqlist, i, elemarray[i]);
	}
}
/**
向顺序表中index下标处插入某个元素
要插入的链表，要插入的下标，要插入的元素
*/
void InsertElemrnt(SeqList* seqlist, int  index, ElementType element)
{
	//1、验证插入后的元素空间是否超过最大空间
	if (seqlist->length + 1 > MAX_SIZE)
	{
		printf("数组已满，插入元素失败！\n");
		return;
	}
	//2、Index的值是否合法[0, MAX_SIZE - 1]
	if (index < 0 || index > MAX_SIZE - 1)
	{
		printf("只能在允许的下标范围内插入元素！[0, %d]\n", MAX_SIZE - 1);
		return;
	}
	//3、插入的Index应该在length之内
	if (index > seqlist->length)
	{
		printf("插入的下标超过了数组的最大长度，插入失败！\n");
		return;
	}
	//4、从第length - 1个下标开始前面一个元素赋值给后面一个元素
	for (int i = seqlist->length - 1; i >= index; i--)
	{
		seqlist->datas[i + 1] = seqlist->datas[i];
	}
	//5、将要插入的值赋给index个下标
	seqlist->datas[index] = element;
	//6、顺序表的总长度+1
	seqlist->length++;
}
void PrintList(SeqList* seqlist)
{
	for (int i = 0; i < seqlist->length; i++)
	{
		printf("%d\t%s\n", seqlist->datas[i].id, seqlist->datas[i].name);
	}
}
/**
删除顺序表
*/
ElementType * DeletElement(SeqList * seqlist, int index)
{
	if (index < 0 || index > MAX_SIZE - 1)
	{
		printf("下标越界，无法删除指定下标的元素！\n");
		return NULL;
	}
	//1、找到要删除的元素，找到并保存以便返回
	ElementType* delElement = (ElementType*)malloc(sizeof(ElementType));//要删除元素
	//单独定义并调用查找函数，返回要删除元素的指针
	*delElement = *GetElement(seqlist, index);
	//2、从指定位置删除，后面一个元素赋值给前面一个元素
	for (int i = index; i < seqlist->length - 1; i++)
	{
		seqlist->datas[i] = seqlist->datas[i + 1];
	}
	//3、顺序表的总长度减1
	seqlist->length--;
	return delElement;   //建议使用完毕后进行内存释放
}

ElementType * GetElement(SeqList * seqlist, int index)
{
	if (index < 0 || index > MAX_SIZE - 1)
	{
		printf("下标越界，无法找到指定下标的元素！\n");
		return NULL;
	}
	ElementType* element;//要查找的元素
	element = &seqlist->datas[index];
	return element;
}
/**
得到长度
*/
int GetLength(SeqList * seqlist)
{
	if (seqlist == NULL)
		return 0;
	return seqlist->length;
}
/**
是否为空
*/
int isEmpty(SeqList * seqlist)
{
	return GetLength(seqlist) == 0 ? TRUE : FALSE;
}
/**
清空
*/
void ClearList(SeqList * seqlist)
{
	if (seqlist == NULL) return;
	seqlist->length = 0;
}
