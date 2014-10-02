# DumbVM

DumbVM is a simplistic virtual machine written in C. It has its own assembly language, a simple assembler, and can read and execute hex machine code. I wrote this to try and apply the concepts taught in first year of BSc Computing by Dr. Ian Ferguson at Abertay Dundee University. It is certainly not an example of good C code, neither is it useful or complete. I intend to use it as I learn more about architecture and OS design, before switching to Raspberry PI bare metal programming.

# Building

The Makefile contains build instructions for creating a Mac executable, but should work for Windows and *nix without major changes. Running `make debug` will trigger verbose output on the vm executable, which will display the values of all registers for each cpu cycle.

Running `make all` will produce two executables, `dumbvm` (the actual virtual machine) and `dumbasm` (the assembler).

# Running

The VM is launched by calling `./dumbvm <assembled programme file>`. It will attempt to load the programme in memory, and run it.

The assembler is called with `./dumbasm <assembly programme>` and will output the assembled programme.

# Design

DumbVM possesses four standard 8-bit (two's complement, from -128 to 127) registers (`r0` through `r3`), an input register (`r4`, unused at the moment, will hold the value of the last pressed key) and an output register (`r5`, which content is output as ascii and reset each cycle).

DumbVM does not yet have any RAM.

# Instruction set

## assembly language and machine code

For the moment, the only language that can be used on DumbVM is its own assembly, which is mapped to the custom machine code. Each machine code instruction is made of a four-byte word.

The first byte represents the operation, while the next three byte can represent, depending on the operation, registers, constants and (not yet implemented) RAM addresses.

In assembly, a register number is always preceded by `r`, while a constant is written as-is.

|Asm. Instr.	| Mach. Instr. | Syntax                                          | Example        |
|:--------------|:-------------|:------------------------------------------------|:---------------|
|`mov`          |1             |load a value in a register                       |`mov r0,200`    |
|`cpy`          |2             |copy value from register to register             |`cpy r0,r2`     |
|`add`          |3             |add the second register to the first one         |`add r0,r2`     |
|`sub`          |4             |subtract the second register from the first one  |`sub r0,r2`     |
|`mul`          |5             |multiply the first register by the second one    |`mul r0,r2`     |
|`div`          |6             |divide the first register by the second one      |`div r0,r2`     |
|`jmp`          |7             |jump by a certain offset in the execution        |`jmp -5`        |
|`jnz`          |7             |jump, only if the given register holds zero      |`jnz r1,-5`     |

## example programme

The following is a simple programme that prints the alphabet to the output in lower case. It can be found in the `example.asm` file.

`r0` is used as a counter, and is set to 26. `a` ascii value (97) is loaded in `r1`, and `1`, the increment, in `r2`. Then, the letter is copied in `r5`, which puts it on the screen, `r2` is subtracted to the counter and added to the letter, and we jump back four instructions until the counter reaches 0.

**assembly**
~~~~text
mov r0,26
mov r1,97
mov r2,1
cpy r1,r5
sub r0,r2
add r1,r2
jnz r0,-4
hlt
~~~~

**machine code (beautified)**
~~~text
0x101a
0x1161
0x1201
0x2150
0x4020
0x3120
0x70fc
0x0000
~~~