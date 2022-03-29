#include <stdio.h>

int main()
{
	signed char a = -1;

	char b = -1;

	if((int)b == 255)
	{
		printf("default : unsigned char\n");
	}
	if((int)b == -1)
	{
		printf("default : signed char\n");
	}

	return 0;
}
