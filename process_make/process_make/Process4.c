#include <stdio.h>
#include <time.h>
//double loop
int main(void) {

	printf("P4 : Double Loop\n");
	int sum1 = 0;
	for (int i = 0; i < 5000; i++)
	{
		for (int j = 0; j < 5000; j++)
		{
			sum1 = sum1 + i + j;
		}
	}
	printf("Process result : %d \n", sum1);

	return 0;
}



