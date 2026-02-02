################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART/Src/pin_config.c \
../UART/Src/uart.c \
../UART/Src/uart_config.c 

OBJS += \
./UART/Src/pin_config.o \
./UART/Src/uart.o \
./UART/Src/uart_config.o 

C_DEPS += \
./UART/Src/pin_config.d \
./UART/Src/uart.d \
./UART/Src/uart_config.d 


# Each subdirectory must supply rules for building sources it contributes
UART/Src/%.o UART/Src/%.su UART/Src/%.cyclo: ../UART/Src/%.c UART/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/GPS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/UART/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/APDS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/I2C/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/MCP2515_TX/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/SPI/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/include" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UART-2f-Src

clean-UART-2f-Src:
	-$(RM) ./UART/Src/pin_config.cyclo ./UART/Src/pin_config.d ./UART/Src/pin_config.o ./UART/Src/pin_config.su ./UART/Src/uart.cyclo ./UART/Src/uart.d ./UART/Src/uart.o ./UART/Src/uart.su ./UART/Src/uart_config.cyclo ./UART/Src/uart_config.d ./UART/Src/uart_config.o ./UART/Src/uart_config.su

.PHONY: clean-UART-2f-Src

