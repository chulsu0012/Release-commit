#include <stdio.h>

void fibonacci(int* n);

int main(void) {
	int n;
	scanf("%d", &n);
	fibonacci(&n);
	printf("%d\n", n);
	return 0;
}

void fibonacci(int* n) {
	int a = 0, b = 1;
	for (int i = 0; i < *n - 1; i++) {
		if (i % 2 == 0)
			a = a + b;
		else
			b = a + b;
	}
	if (a > b)
		*n = a;
	else
		*n = b;
}
