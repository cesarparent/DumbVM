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

#define NUM_REGISTERS 10
#define RAM_WORDS_NUM 8192
#define MAX_PROGRAM_LENGTH 1024
#define STACK_SIZE 256;

typedef enum OpCodes
{
	INVALID = -1,
	HLT = 0x0,
	MOV = 0x1,
	CPY = 0x2,
	LOD = 0x3,
	STR = 0x4,
	ADD = 0x5,
	SUB = 0x6,
	MUL = 0x7,
	DIV = 0x8,
	INC = 0x9,
	DEC = 0xa,
	PSH = 0xb,
	POP = 0xc,
	JMP = 0xd,
	JNZ = 0xe,
} INSTRUCTION_CODE;

typedef enum
{
	GPI = 4,
	GPO,
	IP,
	SP,
	SS,
	SU,
} VMSpecialRegisters;

typedef struct
{
	bool running;
	int16_t memory[RAM_WORDS_NUM];
	int16_t registers[10]; // four gp registers, input, output, ip, sp, ss, us
	uint32_t instruction;
	INSTRUCTION_CODE opcode;
	uint8_t regs[3];
	int16_t num;
} NanoVM;

#endif