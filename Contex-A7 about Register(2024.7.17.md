2024.7.17

First day in embeded area and wiring MD file with english for first time .

what i plan to do is to sort out previous content.



# 1.Contex-A7 MPCore stucture

## cotex-A7 has 7 running modes, User, FIQ, IRQ ,Supervisor(svr), Abort, Undef and System.

and here is the brief introduction to these models.

**1.User Mode(usr)**

normal operational mode for user application. It has least previleages and Not allowed to access critical system resources.

**2.FIQ Mode(fiq)**

Fast Interrupt Mode. Handling Fast Interrupt Requests, typically used in time-critical data processing tasks.

**3.IRQ**

Standard Interrupt Mode.

**4.Supervisor Mode(svc)**

primarily used by the operating system for privileged operations and executing system calls.

**5.Abort** 

Abort Mode .Two types :Data Abort and Prefetch Abort(数据中止和预取中止),

---------------------------------------------------------------

what is  and Prefetch Abort

Data Abort:

When accessing data memory, maybe existing non-existent memory address???

or accessing somewhere without permissions, or something like that

Prefecth Abort

when fetching instruction from memory, just like above.

-----------

**6.Undeifined Mode(und)**

When encountered with an undefined instrutction 

**7.System Mode (sys)**

Same register as User.It is used for operating system tasks that do not require a separate stack for each mode(它用于不需要为每种模式提供单独堆栈的操作系统任务)



And the Cotex-A7 has registers like

1.r0-r15 for software using 

2.CPSR (current programming status register)



![image-20240717200914563](https://github.com/user-attachments/assets/11b5fbc1-f96a-41d2-ad48-47dbf59dc1be)




some Mode has its own register, such as R8_fiq

and Registers from **r0-r7 are not backed up**, for all modes share them.

every mode has its own **R13** execpt User and Sys sharing one, R13(sp) is sp point used as 

to init the sp point

 **R14** used as storing the return address of the current subroutine.

if we use BL or BLX to call subroutine, R14(LR) is set as the return address of subroutine.

In subroutine, we can assign the value of R14 to PC to return.

For example, we can use the following code in a subroutine:
MOV PC, LR     @Assign the value in register LR to PC to implement jump
Or you can push LR onto the stack at the entrance of the sub-function:
PUSH {LR}  @Push the LR register onto the stack
 Just pop the stack at the end of the sub-function:
POP {PC}



**R15 ** is called PC ,which stores the current address add 8 B .for the 

ARM
The pipeline mechanism :ARM processor 3-stage pipeline: fetch->decode->execute

PC stores the current address, for the pipeline mechanism and 32 bit structure, 

PC = current Base +8B

## Program status register





**every mode shares one CPSR**, so CPSR can be accessed in any mode.

CPSR is the current program status registration, which contains **condition flag bits**, **prohibition bits**, and **current processor mode flags**.
Wait for some status bits and some control bits. **All CPU modes occupying one CPSR will inevitably cause conflicts**, therefore,Except for the two modes User and Sys, the other 7 modes are each equipped with a dedicated physical status register called
Do SPSR (**Backup Program Status Registration**),**after the exception exits, we can** 

**recover the CPSR with SPSR.**

Detail can refer to the ARM Cortex-A7(arm v7)P46

![image-20240717204023056](https://github.com/user-attachments/assets/177f66d2-b654-43d1-a328-82a9667f6679)


N(bit31)：当两个补码表示的 有符号整数运算的时候， N=1 表示运算对的结果为负数， N=0

表示结果为正数。



Z(bit30)： Z=1 表示运算结果为零， Z=0 表示运算结果不为零，对于 CMP 指令， Z=1 

表示进行比较的两个数大小相等。



C(bit29)：在加法指令中，当结果产生了进位，则 C=1，表示无符号数运算发生上溢，其它情况下 C=0。在减法指令中，当运算中发生借位，则 C=0，表示无符号数运算发生下溢，其它情况下 C=1。对于包含移位操作的非加/减法运算指令， C 中包含最后一次溢出的位的数值，对于其它非加/减运算指令， C 

位的值通常不受影响。



V(bit28)： 对于加/减法运算指令，当操作数和运算结果表示为二进制的补码表示的带符号数时， V=1 表示符号位溢出，通常其他位不影响 V 

位。



Q(bit27)： 仅 ARM v5TE_J 架构支持，表示饱和状态， Q=1 表示累积饱和， Q=0 

表示累积不饱和。



IT[1:0](bit26:25)： 和 IT[7:2](bit15:bit10)一起组成 IT[7:0]，作为 IF-THEN 

指令执行状态。



J(bit24)： 仅 ARM_v5TE-J 架构支持， J=1 表示处于 Jazelle 状态，此位通常和 T(bit5)位一起表示当前所使用的指令集，如表 6.3.2.1 所示：

GE[3:0](bit19:16)： SIMD 指令有效，大于或等于。IT[7:2](bit15:10)： 参考 IT[1:0]

。



E(bit9)： 大小端控制位， E=1 表示大端模式， E=0 表示小端模式。A(bit8)： 禁止异步中断位， A=1 表示禁止异步中断。I(bit7)： I=1 禁止 IRQ， I=0 使能 IRQ

。



F(bit6)： F=1 禁止 FIQ， F=0 使能 FIQ

。



T(bit5)： 控制指令执行状态，表明本指令是 ARM 指令还是 Thumb 指令，通常和 J(bit24)一起表明指令类型，参考 J(bit24)

位。



M[4:0]： 处理器模式控制位，含义如表 6.3.2.2 所示：

![image-20240717204353796](https://github.com/user-attachments/assets/90ed78df-1555-4517-87db-860fab5b623c)






ARM Cotex(arm v7)p41

-----------------------------------------------------
![image-20240717205247601](https://github.com/user-attachments/assets/dff34cdf-f196-40a4-9eb9-8f9d760b4730)



a new Mode TrustZone Security Extensions. independent of privilege and processor mode????

![image-20240717204353796](https://github.com/user-attachments/assets/fb30391a-d03e-493b-8375-533df5bf32ea)



described in ARM Cotex(ARM v7)Chapter 21

And Hypvervisor mode???? 

![image-20240717204529623](https://github.com/user-attachments/assets/c8b00a25-144e-4495-b5a9-ba3ca886fada)



-----------------------------------------------------





