
obj-m := main.o

main-objs := lcd_common.o lcd_driver.o lcd_fops.o  lcd_module.o  lcd_ops.o

all:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/sunbeam/linux/linux M=`pwd` modules
	
clean:
	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/sunbeam/linux/linux M=`pwd` clean


.PHONY: deploy clean

