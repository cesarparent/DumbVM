/**
** NanoVM — Dead simple C-based virtual machine
**
** nanovm.c - main implementation of the VM logic
**
** Created 2014-09-09 by Cesar Parent <cesar@cesarparent.com>
** Copyright (c) 2014 Cesar Parent
**
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "dumbvm.h"
#include "dumbdebug.h"
#include "dumbasm.h"

/**
** Boots the virtual machine, attempts to read a program,
** assemble it and load it in the program memory
**
** @param FILE* program the file containing the assembly program to run
** @param NanoVM* vm the VM instance in which to load the program
** @return bool true if the program was loaded and assembled, false otherwise
*/
bool loadProgram(char *program, NanoVM *vm)
{
	FILE *programFile = fopen(program, "r");
	if (programFile == NULL) die(program);
	ASMLoadProgram(programFile, vm);
	fclose(programFile);
	return true;
}

/**
** Fetches and return the next operation code to be executed
**
** @param NanoVM* vm a booted and running virtual machine
*/
void VMFetch(NanoVM *vm)
{
	vm->instruction = vm->program[vm->instructionPointer++];
}

/**
** Decodes the current opcode and selects the right operands
**
**
*/
void VMDecodeOperation(NanoVM *vm)
{
	vm->opcode = (vm->instruction & 0xF000) >> 12;
	vm->regs[0] = (vm->instruction & 0xF00) >> 8;
	vm->regs[1] = (vm->instruction & 0xF0) >> 4;
	vm->regs[2] = (vm->instruction & 0xF);
	vm->num = (int8_t)(vm->instruction & 0xFF);
}

/**
**
**
**
*/
void VMEval(NanoVM *vm)
{
	switch(vm->opcode)
	{
		case 0: // halt execution
			vm->running = 0;
			break;
		
		case 1: //ld
			vm->registers[vm->regs[0]] = vm->num;
			break;
		
		case 2: // cpy
			vm->registers[vm->regs[1]] = vm->registers[vm->regs[0]];
			break;
		
		case 3:
			vm->registers[vm->regs[2]] = vm->registers[vm->regs[0]] + vm->registers[vm->regs[1]];
			break;
		
		case 4:
			vm->registers[vm->regs[2]] = vm->registers[vm->regs[0]] * vm->registers[vm->regs[1]];
			break;
		
		case 5:
			vm->registers[vm->regs[2]] = vm->registers[vm->regs[0]] / vm->registers[vm->regs[1]];
			break;
		
		default:
			break;
	}
}

/**
** Boots the virtual machine, attempts to read a program,
** assemble it and load it in the program memory
**
** @param FILE* program the file containing the assembly program to run
** @return NanoVM* a ready-to-use VM instance
*/
NanoVM *newVMInstance (char *programFile)
{
	NanoVM *newVM = malloc(sizeof (NanoVM));
	if (newVM == NULL) die("Memory allocation error while creating VM");
	newVM->instructionPointer = 0;
	if (!loadProgram(programFile, newVM)) die ("error while loading program");
	
	newVM->registers[0] = 0;
	newVM->registers[1] = 0;
	newVM->registers[2] = 0;
	newVM->registers[3] = 0;
	
	newVM->opcode = 0;
	newVM->running = true;
	return newVM;
}

/**
** Destroys the memory occupied by the VM, once it is shut down
**
** @param NanoVM *vm the vm instance to destroy
** @return void
*/
void VMDestroy(NanoVM *vm)
{
	free(vm);
	vm = NULL;
}

/**
** Launches the execution of the programme
**
** @param NanoVM *vm the VM to run
** @return void
*/
void VMRun(NanoVM *vm)
{
	while(vm->running)
	{
		vm->registers[5] = 0;
		VMFetch(vm);
		VMDecodeOperation(vm);
		VMEval(vm);
		//VMDebug(vm);
		printf("%c", vm->registers[5]);
	}
}


int main (int argc, char **argv)
{
	if(argc != 2) die("wrong number of arguments");
	NanoVM *vmInstance = newVMInstance(argv[1]);
	VMRun(vmInstance);
	printf("Shutting Down...\n");
	getchar();
	VMDestroy(vmInstance);
	return 0;
}