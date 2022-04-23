################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
D:/STM32/STM32_SourceCode/Register\ Programming/Common_Lib/DelayTimer.c 

OBJS += \
./Common_Lib/DelayTimer.o 

C_DEPS += \
./Common_Lib/DelayTimer.d 


# Each subdirectory must supply rules for building sources it contributes
Common_Lib/DelayTimer.o: D:/STM32/STM32_SourceCode/Register\ Programming/Common_Lib/DelayTimer.c Common_Lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DARM_MATH_CM4 -DSTM32F4XX -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/Register Programming/Common_Lib" -O0 -ffunction-sections -fdata-sections -Wall -v -fstack-usage -MMD -MP -MF"Common_Lib/DelayTimer.d" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

