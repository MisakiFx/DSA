#include <iostream>
#include <stack>
using namespace std;
//std::stack<int> s;
/**
 * void s.push()//压栈
 * void s.pop()//弹出
 * T s.top()//查看栈顶元素
 * int s,size()//查看栈的大小
 */
void Test()
{
  std::stack<int> s;
  s.push(1);
  s.push(3);
  s.push(9);
  printf("%d\n", s.top());
  s.pop();
  printf("%d\n", s.top());
  s.pop();
  printf("%d\n", s.top());
  printf("size: %d\n", s.size());
}
