#ifndef _nanoasm_h
#define _nanoasm_h

#include <string.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_LINE_LENGTH 64

uint16_t ASMLineForLabel(char *program, char *search);

#endif