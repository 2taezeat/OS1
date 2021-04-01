#include <stdio.h>
//int gcd(int x_i, int y_i, int go_i)
//{	
//	int g,x,y;
//	while (1)
//	{
//		while (!go);
//		x = x_i;
//		y = y_i;
//		while (x != y) {
//			if (x < y)
//				y = y - x;
//			else
//				x = x - y;
//		}
//		g = x;
//		return g ;
//	}
//}
int lcm(int x_i, int y_i, int go_i)
{
	int g, x, y, l;
	while (1)
	{
		while (!go_i)
		{}
	
		x = x_i;
		y = y_i;
		while (x != y) {
			if (x < y)
				y = y - x;
			else
				x = x - y;
		}
		g = x;
		l = x_i * y_i / g;
		return l;
	}
}


int main(void) {
	//int result = gcd(12, 4, 1);
	int result = lcm(12, 5, 1);
	printf("%d",result);

}