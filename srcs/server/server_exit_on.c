#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

void		exit_on(char *str, char *file, int line)
{
	fprintf(stderr, "%s error (%s, %d): %s\n", 
		str, file, line, strerror(errno));
	exit(1);
}
