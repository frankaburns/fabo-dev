#include <stdio.h>

struct Test {
	unsigned int a;
	unsigned int b:3;
}
int main () {
	struct Test t;
	int *aptr = &t.a;
	printf ("address of a: 0x%x\n", aptr);

	int *bptr = &t.b;
	printf ("address of b: 0x%x\n", bptr);

	return 0;
}
