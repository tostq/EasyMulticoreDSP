#include <stdio.h>						// standard I/O needed for printf
#include <c6x.h>

void main(void) {
	int coreId = DNUM;
	printf("hello world from core %d\n", coreId);

	return;
}
