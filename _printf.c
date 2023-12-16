#include "main.h"

/**
 * _printf - a function that mimics the printf
 * command
 * @printout: the output of the function
 */

void _printf(const char *printout)
{
	fputs(printout, stdout);
}
