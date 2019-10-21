//链表反转
//https://leetcode-cn.com/problems/reverse-linked-list/submissions/
// Definition for singly-linked list.
#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
    //方法1,后删头插法
    ListNode *reverseList_1(ListNode *head)
    {
        if (head == NULL)
        {
            return head;
        }
        ListNode *oldHead = head;
        ListNode *temp = oldHead->next;
        while (oldHead->next != NULL)
        {
            oldHead->next = temp->next;
            temp->next = head;
            head = temp;
            temp = oldHead->next;
        }
        return head;
    }
    //方法2，向后转法
    ListNode* reverseList_2(ListNode* head) {
        if(head == NULL)
        {
            return head;
        }
        ListNode* prev = head;
        ListNode* cur = head->next;
        ListNode* next = cur;
        head->next = NULL;
        while(cur != NULL)
        {
            next = cur->next;
            cur->next = prev;
            prev = cur;
            cur = next;
        }
        return prev;
    }
};