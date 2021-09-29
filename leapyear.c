#include <stdio.h>

int leapyear(const int x);

int main(void){
	int x;
	printf("Type year : ");
	scanf("%d", &x);

	leapyear(x);
}

int leapyear(const int x){
	if ((x%4==0 && x%100!=0) || x%400==0)
		printf("This is leap year!\n");
	else
		printf("This is not leap year!\n");

	return 0;
}
