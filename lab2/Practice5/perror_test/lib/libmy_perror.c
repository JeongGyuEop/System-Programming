#include <stdio.h>
#include <errno.h>
#include <string.h>

// libmy_perror.c
extern void my_perror(const char *str)
{
	if(str == NULL)
		printf("%s",strerror(errno));
	else
		printf("%s : %s",str,strerror(errno));
}
