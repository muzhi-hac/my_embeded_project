Firstly, im sorry for my poor Assembly basics.

So i will start with basic assembly program.
# Assembly program
**Program: 
Label: instruction@comment**

Label used to mark a positon in the code so it can be refered to by other parts of code

instruction:
commonds or operations like MOV, SUB, MSR.

commment:explanatory texts or remarks in the code 
use @or /* */ to comment   
for example
```
.text represents  code segment
data initialized data segment.
.bss Uninitialized data section.
.rodata read-only data section.

`.section .text
.globl _start
_start:
    BL main
    B .

.section .data
counter:
    .word 0

.section .rodata
hello_msg:
    .asciz "Hello, world!"
`
```

**the default entry label for the assembler is _start. However we can also use ENTRY in the link
scirpt to specify other the entry point**

Here is the common use assembly commond, the detailed commond referring to 
ARM ArchitectureReference Manual ARMv7-A and ARMv7-R edition.pdf
![image](https://github.com/user-attachments/assets/9826c7d6-c9c0-4288-832a-a0dcdfb57b22)
# Processor internal data transfer instructions
## MOV
MOV used to copy data from a register to another register or transfer a data to the register
for example
```
MOV R0,R1 @pass data from R1 to R0,that is R0=R1
MOV R0, 0X11  @pass data to register R0, that is R0=0X11
```
## MRS ( Move to Register from State register)
MRS used to pass data in special register (like CPSR or SPSR) to general register.
```
MRS R0, CPSR @pass data in MRS to R0
```
## MSR (Move to State Register from  registerr)
like above

**from chatgpt4 MRS and MSR can change data in SPSR as well, but it is limited for the SPSR 
is used to store and recover from exact exception status.**

# memory access instructions
ARM can't access mem directlt, like data in RAM. When registering, we need to use the device access command. Generally, we need to configure the value first.
Write to the Rx(x=0~12) register, and then use the memory access instruction to write the data in Rx to the I.MX6UL register. But **why????**.  
Here is the answer from chatgpt.
Firstly, Most CPU architectures, including ARM which is used in I.MU6UL, do not support direct immediate-to-hardware register operations. and the operations are faster for the registers are part of the processor's core and operate at the speed of CPU.
Secondly, Indirect addressing, the register are often memory-mapped, which means they are assigned specific addressed in the memory space.(So, if we want to caculate on the adress?or something like that?it won't work?????, this is my understanding)



