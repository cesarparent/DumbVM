#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dumbvm.h"
#include "dumbdebug.h"
#include "dumbasm.h"
#include "asmcallbacks.h"



/**
** Returns the ASMCommand value for the current line
**
** @param const char *line the assembly code line to decode
** @return ASMCommand the command value
*/
ASMCommand ASMinstructionForLine(const char *line)
{
	char operation[4];
	sscanf(line, "%s", operation);
	ASMCommand command = 0;
	while(strcmp(operation,commands[command]))
	{
		if(command < JNZ)
		{
			++command;
		}
		else
		{
			return HLT;
		}
	}
	return command;
}

/**
** Assembles the programme file into machine code
**
** @param FILE *programFile the assembly file
** @return void
*/
void ASMAssembleProgram(FILE *programFile)
{
	tokenCallack callbacks[] = {
		asmHalt,
		asmMove,
		asmCopy,
		asmAdd,
		asmSub,
		asmMult,
		asmDiv,
		asmJump,
		asmJumpNZ
	};
	char currentLine[MAX_LINE_LENGTH];
	int length = 0;
	uint16_t assembledProgram[MAX_PROGRAM_LENGTH]= {0x0000};
	
	while(fgets(currentLine, MAX_LINE_LENGTH, programFile))
	{
		ASMCommand instr = ASMinstructionForLine(currentLine);
		assembledProgram[length++] = callbacks[instr](currentLine);
	}
	FILE *assembledFile = fopen("run.d", "w");
	if(assembledFile == NULL) die ("Error writing assembled program");
	fwrite(assembledProgram, sizeof (uint16_t), length, assembledFile);
	fclose(assembledFile);
}

/**
** Assembles the program file, then reads the assembled output
** and loads it into the program memory for execution
**
** @param FILE *programFile the file containing the assembly program
** NanoVM *vm the VM in which to load the program
*/
void ASMLoadProgram(FILE *programFile, NanoVM *vm)
{
	ASMAssembleProgram(programFile);
	FILE *machineCode = fopen("run.d", "r");
	fread(vm->program, sizeof (uint16_t), MAX_PROGRAM_LENGTH, machineCode);
	fclose(machineCode);
}


#ifdef ASM

int main (int argc, char const *argv[])
{
	if(argc != 2) die("Wrong number of arguments");
	FILE *program = fopen("test.asm", "r");
	
	if(program == NULL) die("Error reading assembly file");
	ASMAssembleProgram(program);
	
	fclose(program);
	return 0;
}

#endif