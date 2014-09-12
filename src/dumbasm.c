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
void ASMAssembleProgram(FILE *programFile, char *output)
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
	FILE *assembledFile = fopen(output, "w");
	if(assembledFile == NULL) die ("Error writing assembled program");
	fwrite(assembledProgram, sizeof (uint16_t), length, assembledFile);
	fclose(assembledFile);
}

int main (int argc, char const *argv[])
{
	if(argc != 2) die("Wrong number of arguments");
	FILE *program = fopen(argv[1], "r");
	if(program == NULL) die("Error reading assembly file");
	char outFileName[512];
	sprintf(outFileName, "%s.d", argv[1]);
	ASMAssembleProgram(program, outFileName);
	fclose(program);
	return 0;
}