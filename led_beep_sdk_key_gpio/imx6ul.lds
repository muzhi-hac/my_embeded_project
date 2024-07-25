/* 定义内存区域 */
/*MEMORY
{
  RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 128K
  FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 512K
}*/
/* 内存区域暂时没用到*/
SECTIONS{
    . =0x87800000;
    .text ALIGN(4):
    {
      obj/sdk.o
      *(.text)
    }
    .rodata ALIGN(4):
    {
      
      *(.rodata*)
    }
    .data : 
    {              /* 数据部分 */
        *(.data)           /* 把所有.data段的内容放这里 */
    }
     __bss_start = .;
    .bss  ALIGN(4): {               /* 可变数据部分 */
       
       *(.bss) 
       *(COMMON)            /* 把所有.bss段的内容放这里 */
      
    }
     __bss_end = .;


}