# NanoVM Specs

* 4 registers [r0 r1 r2 r3]
* I/O registers [ri, ro]
* Integer only

# Instruction Set

* load value in register								`ld reg,value`				1
* copy value between registers					`cpy reg,dest`				2
* Add values from two registers					`add reg,reg dest`		3
* Multiply values from two registers		`mul reg,reg dest`		4
* Divide values from two registers			`div reg,reg dest`		5
* Jump marker start											`jmk number`					6
* Jump condition												`jnz reg jmk`					7
* shut down virtual machine							`hlt`									0