#include <stdio.h>
#include <assert.h>
typedef struct
{
	int x;
	int y;
}RationalNum;//有理数 
double plus(RationalNum a, RationalNum b)//加 
{
	assert(a.y > 0 && b.y > 0);
	return ((double)a.x / a.y) + ((double)b.x / b.y);
}
double minus(RationalNum a, RationalNum b)//减 
{
	assert(a.y > 0 && b.y > 0);
	return ((double)a.x / a.y) - ((double)b.x / b.y);
}
double mul(RationalNum a, RationalNum b)//乘 
{
	assert(a.y > 0 && b.y > 0);
	return ((double)a.x / a.y) * ((double)b.x / b.y);
}
double div(RationalNum a, RationalNum b)//除 
{
	assert(a.y > 0 && b.y > 0 && (b.x / b.y) != 0);
	return ((double)a.x / a.y) / ((double)b.x / b.y);
}
int main()
{
	
}
