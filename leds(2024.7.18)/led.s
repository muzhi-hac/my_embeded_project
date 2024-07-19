.global _start
    _start:
    LDR R1,=0X20C4070
    STR (3<<26), [R1] ;clock

    LDR R2,=0X20E0068
    STR 0X5, [R2] ;

    LDR R3,=0X20E02F4 ；PAD
    /*
bit 16 HYS 0:是否使能迟滞比较器 0
bit 15-14 00 选择一个100k下拉，在没有输入的时候是接地的，所以我认为选这个比较好
bit 13 0 选择一个keeper保持器
bit 12 1 使能keeper保持器
bit 11 0 是否使能开路输出，我这里选择的是不开启,我的理解是我选择的是下拉电阻，如果再选这个，那么没有上拉电阻将其拉到高电位，就g了
bit 10-8 000 reserved
bit 7-6  01 速率选择 01 选了个100MHZ(中庸之道),10也是100MHZ
bit 5-3  110 驱动强度 越往下，强度越高
bit 2-1 reserved 
bit 0 SRE 变化率快慢 0 因为变化率快了功耗高容易g?。
所以是 0001 0000 1011 000 0=0X10B0
    */
    LDR R4,=0X10B0
    STR R4,[R3]
/*
设置GPIO registers
*/
    LDR R0,0X209_C0004 ;GDIR
    STR (1<<3),[R0]

    LDR R0,=0X209_C0000 ;GPIO1_DR
    STR (0<<3),[R0]
    



