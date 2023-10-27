#include <stdio.h>
#include <stdlib.h>
#include "libmy_assert.h"

void my_assert_fail (const char *assertion, const char *file, unsigned int line, const char *function) {
	
	printf("%s:%s:%u:%s:Assertion '%s' failed.", __progname, file, line, function, assertion);
	
	abort();
}
