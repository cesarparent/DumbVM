# DumbVM

DumbVM is a simplistic virtual machine written in C. It has its own assembly language, a simple assembler, and can read and execute hex machine code. I wrote this to try and apply the concepts taught in first year of BSc Computing by Dr. Ian Ferguson at Abertay Dundee University. It is certainly not an example of good C code, neither is it useful or complete. I intend to use it as I learn more about architecture and OS design, before switching to Raspberry PI bare metal programming.

# Building

The Makefile contains build instructions for creating a Mac executable, but should work for Windows and *nix without major changes. `make debug` will switch the debug mode on in the built executable, which will print the contents of all registers for each vm cpu cycle. `make` will build the vm, and `make assembler` will build the assembler as a standalone executable.

# Running

The machine is launched by calling `./dumbvm <assembly programme>`. It will assemble the given file and output a `run.d` file with the final machine code, and run it. If the assembler is built, it can be used the same way to output machine code without running the machine.

# Design

DumbVM possesses four standard 8-bit (two's complement, from -128 to 127) registers (`r0` through `r3`), an input register (`r4`, unused at the moment, will hold the value of the last pressed key) and an output register (`r5`, which content is output as ascii and reset each cycle).

DumbVM does not yet have any RAM.

# Instruction set

## assembly language and machine code

For the moment, the only language that can be used on DumbVM is its own assembly, which is mapped to the custom machine code. Each machine code instruction is made of a four-byte word.

The first byte represents the operation, while the next three byte can represent, depending on the operation, registers, constants and (not yet implemented) RAM addresses.

In assembly, a register number is always preceded by `r`, while a constant is always preceded by `#`.

|Asm. Instr.	| Mach. Instr. | Syntax                                          | Example        |
|:--------------|:-------------|:------------------------------------------------|:---------------|
|`mov`          |1             |load a value in a register                       |`mov r0,#200`   |
|`cpy`          |2             |copy value from register to register             |`cpy r0,r2`     |
|`add`          |3             |add values from to registers in a third one      |`add r0,r2,r3`  |
|`sub`          |4             |subtract values from to registers in a third one |`sub r0,r2,r3`  |
|`mul`          |5             |multiply values from to registers in a third one |`mul r0,r2,r3`  |
|`div`          |6             |divide values from to registers in a third one   |`div r0,r2,r3`  |
|`jpm`          |7             |jump by a certain offset in the execution        |`jmp #-5`       |
|`jnz`          |7             |jump, only if the given register holds zero      |`jnz r1,#-5`    |

## example programme

The following is a simple programme that prints the alphabet to the output in lower case. It can be found in the `example.asm` file.

`r0` is used as a counter, and is set to 26. `a` ascii value (97) is loaded in `r1`, and `1`, the increment, in `r2`. Then, the letter is copied in `r5`, which puts it on the screen, `r2` is subtracted to the counter and added to the letter, and we jump back four instructions until the counter reaches 0.

**assembly**
~~~~text
mov r0,#26
mov r1,#97
mov r2,#1
cpy r1,r5
sub r0,r2,r0
add r1,r2,r1
jnz r0,#-4
hlt
~~~~

**machine code (beautified)**
~~~text
0x101a
0x1161
0x1201
0x2150
0x4020
0x3121
0x70fc
0x0000
~~~