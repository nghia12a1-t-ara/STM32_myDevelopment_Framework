################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32/STM32_SourceCode/Register\ Programming/STM32F4_Drivers/DMA/src/DMA.c 

OBJS += \
./DMA/src/DMA.o 

C_DEPS += \
./DMA/src/DMA.d 


# Each subdirectory must supply rules for building sources it contributes
DMA/src/DMA.o: D:/STM32/STM32_SourceCode/Register\ Programming/STM32F4_Drivers/DMA/src/DMA.c DMA/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/Register Programming/STM32F4_Drivers/Clock/inc" -I"D:/STM32/STM32_SourceCode/Register Programming/STM32F4_Drivers/Common/inc" -I"D:/STM32/STM32_SourceCode/Register Programming/STM32F4_Drivers/DMA/inc" -I"D:/STM32/STM32_SourceCode/Register Programming/DMA_MemtoMem/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"DMA/src/DMA.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

