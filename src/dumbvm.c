/**
** NanoVM — Dead simple C-based virtual machine
**
** nanovm.c - main implementation of the VM logic
**
** Created 2014-09-09 by Amy Parent <amy@amyparent.com>
** Copyright (c) 2014 Amy Parent
**
*/
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

#include "dumbvm.h"
#include "dumbdebug.h"
#include "instructionset.h"

/**
** Boots the virtual machine, attempts to read a program,
** assemble it and load it in the program memory
**
** @param FILE* program the file containing the assembly program to run
** @param NanoVM* vm the VM instance in which to load the program
** @return bool true if the program was loaded and assembled, false otherwise
*/

/**
** Loads the machine code programme into the memory of the VM
**
**
*/
void loadProgram(char *program, NanoVM *vm)
{
	FILE *machineCode = fopen(program, "r");
	if (machineCode == NULL) die("Unable to open programme file");
	int length = fread(vm->memory, sizeof (int16_t), MAX_PROGRAM_LENGTH, machineCode);
	fclose(machineCode);
	vm->registers[SS] = length + 32;
	vm->registers[SP] = vm->registers[SS] + STACK_SIZE;
	vm->registers[SU] = vm->registers[SP] + 32;
}

/**
** Fetches and return the next operation code to be executed
**
** @param NanoVM* vm a booted and running virtual machine
*/
void VMFetch(NanoVM *vm)
{
	vm->instruction = vm->memory[vm->registers[IP]++];
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
		
		case 3: // add
			vm->registers[vm->regs[0]] = vm->registers[vm->regs[0]] + vm->registers[vm->regs[1]];
			break;
		
		case 4: // sub
			vm->registers[vm->regs[0]] = vm->registers[vm->regs[0]] - vm->registers[vm->regs[1]];
			break;
		
		case 5: // mul
			vm->registers[vm->regs[0]] = vm->registers[vm->regs[0]] * vm->registers[vm->regs[1]];
			break;
		
		case 6: // div
			vm->registers[vm->regs[0]] = vm->registers[vm->regs[0]] / vm->registers[vm->regs[1]];
			break;
		
		case 7: // jmp
			vm->registers[IP] += vm->num;
			break;
		
		case 8: // jnz
			if(vm->registers[vm->regs[0]])
			{
				vm->registers[IP] += vm->num;
			}
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
	
	for(int i = 0; i < NUM_REGISTERS; ++i)
	{
		newVM->registers[i] = 0x0;
	}
	loadProgram(programFile, newVM);
	
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
#ifdef DEBUG
		VMDebug(vm);
#endif
		printf("%c", vm->registers[5]);
	}
}


int main (int argc, char **argv)
{
	if(argc != 2) die("wrong number of arguments");
	NanoVM *vmInstance = newVMInstance(argv[1]);
	VMRun(vmInstance);
	printf("\n");
	VMDestroy(vmInstance);
	return 0;
}