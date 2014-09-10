#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "nanovm.h"
#include "nanoasm.h"

void ASMLoadProgram(FILE *programFile, NanoVM *vm)
{
	int i = 0;
	uint16_t opcode;
	while(fscanf(programFile, "%hx", &opcode) != EOF)
	{
		vm->program[i++] = opcode;
	}
}