################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MCP2515_TX/Src/MY_MCP2515.c \
../MCP2515_TX/Src/MY_MCP2515_TX.c \
../MCP2515_TX/Src/MY_MCP2516_RX.c 

OBJS += \
./MCP2515_TX/Src/MY_MCP2515.o \
./MCP2515_TX/Src/MY_MCP2515_TX.o \
./MCP2515_TX/Src/MY_MCP2516_RX.o 

C_DEPS += \
./MCP2515_TX/Src/MY_MCP2515.d \
./MCP2515_TX/Src/MY_MCP2515_TX.d \
./MCP2515_TX/Src/MY_MCP2516_RX.d 


# Each subdirectory must supply rules for building sources it contributes
MCP2515_TX/Src/%.o MCP2515_TX/Src/%.su MCP2515_TX/Src/%.cyclo: ../MCP2515_TX/Src/%.c MCP2515_TX/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/GPS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/UART/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/APDS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/I2C/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/MCP2515_TX/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/SPI/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/include" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCP2515_TX-2f-Src

clean-MCP2515_TX-2f-Src:
	-$(RM) ./MCP2515_TX/Src/MY_MCP2515.cyclo ./MCP2515_TX/Src/MY_MCP2515.d ./MCP2515_TX/Src/MY_MCP2515.o ./MCP2515_TX/Src/MY_MCP2515.su ./MCP2515_TX/Src/MY_MCP2515_TX.cyclo ./MCP2515_TX/Src/MY_MCP2515_TX.d ./MCP2515_TX/Src/MY_MCP2515_TX.o ./MCP2515_TX/Src/MY_MCP2515_TX.su ./MCP2515_TX/Src/MY_MCP2516_RX.cyclo ./MCP2515_TX/Src/MY_MCP2516_RX.d ./MCP2515_TX/Src/MY_MCP2516_RX.o ./MCP2515_TX/Src/MY_MCP2516_RX.su

.PHONY: clean-MCP2515_TX-2f-Src

