# The module name
obj-m := My_SPI_Driver.o

# All object files MUST be listed directly here
# Note: No leading slashes for folder paths
My_SPI_Driver-objs := \
    MCP2515/Src/MY_MCP2515.o \
    MCP2515/Src/MY_MCP2516_RX.o \
    MCP2515/Src/SPI_CAN_operations.o \
    SPI_driver_core/Src/SPI_driver_clean.o \
    SPI_driver_core/Src/SPI_driver_init.o \
    SPI_driver_core/Src/SPI_driver_operations.o \
    SPI_driver_core/Src/SPI_driver_variables.o \

# Standard Kbuild variables
KDIR := /lib/modules/$(shell uname -r)/build
PWD  := $(shell pwd)

all:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	$(MAKE) -C $(KDIR) M=$(PWD) clean

# Add this line near the top of your Makefile
ccflags-y := -std=gnu99 -Wno-unused-variable

.PHONY: all clean

