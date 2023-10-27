#include <stdio.h>
#include "libmy_assert.h"
#include <stdlib.h>

void foo(int num)
{
	my_assert(((num >=0) && (num <=100)));
	printf("foo : num = %d\n", num);
}

void main(int argc, char *argv[])
{
	int num;

	if (argc<2) {

		fprintf(stderr,"Usage : assert_test a Number\n(0 <= aNumber<=100)\n");
		exit(1);
	}

	num = atoi(argv[1]);
	foo(num);
}
