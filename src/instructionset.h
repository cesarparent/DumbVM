/**
** Callbacks called during VM execution
**
**
*/

void execHalt(struct NanoVM *vm)
{
	vm->running = false;
}

void execMove(struct NanoVM *vm)
{
	vm->registers[vm->opReg[0]] = vm->opNum;
}

void execCopy(struct NanoVM *vm)
{
	vm->registers[vm->opReg[1]] = vm->registers[vm->opReg[0]];
}

void execCopyIn(struct NanoVM *vm)
{
	vm->registers[vm->opReg[0]] = vm->ram[vm->opNum];
}

void execCopyOut(struct NanoVM *vm)
{
	vm->ram[vm->opNum] = vm->ram[vm->opReg[0]];
}

void execAdd(struct NanoVM *vm)
{
	vm->registers[vm->opReg[0]] = vm->registers[vm->opReg[0]] + vm->registers[vm->opReg[1]];
}

void execSub(struct NanoVM *vm)
{
	vm->registers[vm->opReg[0]] = vm->registers[vm->opReg[0]] - vm->registers[vm->opReg[1]];
}

void execMult(struct NanoVM *vm)
{
	vm->registers[vm->opReg[0]] = vm->registers[vm->opReg[0]] * vm->registers[vm->opReg[1]];
}

void execDiv(struct NanoVM *vm)
{
	vm->registers[vm->opReg[0]] = vm->registers[vm->opReg[0]] / vm->registers[vm->opReg[1]];
}

void execInc(struct NanoVM *vm)
{
	++vm->registers[vm->opReg[0]];
}

void execDec(struct NanoVM *vm)
{
	--vm->registers[vm->opReg[0]];
}

void execCall(struct NanoVM *vm)
{
	VMPushStack(vm, (int8_t)vm->registers[RIP]);
	vm->registers[RIP] += vm->opNum;
}

void execLabel(struct NanoVM *vm)
{
	
}

void execJump(struct NanoVM *vm)
{
	vm->registers[RIP] += vm->opNum;
}

void execJumpNZ(struct NanoVM *vm)
{
	if(vm->registers[vm->opReg[0]])
	{
		vm->registers[RIP] += vm->opNum;
	}
}

void execReturn(struct NanoVM *vm)
{
	vm->registers[RIP] = (int16_t)VMPopStack(vm);
}