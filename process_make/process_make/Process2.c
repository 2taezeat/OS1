#include <stdio.h>
#include <time.h>

void Hanoi(int n, const char* src, const char* use, const char* dest);

int main(void)
{
	printf("P2 : Hanoi Top\n");
	printf("Process result : \n");
    Hanoi(6, "A", "B", "C");


	return 0;
}

void Hanoi(int n, const char* src, const char* use, const char* dest)
{
    if (n <= 0)
    {
        return;
    }
    Hanoi(n - 1, src, dest, use);
    printf("%s ¡æ %s\n", src, dest);
    Hanoi(n - 1, use, src, dest);
}