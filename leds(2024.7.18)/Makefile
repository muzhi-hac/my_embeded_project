source =%.c
obj=led
tool=arm-linux-gnueabihf
$(obj).bin:$(obj).s
	$(tool)-gcc -g -c led.s -o $(obj).o 
	$(tool)-ld -Ttext 0X87800000 $(obj).o -o $(obj).elf
	$(tool)-objcopy -O binary -S -g $(obj).elf $(obj).bin  
