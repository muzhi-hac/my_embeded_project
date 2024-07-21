
TARGET			?=sdk

# source 			:=%.c

# obj				:=led

TOOL			?=arm-linux-gnueabihf

GCC 			:=$(TOOL)-gcc
LD				:=$(TOOL)-ld
OBJCOPY			:=$(TOOL)-objcopy
OBJDUMP			:=$(TOOL)-objdump

INCDIRS 		:=imx6ul \
				bsp/clock \
				bsp/led	\
				bsp/delay \
				bsp/beep

SRCDIRS			:=project \
				bsp/clock \
				bsp/led \
				bsp/delay \
				bsp/beep


VPATH			:= $(SRCDIRS)
INCLUDE 		:=$(patsubst %, -I %, $(INCDIRS))

SFILESDIR		:=$(foreach dir, $(SRCDIRS) , $(wildcard $(dir)/*.S))
CFILESDIR		:=$(foreach dir, $(SRCDIRS) , $(wildcard $(dir)/*.c))
# SFILEDIR =bsp/clock/xxx.S

SFILES 			:=$(notdir $(SFILESDIR))
CFILES			:=$(notdir $(CFILESDIR))
#SFILES =xxx.S
SOBJS			:=$(patsubst %, obj/% ,$(SFILES:.S=.o))
COBJS			:=$(patsubst %, obj/% ,$(CFILES:.c=.o))
#SOBJS =obj/xxx.o
OBJS			:=$(SOBJS) $(COBJS)

VPATH			:= $(SRCDIRS)
.PHONY: clean


show-vars:
	@echo "INCDIRS: $(INCDIRS)"
	@echo "SRCDIRS: $(SRCDIRS)"
	@echo "INCLUDE: $(INCLUDE)"
	@echo "SFILESDIR: $(SFILESDIR)"
	@echo "CFILESDIR: $(CFILESDIR)"
	@echo "SFILES: $(SFILES)"
	@echo "CFILES: $(CFILES)"
	@echo "SOBJS: $(SOBJS)"
	@echo "COBJS: $(COBJS)"
	@echo "OBJS: $(OBJS)"

#OBJS =obj/xxx.o
$(TARGET).bin:$(OBJS)
	$(LD) -Timx6ul.lds -o $(TARGET).elf $^
	$(OBJCOPY) -O binary -S $(TARGET).elf $@
	$(OBJDUMP) -D -m arm $(TARGET).elf >$(TARGET).dis

$(SOBJS) : obj/%.o :  %.S
	$(GCC) -c -Wall -nostdlib -O2 $(INCLUDE) -o $@ $<

$(COBJS): obj/%.o :  %.c
	$(GCC) -c -Wall -nostdlib -O2 $(INCLUDE) -o $@ $<
#-Wall：打开几乎所有的编译器警告，有助于发现代码中的潜在问题。
# -nostdlib：在编译过程中不使用标准库。这通常在编写操作系统或嵌入式系统的底层代码时使用。
# -c：告诉编译器只编译源代码，但不进行链接。
# -O2：这是一个优化等级，告诉编译器进行较为深入的代码优化，以提高代码的执行效率。
#-I 告诉编译器这个源码在哪里去搜索

# $(obj).bin:$(obj).s
# 	$(tool)-gcc -g -c led.s -o $(obj).o 
# 	$(tool)-ld -Ttext 0X87800000 $(obj).o -o $(obj).elf
# 	$(tool)-objcopy -O binary -S -g $(obj).elf $(obj).bin  
# 	$(tool)-objdump -D $(obj).elf >$(obj).dis

#$(name).o:$(name).s
#	$(tool)-gcc -g -c 
#$(name).o:$(name).c

clean:
#	rm -rf *.o led.bin led.elf led.dis
	rm -rf  $(TARGET).bin $(TARGET).elf $(TARGET).dis $(OBJS)
