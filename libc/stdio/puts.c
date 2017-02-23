#include <stack_chk.h>
#include <stdio.h>

int puts(const char *s)
{
	return printf("%s\n", s);
}
