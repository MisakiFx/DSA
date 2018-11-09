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
	printf("\n删除后\n");
	PrintList(&seqlist);
	printf("\n被删除的元素：\n");
	printf("%d\t%s\n", delElement->id, delElement->name);
	free(delElement);
}
