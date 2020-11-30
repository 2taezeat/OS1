#include <stdio.h>
#include <time.h>

int main(void)
{	

	int i = 0;
	while (i < 10000000)
	{
		i = i + 1;
	}

	printf("P1 : Simple loop\n");
	printf("Process result : %d\n", i);
	

	return 0;
}