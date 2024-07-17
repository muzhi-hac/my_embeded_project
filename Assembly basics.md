Firstly, im sorry for my poor Assembly basics.

So i will start with basic assembly program.  
Program: 
Label: instruction@comment
Label used to mark a positon in the code so it can be refered to by other parts of code

instruction:
commonds or operations like MOV, SUB, MSR.

commment:explanatory texts or remarks in the code 
use @or /* */ to comment 
  
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

for 
the default entry label for the assembler is _start. However we can also use ENTRY in the link
scirpt to specify other the entry point


