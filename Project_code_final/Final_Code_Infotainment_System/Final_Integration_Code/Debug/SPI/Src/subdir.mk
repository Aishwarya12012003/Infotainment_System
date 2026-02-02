################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SPI/Src/MY_PIN.c \
../SPI/Src/MY_SPI.c 

OBJS += \
./SPI/Src/MY_PIN.o \
./SPI/Src/MY_SPI.o 

C_DEPS += \
./SPI/Src/MY_PIN.d \
./SPI/Src/MY_SPI.d 


# Each subdirectory must supply rules for building sources it contributes
SPI/Src/%.o SPI/Src/%.su SPI/Src/%.cyclo: ../SPI/Src/%.c SPI/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/GPS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/UART/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/APDS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/I2C/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/MCP2515_TX/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/SPI/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/include" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-SPI-2f-Src

clean-SPI-2f-Src:
	-$(RM) ./SPI/Src/MY_PIN.cyclo ./SPI/Src/MY_PIN.d ./SPI/Src/MY_PIN.o ./SPI/Src/MY_PIN.su ./SPI/Src/MY_SPI.cyclo ./SPI/Src/MY_SPI.d ./SPI/Src/MY_SPI.o ./SPI/Src/MY_SPI.su

.PHONY: clean-SPI-2f-Src

