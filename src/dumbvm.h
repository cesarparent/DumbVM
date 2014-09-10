/**
** NanoVM — Dead simple C-based virtual machine
**
** nanovm.h - headers and datatypes for nanovm
**
** Created 2014-09-09 by Cesar Parent <cesar@cesarparent.com>
** Copyright (c) 2014 Cesar Parent
**
*/

#ifndef _nanovm_h
#define _nanovm_h

#include <stdint.h>

#define NUM_REGISTERS 6
#define MAX_PROGRAM_LENGTH 1024

typedef struct
{
	bool running;
	int16_t registers[NUM_REGISTERS]; // four standard regs, two I/O regs
	uint16_t program[MAX_PROGRAM_LENGTH];
	uint16_t instruction;
	uint16_t opcode;
	uint8_t regs[3];
	int8_t num;
	uint16_t instructionPointer;
} NanoVM;

#endif