#include <stdio.h>
#include <assert.h>
typedef struct
{
	int x;
	int y;
}RationalNum;//有理数 
typedef struct
{
	RationalNum x;
	RationalNum y;
}Fraction;//分数 
double plus(Fraction a, Fraction b)//加 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0);//基本条件 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) + ((b.x.x / b.x.y) / (b.y.x / b.y.y));//运算 
}
double minus(Fraction a, Fraction b)//减 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0);//基本条件 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) - ((b.x.x / b.x.y) / (b.y.x / b.y.y));//运算 
}
double mul(Fraction a, Fraction b)//乘 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0);//基本条件 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) * ((b.x.x / b.x.y) / (b.y.x / b.y.y));//运算 
}
double div(Fraction a, Fraction b)//除 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0 && ((b.x.x / b.x.y) / (b.y.x / b.y.y)) != 0);//基本条件 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) / ((b.x.x / b.x.y) / (b.y.x / b.y.y));//运算 
}
int main()
{
	
}
