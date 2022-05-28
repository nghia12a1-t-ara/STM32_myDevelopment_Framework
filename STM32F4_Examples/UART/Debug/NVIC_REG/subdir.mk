################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../NVIC_REG/NVIC_REG.c 

OBJS += \
./NVIC_REG/NVIC_REG.o 

C_DEPS += \
./NVIC_REG/NVIC_REG.d 


# Each subdirectory must supply rules for building sources it contributes
NVIC_REG/%.o NVIC_REG/%.su: ../NVIC_REG/%.c NVIC_REG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/NVIC_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/GPIO_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/CLOCK_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/UART_REG" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-NVIC_REG

clean-NVIC_REG:
	-$(RM) ./NVIC_REG/NVIC_REG.d ./NVIC_REG/NVIC_REG.o ./NVIC_REG/NVIC_REG.su

.PHONY: clean-NVIC_REG

