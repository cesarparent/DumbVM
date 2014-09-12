#ifndef _nanoasm_h
#define _nanoasm_h

#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_LINE_LENGTH 64

typedef uint16_t (*tokenCallack)(char *line);

typedef enum
{
	HLT,
	MOV,
	CPY,
	ADD,
	SUB,
	MUL,
	DIV,
	JMP,
	JNZ,
} ASMCommand;

static char *commands[] = {
	"hlt",
	"mov",
	"cpy",
	"add",
	"sub",
	"mul",
	"div",
	"jmp",
	"jnz",
};



#endif