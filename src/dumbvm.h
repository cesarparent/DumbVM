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

#define NUM_REGISTERS 10
#define MAX_PROGRAM_LENGTH 1024
#define MAX_RAM_BYTES 16384
#define STACK_SIZE 1024

typedef enum
{
	INVALID = -1,
	HLT,
	MOV,
	CPY,
	CPI,
	CPO,
	ADD,
	SUB,
	MUL,
	DIV,
	INC,
	DEC,
	CLL,
	LBL,
	JMP,
	JNZ,
	RET,
} ASMCommand;

static char *commands[] = {
	"hlt",
	"mov",
	"cpy",
	"cpi",
	"cpo",
	"add",
	"sub",
	"mul",
	"div",
	"inc",
	"dec",
	"cll",
	"lbl",
	"jmp",
	"jnz",
	"ret",
};

typedef enum
{
	GAX,
	GBX,
	GCX,
	GDX,
	GIX,
	GOX,
	RIP,
	RSP,
	RMS,
	RMU,
} ASMRegisters;

static char *registers[] = {
	"gax", // four general-purpose registers
	"gbx",
	"gcx",
	"gdx",
	"gix", // input register
	"gox", // output register
	"rip", // instruction pointer
	"rsp", // stack pointer
	"rms", // stack ram sector
	"rmu", // user-mode ram sector
};

typedef uint32_t (*tokenCallack)(char *line, uint16_t lineNum, char *prog);

typedef struct NanoVM
{
	bool running;
	int8_t ram[MAX_RAM_BYTES];
	int8_t registers[NUM_REGISTERS]; // four standard regs, two I/O regs
	uint8_t opcode;
	uint32_t instruction;
	int16_t opNum;
	uint8_t opReg[3];
	void (*execOps[RET+1])(struct NanoVM *vm);
} NanoVM;

void VMPushStack(NanoVM *vm, int8_t value);
int8_t VMPopStack(NanoVM *vm);

#endif