#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "dumbdebug.h"

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

/**
** Prints out the value of the four main registers
**
** @param NanoVM *vm the virtual machine to debug
*/
void VMDebug(NanoVM *vm)
{
	for(int i = 0; i < 4; ++i)
	{
		printf("%03d ", vm->registers[i]);
	}
	printf("\n");
	for(int i = 4; i < NUM_REGISTERS; ++i)
	{
		printf("%03d ", vm->registers[i]);
	}
	printf("\n");
	printf("OpCode: 0x%2x\n", vm->instruction);
	getchar();
}