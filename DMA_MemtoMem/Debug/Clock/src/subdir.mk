################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32/STM32_SourceCode/Register\ Programming/STM32F4_Drivers/Clock/src/stm32f4xx_rcc_driver.c 

OBJS += \
./Clock/src/stm32f4xx_rcc_driver.o 

C_DEPS += \
./Clock/src/stm32f4xx_rcc_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Clock/src/stm32f4xx_rcc_driver.o: D:/STM32/STM32_SourceCode/Register\ Programming/STM32F4_Drivers/Clock/src/stm32f4xx_rcc_driver.c Clock/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/Register Programming/STM32F4_Drivers/Clock/inc" -I"D:/STM32/STM32_SourceCode/Register Programming/STM32F4_Drivers/Common/inc" -I"D:/STM32/STM32_SourceCode/Register Programming/STM32F4_Drivers/DMA/inc" -I"D:/STM32/STM32_SourceCode/Register Programming/DMA_MemtoMem/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Clock/src/stm32f4xx_rcc_driver.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

