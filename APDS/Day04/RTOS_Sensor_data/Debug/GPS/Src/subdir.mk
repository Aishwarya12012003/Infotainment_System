################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../GPS/Src/gps.c \
../GPS/Src/uart.c 

OBJS += \
./GPS/Src/gps.o \
./GPS/Src/uart.o 

C_DEPS += \
./GPS/Src/gps.d \
./GPS/Src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
GPS/Src/%.o GPS/Src/%.su GPS/Src/%.cyclo: ../GPS/Src/%.c GPS/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/GPS/Inc" -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/MCP2515_TX/Inc" -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/SPI/Inc" -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/APDS" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-GPS-2f-Src

clean-GPS-2f-Src:
	-$(RM) ./GPS/Src/gps.cyclo ./GPS/Src/gps.d ./GPS/Src/gps.o ./GPS/Src/gps.su ./GPS/Src/uart.cyclo ./GPS/Src/uart.d ./GPS/Src/uart.o ./GPS/Src/uart.su

.PHONY: clean-GPS-2f-Src

