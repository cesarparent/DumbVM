#ifndef _nanoasm_h
#define _nanoasm_h

void ASMLoadProgram(FILE *programFile, NanoVM *vm);

static char OPS_TOKEN[] = {
	"hld",
	"ld",
	"cpy",
	"add",
	""
};

#endif