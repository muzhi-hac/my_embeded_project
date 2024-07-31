.global _start
_start :
    ldr pc, =Reset_Handler
    ldr pc, =Undef_Handler
    ldr pc, =SVC_Handler
    ldr pc, =PreAbort_Handler
    ldr pc, =DataAbort_Handler
    ldr pc, =IRQ_Handler
    ldr pc, =FIQ_Handler

Reset_Handler:
    cpsid i
    /*c0 control the SCTRL*/
    mrc p15,0,r0,c1,c0,0
    bic     r0,  r0, #(0x1 << 12)     /* 清除C1寄存器的bit12位(I位)，关闭I Cache            	*/
    bic     r0,  r0, #(0x1 <<  2)     /* 清除C1寄存器的bit2(C位)，关闭D Cache    				*/
    bic     r0,  r0, #0x2             /* 清除C1寄存器的bit1(A位)，关闭对齐						*/
    bic     r0,  r0, #(0x1 << 11)     /* 清除C1寄存器的bit11(Z位)，关闭分支预测					*/
    bic     r0,  r0, #0x1             /* 清除C1寄存器的bit0(M位)，关闭MMU				       	*/
    mcr p15,0,r0,c1,c0,0
    
    ldr r0 ,=0x87000000
    dsb
    isb
    mrc p15,0,r0,c12,c0,0 /* config the VBAR*/ 
    dsb
    isb

    /*SYS_MODE*/
    mrs r0, cpsr
    bic r0, r0,#0x1f
    orr r0, r0, #0x1f
    msr cpsr,r0
    ldr sp, =0x80600000

    /*IRQ_MODE*/
     mrs r0, cpsr
    bic r0, r0,#0x1f
    orr r0, r0, #0x12
    msr cpsr,r0
    ldr sp, =0x80400000

    /*SVS_MODE*/
    mrs r0, cpsr
    bic r0, r0,#0x1f
    orr r0, r0, #0x13
    msr cpsr,r0
    ldr sp, =0x80200000
    
    cpsie i
    b main
   


Undefined_Handler:
	ldr r0, =Undefined_Handler
	bx r0

SVC_Handler:
	ldr r0, =SVC_Handler
	bx r0

PrefAbort_Handler:
	ldr r0, =PrefAbort_Handler	
	bx r0

DataAbort_Handler:
	ldr r0, =DataAbort_Handler
	bx r0

IRQ_Handler:
    cpsid i
    push {r0-r3,r12}
    push {lr}

    mrs r0,spsr
    push {r0}

   /* MCR{cond} p15, <opc1>, <Rt>, <CRn>, <CRm>, <opc2>*/
   mcr p15,4,r1,c15,c0 
   /*get GICC_CBAR register value*/

   add r1, r1,0x2000
   ldr r0,[r1,0xc]
   /*get GICC_IAR which controls ID*/

    psuh {r0,r1}

    cps 0x13
    psuh {lr}
    ldr r2,=system_irq_handler
    blx r2

    pop {lr}
    cps 0x12
    pop {r0,r1}
	str r0, [r1, #0X10]			/* 中断执行完成，写EOIR */

    pop {r0}						
	msr spsr_cxsf, r0			/* 恢复spsr */

    pop {r0-r3,r12}
    pop {lr}
    sub pc,lr,#4
    


   


    


    ldr r0, =IRQ_Handler
    bx r0

FIQ_Handler:
    ldr r0, =FIQ_Handler
    bx r0


    mrs r0, cpsr
    bic r0, r0,#0x1f
    orr r0, r0, #0x13
    msr cpsr,r0

    ldr sp, =0x80200000
    
    b main 