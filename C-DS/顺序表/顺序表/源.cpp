#include <stdio.h>
#include "SequenceList.h"
ElementType dataArray[] = {
	{ 1,"Misaki" },
	{ 2,"SasiGay" },
	{ 3,"Mei" },
	{ 4,"fuxiang" },
};
void test();
int main()
{
	test();
}
void test()
{
	SeqList seqlist;
	ElementType* delElement;
	InitList(&seqlist, dataArray, 4);
	PrintList(&seqlist);
	delElement = DeletElement(&seqlist, 2);
	printf("\nɾ����\n");
	PrintList(&seqlist);
	printf("\n��ɾ����Ԫ�أ�\n");
	printf("%d\t%s\n", delElement->id, delElement->name);
	free(delElement);
}
