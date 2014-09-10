#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dumbvm.h"
#include "dumbasm.h"

void ASMLoadProgram(FILE *programFile, NanoVM *vm)
{
	int i = 0;
	uint16_t word;
	while(fscanf(programFile, "%hx", &word) != EOF)
	{
		vm->program[i++] = word;
	}
}


#ifdef ASM

int main (int argc, char const *argv[])
{
	
	return 0;
}

#endif