#include <iostream>
#include <cassert>
#include "vector.h"//引入我们自己写好的vector模版进行实现
#include <cctype> 
#include <cmath>
#include <cstdlib>
#include <cstring>
#define N_OPTR 9
using namespace std;
template <class T> //栈类模板 
class Stack : public Vector<T>//由向量派生 
{
	public:
		void push(T const &e)
		{
			Vector<T>::insert(Vector<T>::size(), e);//入栈 
		}
		T pop()
		{
			return Vector<T>::remove(Vector<T>::size() - 1);//出栈 
		}
		T & top()
		{
			return (*this)[Vector<T>::size() - 1];
		} 
};
/**
进制转换迭代版
*/ 
void convert(Stack<char> &S, int n, int base)
{
	static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};//新进制下的数位符号 
	while(n > 0)
	{
		S.push(digit[n % base]);//余数入栈
		n /= base;//更新n值 
	}
	while(!S.empty())
	{
		cout << S.pop();
	 } 
}
/**
迭代版括号匹配 
*/
bool paren(const char exp[], int lo, int hi)//使用栈进行符号检查的好处在于可以对多种括号进行正确的检查 
{
	
	//简洁版 
	/* 
	Stack<char> S;//使用栈记录已经发现但尚未匹配的左括号
	for(int i = lo; i < hi; i++)
	{
		if('(' == exp[i])
		{
			S.push(exp[i]);
		}
		else if(!S.empty())//遇右括号栈不空则弹出左括号 
		{
			S.pop();
		}
		else return false;//遇到右括号并且栈为空则不匹配 
	} 
	return S.empty();//如果栈空则匹配，不空则有多余左括号则不匹配 
	*/
	//完整版
	Stack<char> S;
	for(int i = lo; i < hi; i++)//循环判断括号 
	{
		switch(exp[i])
		{
			case '(':
			case '[':
			case '{':
				S.push(exp[i]);//左括号统一压入栈 
				break;
			case ')'://右括号如果匹配则将对应左括号弹出出栈 
				if( (S.empty()) || ('(' != S.pop())) return false;
				break;
			case ']':
				if( (S.empty()) || ('[' != S.pop())) return false;
				break;
			case '}':
				if( (S.empty()) || ('{' != S.pop())) return false;
				break;
		}
	} 
	return S.empty();//扫描过后看栈中是否有残留的括号，如果有则说明不匹配 
}
/**
表达式求值（延迟缓冲） + 逆波兰表达式(RPN)
*/
//运算数接至RPN尾部
void append(char*& rpn, float opnd)
{
	int n = strlen(rpn);//RPN当前长度
	char buf[64];
	if(opnd != (float)(int)opnd)
	{
		sprintf(buf, "%.2f \0", opnd);//浮点格式 
	} 
	else
	{
		sprintf(buf, "%d \0", (int)opnd);//整数形式 
	}
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1));//扩展空间
	strcat (rpn, buf);//RPN加长 
} 
//运算符接至RPN尾部 
void append(char*& rpn, char optr)
{
	int n = strlen(rpn);//RPN当前总长度
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3));//扩充空间
	sprintf(rpn + n, "%c ", optr);
	rpn[n + 2] = '\0';//接入指定的运算符 
} 
//计算 
float calcu(float pOpnd1, char op, float pOpnd2)//后操作数，前操作数 
{
	switch(op)
	{
		case '+':
			return pOpnd1 + pOpnd2;
			break;
		case '-':
			return pOpnd2 - pOpnd1;
			break;
		case '*':
			return pOpnd1 * pOpnd2;
			break;
		case '/':
			if(pOpnd1 == 0)
			{
				exit(-1);
			}
			return pOpnd2 / pOpnd1;
			break;
		case '^':
			return pow(pOpnd2, pOpnd1);
			break;
		default:
			exit(-1);
			break;
			
	}
}
float calcu(char op, float pOpnd)
{
	switch(op)
	{
		case '!':
			{
				float sum = 1;
				while(pOpnd > 0)
				{
					sum *= pOpnd--;
				}
				return sum;
				break;
			}
		default:
			break;
	}
}
void readNumber(char* &p, Stack<float> &stk)//将S中的数字读入运算数栈
{
	stk.push(*p - '0');//当前数为对应的数值入栈
	while(isdigit(*(++p)))//只要下一个还是数字就执行以下操作 
	{
		stk.push(stk.pop() * 10 + (*p - '0'));//弹出原操作数并追加新数位 
	}
	if('.' != *p) return;//如果此后字符不为小数点则表示已经录取完此操作数
	float fraction = 1;//此后还有小数点为后续小数点录入做准备
	while(isdigit(*(++p)))
	{
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10));//小数部分 
	} 
}
typedef enum 
{
	ADD = 0,//+ 
	SUB,//- 
	MUL,//* 
	DIV,/// 
	POW,//^ 
	FAC,//!
	L_P,//(
	R_P,//)
	EOE //'\0'
}Operator;
const char pri[N_OPTR][N_OPTR] = {
	{'>','>','<','<','<','<','<','>','>'},
	{'>','>','<','<','<','<','<','>','>'},
	{'>','>','>','>','<','<','<','>','>'},
	{'>','>','>','>','<','<','<','>','>'},
	{'>','>','>','>','>','<','<','>','>'},
	{'>','>','>','>','>','>',' ','>','>'},
	{'<','<','<','<','<','<','<','=',' '},
	{' ',' ',' ',' ',' ',' ',' ',' ',' '},
	{'<','<','<','<','<','<','<','<','='},
};
Operator optr2rank(char op)
{
	switch(op)
	{
		case '+':
			return ADD;
		case '-':
			return SUB;
		case '*':
			return MUL;
		case '/':
			return DIV;
		case '^':
			return POW;
		case '!':
			return FAC;
		case '(':
			return L_P;
		case ')':
			return R_P;
		case '\0':
			return EOE;
		default:
			exit(-1);
	}
} 
char orderBetween(char op1, char op2)//比较两个运算符之间的优先级 
{
	char t = pri[optr2rank(op1)][optr2rank(op2)];
	return t;
}
//算法主函数 
float evaluate(char* S, char*& RPN)//对表达式s求值，并转换为逆波兰式RPN 
{
	Stack<float> opnd;//运算数栈
	Stack<char> optr;//运算符栈
	optr.push('\0');//尾哨兵'\0'首先入栈
	while(!optr.empty())//运算符栈非空时逐个处理表达式中各字符 
	{//当运算符栈中的尾哨兵出栈后结束真个循环 
		if(isdigit(*S))//当前字符为操作数 
		{
			readNumber(S, opnd);//读入操作数 
			append(RPN, opnd.top());
		}
		else
		{
			switch(orderBetween(optr.top(), *S))
			{
				case '<'://栈顶运算符优先级低时 
					optr.push(*S);//计算推迟，当前运算符进栈 
					S++;
					break;
				case '='://优先级相等时（当前运算符为右括号或者尾部哨兵） 
					optr.pop();//脱括号
					S++;//接收下一个字符
					break;
				case '>':
					{
						char op = optr.pop();//栈顶运算符出栈并且执行相应操作
						append(RPN, op);
						if('!' == op)//若属于一元运算符 
						{
							float pOpnd = opnd.pop();//只需取出一个操作数
							opnd.push(calcu(op, pOpnd)); 
						}
						else//对于其他二元表达式 
						{
							float pOpnd1 = opnd.pop();//取出后操作数 
							float pOpnd2 = opnd.pop();//取出前操作数
							opnd.push(calcu(pOpnd1, op, pOpnd2));//实现二元计算，结果入栈 
						}
						break;
					}
				default:
					exit(-1);
			}
		}
	} 
	return opnd.pop();//弹出操作数栈的最后计算结果 
}
int main()
{

}
