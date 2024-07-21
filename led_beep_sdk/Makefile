
target			:=sdk

source 			:=%.c

obj				:=led

tool			:=arm-linux-gnueabihf

gcc 			:=$(tool)-gcc
ld 				:=$(tool)-ld
objcopy			:=$(tool)-objcopy
objdump			:=$(tool)-objdump

INCDIRS 		:=imx6ul \
				bsp/clock \
				bsp/led	\

SRCDIRS			:=project \
				bsp/clock \
				bsp/led

SFILESDIR		:=$(foreach dir, $(SRCDIRS),$(wildcard $(dir)/%.s))
CFILESDIR		:=$(foreach dir, $(SRCDIRS),$(wildcard $(dir)/%.c))

SFILES 			:=$(notdir $(SFILESDIR))
CFILES			:=$(notdir $(CFILESDIR))




$(obj).bin:$(obj).s
	$(tool)-gcc -g -c led.s -o $(obj).o 
	$(tool)-ld -Ttext 0X87800000 $(obj).o -o $(obj).elf
	$(tool)-objcopy -O binary -S -g $(obj).elf $(obj).bin  
	$(tool)-objdump -D $(obj).elf >$(obj).dis

$(name).o:$(name).s
	$(tool)-gcc -g -c 
$(name).o:$(name).c

clean:
	rm -rf *.o led.bin led.elf led.dis