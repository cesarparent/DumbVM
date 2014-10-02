#ifndef _nanoasm_h
#define _nanoasm_h

#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_LINE_LENGTH 64

typedef uint16_t (*tokenCallback)(char *line);


static char *commands[] = {
	"hlt",
	"mov",
	"cpy",
	"lod",
	"str",
	"add",
	"sub",
	"mul",
	"div",
	"inc",
	"dec",
	"psh",
	"pop",
	"jmp",
	"jnz",
};

#endif