################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPS/Src/gps.c 

OBJS += \
./GPS/Src/gps.o 

C_DEPS += \
./GPS/Src/gps.d 


# Each subdirectory must supply rules for building sources it contributes
GPS/Src/%.o GPS/Src/%.su GPS/Src/%.cyclo: ../GPS/Src/%.c GPS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F411CEUx -c -I../Inc -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/GPS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/UART/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/APDS/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/I2C/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/MCP2515_TX/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/SPI/Inc" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/include" -I"/home/raghav/Desktop/Final_Code_Infotainment_System/Final_Integration_Code/ThirdParty/FreeRTOS/portable/GCC/ARM_CM4F" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GPS-2f-Src

clean-GPS-2f-Src:
	-$(RM) ./GPS/Src/gps.cyclo ./GPS/Src/gps.d ./GPS/Src/gps.o ./GPS/Src/gps.su

.PHONY: clean-GPS-2f-Src

