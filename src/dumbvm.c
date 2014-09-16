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
#include "instructionset.h"

/**
** Boots the virtual machine, attempts to read a program,
** assemble it and load it in the program memory
**
** @param FILE* program the file containing the assembly program to run
** @param NanoVM* vm the VM instance in which to load the program
** @return bool true if the program was loaded and assembled, false otherwise
*/


void VMPushStack(NanoVM *vm, int8_t value)
{
	if(vm->registers[RSP] < (vm->registers[RMS]))
	{
		die("Stack overflow");
	}
	vm->ram[vm->registers[RSP]--] = value;
}

int8_t VMPopStack(NanoVM *vm)
{
	if(vm->registers[RSP] < vm->registers[RMS] + STACK_SIZE)
	{
		return vm->ram[++vm->registers[RSP]];
	}
	return vm->ram[vm->registers[RMS] + STACK_SIZE];
}

/**
** Loads the machine code programme into the memory of the VM
**
**
*/
void loadProgram(char *program, NanoVM *vm)
{
	uint32_t tempProgram[MAX_PROGRAM_LENGTH] = {0};
	int length = 0;
	FILE *machineCode = fopen(program, "r");
	if (machineCode == NULL) die("Unable to open programme file");
	length = fread(tempProgram, sizeof (uint32_t), MAX_PROGRAM_LENGTH, machineCode);
	fclose(machineCode);
	for(int i = 0; i < length; ++i)
	{
		vm->ram[i*4] = (tempProgram[i] & 0xff000000) >> 24;
		vm->ram[(i*4)+1] = (tempProgram[i] & 0xff0000) >> 16;
		vm->ram[(i*4)+2] = (tempProgram[i] & 0xff00) >> 8;
		vm->ram[(i*4)+3] = (tempProgram[i] & 0xff);
	}
	vm->registers[RMS] = (length*4) + 128;
	vm->registers[RSP] = vm->registers[RMS] + STACK_SIZE;
}

/**
** Fetches and return the next operation code to be executed
**
** @param NanoVM* vm a booted and running virtual machine
*/
void VMFetch(NanoVM *vm)
{
	vm->instruction = 0x00000000;
	uint16_t ramAddress = 0;
	for(int i = 0; i < 4; ++i)
	{
		ramAddress = (vm->registers[RIP]*4) + i;
		vm->instruction |= (vm->ram[ramAddress] & 0x0ff) << ((3-i) * 8);
	}
	++vm->registers[RIP];
#ifdef DEBUG
	getchar();
#endif
}

/**
** Decodes the current opcode and selects the right operands
**
**
*/
void VMDecodeOperation(NanoVM *vm)
{
	vm->opcode = (vm->instruction & 0xff000000) >> 24;
	vm->opReg[0] = (vm->instruction & 0xff0000) >> 16;
	vm->opReg[1] = (vm->instruction & 0xff00) >> 8;
	vm->opReg[2] = (vm->instruction & 0xff);
	vm->opNum = (int8_t)(vm->instruction & 0xffff);
}

/**
**
**
**
*/
void VMEval(NanoVM *vm)
{
	vm->execOps[vm->opcode](vm);
}

void VMLoadInstructionSet(NanoVM *vm)
{
	vm->execOps[HLT] = execHalt;
	vm->execOps[MOV] = execMove;
	vm->execOps[CPY] = execCopy;
	vm->execOps[CPI] = execCopyIn;
	vm->execOps[CPO] = execCopyOut;
	vm->execOps[ADD] = execAdd;
	vm->execOps[SUB] = execSub;
	vm->execOps[MUL] = execMult;
	vm->execOps[DIV] = execDiv;
	vm->execOps[INC] = execInc;
	vm->execOps[DEC] = execDec;
	vm->execOps[CLL] = execCall;
	vm->execOps[LBL] = execLabel;
	vm->execOps[JMP] = execJump;
	vm->execOps[JNZ] = execJumpNZ;
	vm->execOps[RET] = execReturn;
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
	
	newVM->registers[GAX] = 0;
	newVM->registers[GBX] = 0;
	newVM->registers[GCX] = 0;
	newVM->registers[GDX] = 0;
	newVM->registers[GIX] = 0;
	newVM->registers[GOX] = 0;
	newVM->registers[RIP] = 0;
	newVM->registers[RSP] = 0;
	newVM->registers[RMS] = 0;
	newVM->registers[RMU] = 0;
	
	loadProgram(programFile, newVM);
	
	newVM->opcode = 0;
	newVM->running = true;
	VMLoadInstructionSet(newVM);
	
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