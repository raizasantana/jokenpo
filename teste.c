#include<stdlib.h>
#include<stdio.h>

typedef struct
{
	char *boca;
} teste;

teste oi()
{
	teste k;
	k.boca = "ghsuahau";
	return k;
}
int main()
{
	teste ole = oi();
	printf("%s\n",ole.boca);
	
}
