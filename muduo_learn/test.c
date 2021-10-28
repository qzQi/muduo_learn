#include<stdio.h>
#include<stdlib.h>

typedef int (*fun)();

static fun Do;
static int a()
{
	return printf("12345\n");
}
void never()
{
	Do=a;
}

int main()
{
	return Do();
}
