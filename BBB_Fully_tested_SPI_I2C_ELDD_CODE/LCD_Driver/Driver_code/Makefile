
obj-m := main.o

main-objs := day4_i2c_lcd_driver.o

#all:
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/sunbeam/linux/linux M=`pwd` modules
	
#clean:
#	make ARCH=arm CROSS_COMPILE=arm-linux-gnueabihf- -C /home/sunbeam/linux/linux M=`pwd` clean

# Standard Kbuild variables
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

.PHONY: deploy clean

