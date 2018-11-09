#include "SequenceList.h"
/**
��ʼ��˳���
����ʼ�������Ա�ָ�룬��ʼ��Ҫ��ӵ�Ԫ���������飬Ҫ��ӵ�Ԫ�ظ���
�������е�ֵ�������Ա������Ԫ����
*/
void InitList(SeqList* seqlist, ElementType* elemarray, int length)
{
	seqlist->length = 0;
	if (length > MAX_SIZE)
	{
		printf("����������������������ʼ��ʧ�ܣ�");
	}
	for (int i = 0; i < length; i++)
	{
		//ÿ��ѭ��������һ��Ԫ��
		InsertElemrnt(seqlist, i, elemarray[i]);
	}
}
/**
��˳�����index�±괦����ĳ��Ԫ��
Ҫ���������Ҫ������±꣬Ҫ�����Ԫ��
*/
void InsertElemrnt(SeqList* seqlist, int  index, ElementType element)
{
	//1����֤������Ԫ�ؿռ��Ƿ񳬹����ռ�
	if (seqlist->length + 1 > MAX_SIZE)
	{
		printf("��������������Ԫ��ʧ�ܣ�\n");
		return;
	}
	//2��Index��ֵ�Ƿ�Ϸ�[0, MAX_SIZE - 1]
	if (index < 0 || index > MAX_SIZE - 1)
	{
		printf("ֻ����������±귶Χ�ڲ���Ԫ�أ�[0, %d]\n", MAX_SIZE - 1);
		return;
	}
	//3�������IndexӦ����length֮��
	if (index > seqlist->length)
	{
		printf("������±곬�����������󳤶ȣ�����ʧ�ܣ�\n");
		return;
	}
	//4���ӵ�length - 1���±꿪ʼǰ��һ��Ԫ�ظ�ֵ������һ��Ԫ��
	for (int i = seqlist->length - 1; i >= index; i--)
	{
		seqlist->datas[i + 1] = seqlist->datas[i];
	}
	//5����Ҫ�����ֵ����index���±�
	seqlist->datas[index] = element;
	//6��˳�����ܳ���+1
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
ɾ��˳���
*/
ElementType * DeletElement(SeqList * seqlist, int index)
{
	if (index < 0 || index > MAX_SIZE - 1)
	{
		printf("�±�Խ�磬�޷�ɾ��ָ���±��Ԫ�أ�\n");
		return NULL;
	}
	//1���ҵ�Ҫɾ����Ԫ�أ��ҵ��������Ա㷵��
	ElementType* delElement = (ElementType*)malloc(sizeof(ElementType));//Ҫɾ��Ԫ��
	//�������岢���ò��Һ���������Ҫɾ��Ԫ�ص�ָ��
	*delElement = *GetElement(seqlist, index);
	//2����ָ��λ��ɾ��������һ��Ԫ�ظ�ֵ��ǰ��һ��Ԫ��
	for (int i = index; i < seqlist->length - 1; i++)
	{
		seqlist->datas[i] = seqlist->datas[i + 1];
	}
	//3��˳�����ܳ��ȼ�1
	seqlist->length--;
	return delElement;   //����ʹ����Ϻ�����ڴ��ͷ�
}

ElementType * GetElement(SeqList * seqlist, int index)
{
	if (index < 0 || index > MAX_SIZE - 1)
	{
		printf("�±�Խ�磬�޷��ҵ�ָ���±��Ԫ�أ�\n");
		return NULL;
	}
	ElementType* element;//Ҫ���ҵ�Ԫ��
	element = &seqlist->datas[index];
	return element;
}
/**
�õ�����
*/
int GetLength(SeqList * seqlist)
{
	if (seqlist == NULL)
		return 0;
	return seqlist->length;
}
/**
�Ƿ�Ϊ��
*/
int isEmpty(SeqList * seqlist)
{
	return GetLength(seqlist) == 0 ? TRUE : FALSE;
}
/**
���
*/
void ClearList(SeqList * seqlist)
{
	if (seqlist == NULL) return;
	seqlist->length = 0;
}
