#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dumbvm.h"
#include "dumbdebug.h"
#include "dumbasm.h"
#include "asmcallbacks.h"

/**
** Creates a dictionary of all the labels in a programme
**
**
*/
uint16_t ASMLineForLabel(char *program, char *search)
{
	FILE *programFile = fopen(program, "r");
	if(programFile == NULL) die("error while reading program file");
	char command[16];
	char label[32];
	char currentLine[128];
	uint16_t line = 0;
	while(fgets(currentLine, 128, programFile))
	{
		sscanf(currentLine, "%s", command);
		if(!strcmp(command, "lbl"))
		{
			sscanf(currentLine, " lbl %s", label);
			if(!strcmp(label, search))
			{
				return line;
			}
		}
		++line;
	}
	printf("(%d) No label found with name %s\n", line, search);
	fclose(programFile);
	return -1;
}

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
		if(command < RET)
		{
			++command;
		}
		else
		{
			return -1;
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
void ASMAssembleProgram(char *program, char *output)
{
	tokenCallack callbacks[] = {
		asmHalt,
		asmMove,
		asmCopy,
		asmCopyIn,
		asmCopyOut,
		asmAdd,
		asmSub,
		asmMult,
		asmDiv,
		asmInc,
		asmDec,
		asmCall,
		asmLabel,
		asmJump,
		asmJumpNZ,
		asmReturn,
	};
	char currentLine[MAX_LINE_LENGTH];
	int length = 0;
	uint16_t line = 0;
	uint32_t assembledProgram[MAX_PROGRAM_LENGTH]= {0};
	FILE *programFile = fopen(program, "r");
	if(programFile == NULL) die("error loading programme file");
	
	while(fgets(currentLine, MAX_LINE_LENGTH, programFile))
	{
		ASMCommand instr = ASMinstructionForLine(currentLine);
		if(instr != -1)
		{
			assembledProgram[length++] = callbacks[instr](currentLine, line, program);
			printf("%02d: 0x%08x\n", line, callbacks[instr](currentLine, line, program));
		}
		++line;
	}
	fclose(programFile);
	FILE *assembledFile = fopen(output, "w");
	if(assembledFile == NULL) die ("Error writing assembled program");
	fwrite(assembledProgram, sizeof (uint32_t), length, assembledFile);
	fclose(assembledFile);
	
	printf("Finished assembling programme. Final size: %lu bytes\n",length*sizeof(uint32_t));
}

int main (int argc, char *argv[])
{
	if(argc != 2) die("Wrong number of arguments");
	char outFileName[512];
	sprintf(outFileName, "%s.d", argv[1]);
	ASMAssembleProgram(argv[1], outFileName);
	int16_t test = 0xfffc;
	printf("0xfffc = %d\n", test);
	return 0;
}