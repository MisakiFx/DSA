#include <stdio.h>
#include <string.h>
#include "LinkList.h"
/*!
 * \项目名 单向链表示例
 * \日期 2018/11/13 1:31
 *
 * \作者 Misaki
 * 联系方式  1761607418@qq.com
 *
 * 文件描述: 链表抽象数据类型的定义，每个链表都有后继节点，优点是存储的高效
 *
*/
ElementType dataArray[] = {
	{1, "Misaki"},
	{2, "MisakiFx"},
	{3, "Misakifx"},
	{4, "MisakiFX"},
};
void TestLinkList()
{
	LinkList linkList;
	linkList.length = 0;
	InitLinkList(&linkList, dataArray, sizeof(dataArray) / sizeof(dataArray[0]));
	PrintLinkList(&linkList);
}
int main()
{
	TestLinkList();
	system("pause");
}