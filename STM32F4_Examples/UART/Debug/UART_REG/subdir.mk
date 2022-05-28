################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../UART_REG/UART_REG.c 

OBJS += \
./UART_REG/UART_REG.o 

C_DEPS += \
./UART_REG/UART_REG.d 


# Each subdirectory must supply rules for building sources it contributes
UART_REG/%.o UART_REG/%.su: ../UART_REG/%.c UART_REG/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F401RETx -DSTM32F4 -c -I../Inc -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/NVIC_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/GPIO_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/CLOCK_REG" -I"D:/STM32/STM32_SourceCode/STM32_Programming/STM32F4_Examples/UART/UART_REG" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-UART_REG

clean-UART_REG:
	-$(RM) ./UART_REG/UART_REG.d ./UART_REG/UART_REG.o ./UART_REG/UART_REG.su

.PHONY: clean-UART_REG

