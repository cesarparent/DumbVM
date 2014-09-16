/**
** Assembler callback functions
** Used to assemble single lines depending on their instruction
*/


uint32_t asmHalt(char *line, uint16_t lineNum, char *prog)
{
	return 0x00000000;
}

uint32_t asmMove(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg;
	int16_t value;
	uint32_t opCode = 0x01000000;
	sscanf(line, " mov r%hd, %hd", &reg, &value);
	opCode |= ((reg & 0x000000ff) << 16);
	opCode |= (value & 0x0000ffff);
	return opCode;
}

uint32_t asmCopy(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1, reg2;
	uint32_t opCode = 0x02000000;
	sscanf(line, " cpy r%hd, r%hd", &reg1, &reg2);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= ((reg2 & 0x000000ff) << 8);
	return opCode;
}


uint32_t asmCopyIn(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1;
	uint16_t memAdress;
	uint32_t opCode = 0x03000000;
	sscanf(line, " cpi r%hd, [%hd]", &reg1, &memAdress);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= (memAdress & 0x0000ffff);
	return opCode;
}

uint32_t asmCopyOut(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1;
	uint16_t memAdress;
	uint32_t opCode = 0x04000000;
	sscanf(line, " cpo r%hd, [%hd]", &reg1, &memAdress);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= (memAdress & 0x0000ffff);
	return opCode;
}

uint32_t asmAdd(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1, reg2;
	uint32_t opCode = 0x05000000;
	sscanf(line, " add r%hd, r%hd", &reg1, &reg2);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= ((reg2 & 0x000000ff) << 8);
	return opCode;
}

uint32_t asmSub(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1, reg2;
	uint32_t opCode = 0x06000000;
	sscanf(line, " sub r%hd, r%hd", &reg1, &reg2);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= ((reg2 & 0x000000ff) << 8);
	return opCode;
}

uint32_t asmMult(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1, reg2;
	uint32_t opCode = 0x07000000;
	sscanf(line, " mul r%hd, r%hd", &reg1, &reg2);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= ((reg2 & 0x000000ff) << 8);
	return opCode;
}

uint32_t asmDiv(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1, reg2;
	uint32_t opCode = 0x08000000;
	sscanf(line, " div r%hd, r%hd", &reg1, &reg2);
	opCode |= ((reg1 & 0x000000ff) << 16);
	opCode |= ((reg2 & 0x000000ff) << 8);
	return opCode;
}

uint32_t asmInc(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1;
	uint32_t opCode = 0x09000000;
	sscanf(line, " inc r%hd", &reg1);
	opCode |= ((reg1 & 0x000000ff) << 16);
	return opCode;
}

uint32_t asmDec(char *line, uint16_t lineNum, char *prog)
{
	uint16_t reg1;
	uint32_t opCode = 0x0a000000;
	sscanf(line, " dec r%hd", &reg1);
	opCode |= ((reg1 & 0x000000ff) << 16);
	return opCode;
}

uint32_t asmCall(char *line, uint16_t lineNum, char *prog)
{
	char jmpLabel[32];
	int16_t offset;
	uint32_t opCode = 0x0b000000;
	sscanf(line, " cll %s", jmpLabel);
	offset = ASMLineForLabel(prog, jmpLabel) - lineNum;
	opCode |= (offset & 0x0000ffff);
	return opCode;
}

uint32_t asmLabel(char *line, uint16_t lineNum, char *prog)
{
	uint32_t opCode = 0x0c000000;
	return opCode;
}

uint32_t asmJump(char *line, uint16_t lineNum, char *prog)
{
	char jmpLabel[32];
	int16_t offset;
	uint32_t opCode = 0x0d000000;
	sscanf(line, " jmp %s", jmpLabel);
	offset = ASMLineForLabel(prog, jmpLabel) - lineNum;
	opCode |= (offset & 0x0000ffff);
	return opCode;
}

uint32_t asmJumpNZ(char *line, uint16_t lineNum, char *prog)
{
	char jmpLabel[32];
	int16_t offset;
	uint16_t reg;
	uint32_t opCode = 0x0e000000;
	sscanf(line, " jnz r%hd, %s", &reg, jmpLabel);
	offset = ASMLineForLabel(prog, jmpLabel) - lineNum;
	opCode |= ((reg & 0x000000ff) << 16);
	opCode |= (offset & 0x0000ffff);
	return opCode;
}

uint32_t asmReturn(char *line, uint16_t lineNum, char *prog)
{
	uint32_t opCode = 0x0f000000;
	return opCode;
}