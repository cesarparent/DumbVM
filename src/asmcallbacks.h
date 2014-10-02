/**
** Assembler callback functions
** Used to assemble single lines depending on their instruction
*/


uint16_t asmHalt(char *line)
{
	return 0x0000;
}

uint16_t asmMove(char *line)
{
	int8_t reg, value;
	uint16_t opCode = 0x1000;
	sscanf(line, "mov r%hhd, %hhd", &reg, &value);
	opCode = (opCode |  ((reg & 0x000f) << 8));
	opCode = (opCode | (value & 0x00ff));
	return opCode;
}

uint16_t asmCopy(char *line)
{
	int8_t reg1, dest;
	uint16_t opCode = 0x2000;
	sscanf(line, "cpy r%hhd, r%hhd", &reg1, &dest);
	opCode = (opCode | ((reg1 & 0x000f) << 8));
	opCode = (opCode | ((dest & 0x000f) << 4));
	return opCode;
}

uint16_t asmAdd(char *line)
{
	int8_t reg1, reg2, dest;
	uint16_t opCode = 0x3000;
	sscanf(line, "add r%hhd, r%hhd, r%hhd", &reg1, &reg2, &dest);
	opCode = (opCode | ((reg1 & 0x000f) << 8));
	opCode = (opCode | ((reg2 & 0x000f) << 4));
	opCode = (opCode | (dest & 0x000f));
	return opCode;
}

uint16_t asmSub(char *line)
{
	int8_t reg1, reg2, dest;
	uint16_t opCode = 0x4000;
	sscanf(line, "sub r%hhd, r%hhd, r%hhd", &reg1, &reg2, &dest);
	opCode = (opCode | ((reg1 & 0x000f) << 8));
	opCode = (opCode | ((reg2 & 0x000f) << 4));
	opCode = (opCode | (dest & 0x000f));
	return opCode;
}

uint16_t asmMultiply(char *line)
{
	int8_t reg1, reg2, dest;
	uint16_t opCode = 0x5000;
	sscanf(line, "mul r%hhd, r%hhd, r%hhd", &reg1, &reg2, &dest);
	opCode = (opCode | ((reg1 & 0x000f) << 8));
	opCode = (opCode | ((reg2 & 0x000f) << 4));
	opCode = (opCode | (dest & 0x000f));
	return opCode;
}

uint16_t asmDivide(char *line)
{
	int8_t reg1, reg2, dest;
	uint16_t opCode = 0x6000;
	sscanf(line, "div r%hhd, r%hhd, r%hhd", &reg1, &reg2, &dest);
	opCode = (opCode | ((reg1 & 0x000f) << 8));
	opCode = (opCode | ((reg2 & 0x000f) << 4));
	opCode = (opCode | (dest & 0x000f));
	return opCode;
}

uint16_t asmJump(char *line)
{
	int8_t offset;
	uint16_t opCode = 0x7000;
	sscanf(line, "jmp %hhd", &offset);
	opCode = (opCode | (offset & 0x00ff));
	return opCode;
}

uint16_t asmJumpNZ(char *line)
{
	int8_t reg, offset;
	uint16_t opCode = 0x8000;
	sscanf(line, "jnz r%hhd, %hhd", &reg, &offset);
	opCode = (opCode | ((reg & 0x000f) << 8));
	opCode = (opCode | (offset & 0x00ff));
	return opCode;
}