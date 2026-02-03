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
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/GPS/Inc" -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/MCP2515_TX/Inc" -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/SPI/Inc" -I"/home/sunbeam/STM32CubeIDE/workspace_1.19.0/RTOS_Sensor_data/APDS" -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-MCP2515_TX-2f-Src

clean-MCP2515_TX-2f-Src:
	-$(RM) ./MCP2515_TX/Src/MY_MCP2515.cyclo ./MCP2515_TX/Src/MY_MCP2515.d ./MCP2515_TX/Src/MY_MCP2515.o ./MCP2515_TX/Src/MY_MCP2515.su ./MCP2515_TX/Src/MY_MCP2515_TX.cyclo ./MCP2515_TX/Src/MY_MCP2515_TX.d ./MCP2515_TX/Src/MY_MCP2515_TX.o ./MCP2515_TX/Src/MY_MCP2515_TX.su ./MCP2515_TX/Src/MY_MCP2516_RX.cyclo ./MCP2515_TX/Src/MY_MCP2516_RX.d ./MCP2515_TX/Src/MY_MCP2516_RX.o ./MCP2515_TX/Src/MY_MCP2516_RX.su

.PHONY: clean-MCP2515_TX-2f-Src

