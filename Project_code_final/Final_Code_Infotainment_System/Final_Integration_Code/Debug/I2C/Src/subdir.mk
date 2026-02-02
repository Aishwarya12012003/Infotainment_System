################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../I2C/Src/i2c.c 

OBJS += \
./I2C/Src/i2c.o 

C_DEPS += \
./I2C/Src/i2c.d 


# Each subdirectory must supply rules for building sources it contributes
I2C/Src/%.o I2C/Src/%.su I2C/Src/%.cyclo: ../I2C/Src/%.c I2C/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/GPS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/UART/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/APDS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/I2C/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/MCP2515_TX/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/SPI/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/include" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-I2C-2f-Src

clean-I2C-2f-Src:
	-$(RM) ./I2C/Src/i2c.cyclo ./I2C/Src/i2c.d ./I2C/Src/i2c.o ./I2C/Src/i2c.su

.PHONY: clean-I2C-2f-Src

