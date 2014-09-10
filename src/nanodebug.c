#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "nanodebug.h"

/**
** Exits the VM with an error message
**
** @param char[] message
*/
void die(char message[])
{
	fprintf(stderr, "Error: %s\nShutting down...\n", message);
	exit(1);
}