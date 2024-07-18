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

    Firstly, Most CPU architectures, including ARM which is used in I.MU6UL, **do not support direct immediate-to-hardware register operations**. and the operations are **faster** for the registers are part of the processor's core and operate at the speed of CPU.  

    Secondly, **Indirect addressing**, the register are often memory-mapped, which means they are assigned specific addressed in the memory space.  

 (So, if we want to caculate on the adress?or something like that?it won't work?????, this is my understanding). and **reducing the errors caused by direct manipulation of control registers**.  

Thirdly, something unimportant .![image](https://github.com/user-attachments/assets/dfb10920-e390-43d6-b9c8-847ce0cee0f7)  

OKOK, let's fxxking go.  

## LDR
used to load data to register Rx.
it use = to load data.
```
LDR R0, =0x0000002 @
LDR R1, [R0] @ R1=R0
```  

## STR
```
LDR R0, =0x209C000
LDR R1, =0x209C001
STR R1, [R0] @
```
~~R1=R0~~, hollyshit, it makes R0=R1.
and LDRB and STRB can act using Byte
```
LDRB R0, [R1]         ; Load a byte from the memory location pointed to by R1 into R0
LDRB R0, [R1, #4]     ; Load a byte from memory at an address offset by 4 bytes from the address in R1
STRB R0, [R1]         ; Store the least significant byte of R0 into the memory location pointed to by R1
STRB R0, [R1, #4]     ; Store the least significant byte of R0 into memory at an address offset by 4 bytes from the address in R1

```
# Push and pop instructions
![image](https://github.com/user-attachments/assets/6cd8b3a8-39d9-45a7-81cd-145aa5569167)

another type is STMFD SP! and LDMFD SP!.  

# jump instruction
![image](https://github.com/user-attachments/assets/75b68b11-724d-47a0-b77c-5fe0cb7d8a2e)

## cps instruction
directly manipulation of the CPSR, specially for enabling or disabling interrupts.

