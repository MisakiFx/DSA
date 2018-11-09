#include <stdio.h>
#include <assert.h>
typedef struct
{
	int x;
	int y;
}RationalNum;//������ 
typedef struct
{
	RationalNum x;
	RationalNum y;
}Fraction;//���� 
double plus(Fraction a, Fraction b)//�� 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0);//�������� 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) + ((b.x.x / b.x.y) / (b.y.x / b.y.y));//���� 
}
double minus(Fraction a, Fraction b)//�� 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0);//�������� 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) - ((b.x.x / b.x.y) / (b.y.x / b.y.y));//���� 
}
double mul(Fraction a, Fraction b)//�� 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0);//�������� 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) * ((b.x.x / b.x.y) / (b.y.x / b.y.y));//���� 
}
double div(Fraction a, Fraction b)//�� 
{
	assert(a.x.y > 0 && a.y.y > 0 && b.x.y > 0 && b.y.y > 0 && (a.y.x / a.y.y) != 0 && (b.y.x / b.y.y) != 0 && ((b.x.x / b.x.y) / (b.y.x / b.y.y)) != 0);//�������� 
	return ((a.x.x / a.x.y) / (a.y.x / a.y.y)) / ((b.x.x / b.x.y) / (b.y.x / b.y.y));//���� 
}
int main()
{
	
}
