#include <iostream>
#include <cassert>
#include "vector.h"//���������Լ�д�õ�vectorģ�����ʵ��
#include <cctype> 
#include <cmath>
#include <cstdlib>
#include <cstring>
#define N_OPTR 9
using namespace std;
template <class T> //ջ��ģ�� 
class Stack : public Vector<T>//���������� 
{
	public:
		void push(T const &e)
		{
			Vector<T>::insert(Vector<T>::size(), e);//��ջ 
		}
		T pop()
		{
			return Vector<T>::remove(Vector<T>::size() - 1);//��ջ 
		}
		T & top()
		{
			return (*this)[Vector<T>::size() - 1];
		} 
};
/**
����ת��������
*/ 
void convert(Stack<char> &S, int n, int base)
{
	static char digit[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};//�½����µ���λ���� 
	while(n > 0)
	{
		S.push(digit[n % base]);//������ջ
		n /= base;//����nֵ 
	}
	while(!S.empty())
	{
		cout << S.pop();
	 } 
}
/**
����������ƥ�� 
*/
bool paren(const char exp[], int lo, int hi)//ʹ��ջ���з��ż��ĺô����ڿ��ԶԶ������Ž�����ȷ�ļ�� 
{
	
	//���� 
	/* 
	Stack<char> S;//ʹ��ջ��¼�Ѿ����ֵ���δƥ���������
	for(int i = lo; i < hi; i++)
	{
		if('(' == exp[i])
		{
			S.push(exp[i]);
		}
		else if(!S.empty())//��������ջ�����򵯳������� 
		{
			S.pop();
		}
		else return false;//���������Ų���ջΪ����ƥ�� 
	} 
	return S.empty();//���ջ����ƥ�䣬�������ж�����������ƥ�� 
	*/
	//������
	Stack<char> S;
	for(int i = lo; i < hi; i++)//ѭ���ж����� 
	{
		switch(exp[i])
		{
			case '(':
			case '[':
			case '{':
				S.push(exp[i]);//������ͳһѹ��ջ 
				break;
			case ')'://���������ƥ���򽫶�Ӧ�����ŵ�����ջ 
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
	return S.empty();//ɨ�����ջ���Ƿ��в��������ţ��������˵����ƥ�� 
}
/**
���ʽ��ֵ���ӳٻ��壩 + �沨�����ʽ(RPN)
*/
//����������RPNβ��
void append(char*& rpn, float opnd)
{
	int n = strlen(rpn);//RPN��ǰ����
	char buf[64];
	if(opnd != (float)(int)opnd)
	{
		sprintf(buf, "%.2f \0", opnd);//�����ʽ 
	} 
	else
	{
		sprintf(buf, "%d \0", (int)opnd);//������ʽ 
	}
	rpn = (char*)realloc(rpn, sizeof(char) * (n + strlen(buf) + 1));//��չ�ռ�
	strcat (rpn, buf);//RPN�ӳ� 
} 
//���������RPNβ�� 
void append(char*& rpn, char optr)
{
	int n = strlen(rpn);//RPN��ǰ�ܳ���
	rpn = (char*)realloc(rpn, sizeof(char) * (n + 3));//����ռ�
	sprintf(rpn + n, "%c ", optr);
	rpn[n + 2] = '\0';//����ָ��������� 
} 
//���� 
float calcu(float pOpnd1, char op, float pOpnd2)//���������ǰ������ 
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
void readNumber(char* &p, Stack<float> &stk)//��S�е����ֶ���������ջ
{
	stk.push(*p - '0');//��ǰ��Ϊ��Ӧ����ֵ��ջ
	while(isdigit(*(++p)))//ֻҪ��һ���������־�ִ�����²��� 
	{
		stk.push(stk.pop() * 10 + (*p - '0'));//����ԭ��������׷������λ 
	}
	if('.' != *p) return;//����˺��ַ���ΪС�������ʾ�Ѿ�¼ȡ��˲�����
	float fraction = 1;//�˺���С����Ϊ����С����¼����׼��
	while(isdigit(*(++p)))
	{
		stk.push(stk.pop() + (*p - '0') * (fraction /= 10));//С������ 
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
char orderBetween(char op1, char op2)//�Ƚ����������֮������ȼ� 
{
	char t = pri[optr2rank(op1)][optr2rank(op2)];
	return t;
}
//�㷨������ 
float evaluate(char* S, char*& RPN)//�Ա��ʽs��ֵ����ת��Ϊ�沨��ʽRPN 
{
	Stack<float> opnd;//������ջ
	Stack<char> optr;//�����ջ
	optr.push('\0');//β�ڱ�'\0'������ջ
	while(!optr.empty())//�����ջ�ǿ�ʱ���������ʽ�и��ַ� 
	{//�������ջ�е�β�ڱ���ջ��������ѭ�� 
		if(isdigit(*S))//��ǰ�ַ�Ϊ������ 
		{
			readNumber(S, opnd);//��������� 
			append(RPN, opnd.top());
		}
		else
		{
			switch(orderBetween(optr.top(), *S))
			{
				case '<'://ջ����������ȼ���ʱ 
					optr.push(*S);//�����Ƴ٣���ǰ�������ջ 
					S++;
					break;
				case '='://���ȼ����ʱ����ǰ�����Ϊ�����Ż���β���ڱ��� 
					optr.pop();//������
					S++;//������һ���ַ�
					break;
				case '>':
					{
						char op = optr.pop();//ջ���������ջ����ִ����Ӧ����
						append(RPN, op);
						if('!' == op)//������һԪ����� 
						{
							float pOpnd = opnd.pop();//ֻ��ȡ��һ��������
							opnd.push(calcu(op, pOpnd)); 
						}
						else//����������Ԫ���ʽ 
						{
							float pOpnd1 = opnd.pop();//ȡ��������� 
							float pOpnd2 = opnd.pop();//ȡ��ǰ������
							opnd.push(calcu(pOpnd1, op, pOpnd2));//ʵ�ֶ�Ԫ���㣬�����ջ 
						}
						break;
					}
				default:
					exit(-1);
			}
		}
	} 
	return opnd.pop();//����������ջ���������� 
}
int main()
{

}
